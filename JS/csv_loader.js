/*
 * www.ventureiq.io
 *
 * Copyright (c) 2017 VentureIQ
 * Author timir@ventureiq.nl 
 */

'use strict';

// npm packages
const Q = require('q');
const fs = require('fs');
const parse = require('csv-parse/lib/sync');
const commandLineArgs = require('command-line-args');
const util = require('util');
const stream = require('stream');
const es = require('event-stream');

// VIQ package
const db = require('../db');
//const scripts = require('../elastic/scripts');
//const e = require('../elastic/entities');
const promiseError = require('../utils').promiseError;

// psql -h localhost -d viq_db_dev -U viq_admin
var entities = [];
let data = [];

const optionDefinitions = [{
    name: 'inFile',
    alias: 'f',
    type: String,
    /*multiple: true,*/
    defaultOption: true
  },
  {
    name: 'dbHost',
    alias: 'd',
    type: String,
    defaultValue: 'localhost'
  },
  {
    name: 'dbPort',
    alias: 'p',
    type: String,
    defaultValue: '5432'
  },
  {
    name: 'dbPass',
    alias: 'a',
    type: String,
    defaultValue: 'XXX'
  },
  {
    name: 'dbUser',
    alias: 'u',
    type: String,
    defaultValue: 'viq_admin'
  },
  {
    name: 'dbDb',
    alias: 'b',
    type: String,
    defaultValue: 'viq_db_dev'
  }
]

const options = commandLineArgs(optionDefinitions);
if (!options.inFile) {
  console.log(process.argv[1]);
  console.log('Usage: node ' + thisFileName() + ' -f filename.csv [ -d <db_host> -p <db_port> -a <db_pass> -u <db_user> -b <db_db>]')
  process.exit(-1);
}

function thisFileName() {
  const path = require('path');
  var fullpath = process.argv[1];
  var pathComponents = fullpath.split(path.sep);
  return pathComponents.length >= 1 ? pathComponents[pathComponents.length - 1] : "???/"
}

readCSVFile(options.inFile);
console.log(getDBConnectionString(options.dbUser, options.dbPass, options.dbHost, options.dbPort, options.dbDb));

function readCSVFile(filename) {
  var lineNr = 0;
  var parse = require('csv-parse');

  var s = fs.createReadStream(filename)
    .pipe(es.split())
    .pipe(es.mapSync(function (line) {

        // pause the readstream
        s.pause();


        // process line here and call s.resume() when rdy
        // function below was for logging memory usage
        //logMemoryUsage(lineNr);
        console.log(lineNr +  ': ' + line); 

        lineNr += 1;
        // resume the readstream, possibly from a callback
        // console.log(line);
        parse(line, {delimiter: ";", rowDelimiter: 'unicode'}, function(err, data){
            console.log(data);
            console.log(`${data}`);
        })
        s.resume();
      })
      .on('error', function () {
        console.log('Error while reading file.');
      })
      .on('end', function () {
        console.log('Read entire file.')
      })
    );
}

function getDBConnectionString(dbUser, dbPass, dbHost, dbPort, dbDb) {
  //connectionString: `postgresql://${process.env.PG_USER}:${process.env.PG_PASS}@${process.env.PG_HOST}:${process.env.PG_PORT}/${process.env.PG_DB}`
  return 'postgresql://' +
    dbUser + ':' +
    dbPass + '@' +
    dbHost + ':' +
    dbPort + '/' +
    dbDb;
}

function makeLocation(freeform) {
  if ((typeof freeform !== typeof '') || !(freeform.trim())) {
    return null;
  }
  if (freeform.length === 2) {
    return {
      country: freeform
    };
  }
  return {
    freeform
  };
}

function validDate(dateAttempt) {
  if ((typeof dateAttempt !== typeof '') || !(dateAttempt.trim())) {
    return null;
  }
  try {
    return (new Date(dateAttempt)).toISOString().split('T')[0];
  } catch (e) {
    return null;
  }
}

function parseRevenue(revenue) {
  if (typeof revenue === typeof '') {
    revenue = revenue.trim().toLowerCase().replace(/,/, '.');
    if (revenue.endswith('k') && !isNaN(parseInt(revenue.substring(revenue.length - 1)))) {
      revenue = parseFloat(revenue) * 1000;
    } else if (revenue.endswith('m') && !isNaN(parseInt(revenue.substring(revenue.length - 1)))) {
      revenue = parseFloat(revenue) * 1000000;
    }
  }
  return Number.isFinite(revenue) ? revenue : null;
}

function addCompany(tagId, entityProfile) {
  // configure/decorate
  let userEmail = 'adam@coocoo.lu',
    clientId = 0;
  let name = typeof entityProfile.name === typeof '' ? entityProfile.name.trim() : '',
    description = typeof entityProfile.description === typeof '' ? entityProfile.description.trim() : '',
    general_score = parseInt(entityProfile.general_score) || null,
    financial_description = typeof entityProfile.financial_description === typeof '' ? entityProfile.financial_description.trim() : null,
    location = makeLocation(entityProfile.country),
    date_founded = validDate(entityProfile.date_founded),
    financial_revenue = parseRevenue(entityProfile.financial_revenue),
    technology_score = parseInt(entityProfile.technology_score) || null,
    oneliner = typeof entityProfile.oneliner === typeof '' ? entityProfile.oneliner : null,
    kvstorage = {
      "version": 1
    },
    tags = typeof entityProfile.tags === typeof '' && entityProfile.tags.trim() ? entityProfile.tags.trim().split('|').map(x => x.trim()) : [];

  if (oneliner) {
    kvstorage['oneliner'] = oneliner;
  }

  if (!name) {
    return promiseError({
      status: 400,
      message: 'profile without name is invalid'
    });
  }

  let profile = [
    'description',
    'general_score',
    'technology_score',
    'oneliner',
    'financial_description',
    'location', // -> 'freeform',
    // 'country' -> 'location/country'
    // 'city' -> 'location/city'
    // 'state' -> 'location/state'
    // 'address' -> 'location/address'
    // 'postcode' -> 'location/postcode'
    // 'latlng' -> 'location/lat location/lng'
    'date_founded',
    'website',
    'business_model',
    'employees',
    'financial_revenue',
  ];

  return db(`
  WITH _user AS (
    SELECT user_id FROM user_profile_v1 WHERE email = $1
  ),
  _existing_entity AS (
    SELECT entity_id, name FROM entities_v1 WHERE name = $3
  ),
  _new_entity AS (
    INSERT INTO entity_user_v1
    (user_id, client_id, name, is_company, is_university, is_person)
    SELECT (SELECT user_id FROM _user), $2, $3, 100, 0, 0
    WHERE NOT EXISTS ( SELECT 1 FROM _existing_entity )
    RETURNING entity_id, name
  ),
  _entity AS (
    SELECT * FROM _existing_entity UNION SELECT * FROM _new_entity
  ),
  _new_tags AS (
    INSERT INTO tags_v1 (value)
    SELECT * FROM UNNEST($13::text[])
    ON CONFLICT DO NOTHING
    RETURNING *
  ),
  _entity_profile AS (
    INSERT INTO entities_profile_v1
    (user_id, client_id, entity_id, description, general_score, financial_description, location, date_founded, financial_revenue, technology_score, kvstorage)
    SELECT (SELECT user_id FROM _user), $2, entity_id, $5, $6, $7, $8, $9, $10, $11, $12
    FROM _new_entity
    RETURNING *
  ),
  _entity_tag AS (
    INSERT INTO entities_tags_v1 (entity_id, tag_id, user_id, client_id)
    SELECT (SELECT entity_id FROM _entity), tag_id, (SELECT user_id FROM _user), $2
    FROM (
      SELECT tag_id FROM tags_v1 t WHERE value = ANY($13::text[])
      AND NOT EXISTS (SELECT 1 FROM entities_tags_v1 JOIN _entity USING (entity_id) WHERE tag_id = t.tag_id)
      UNION
      SELECT tag_id FROM tags_v1 t WHERE tag_id = $4
      AND NOT EXISTS (SELECT 1 FROM entities_tags_v1 JOIN _entity USING (entity_id) WHERE tag_id = t.tag_id)
    ) _
    RETURNING 1
  )
  SELECT *, (SELECT count(*) FROM _entity_tag) AS tagsCount FROM entities_user_input_v1 JOIN _entity USING(entity_id)
  `, [userEmail, clientId, name, tagId, description, general_score, financial_description, location, date_founded, financial_revenue, technology_score, kvstorage, tags])
    .then(x => scripts.updateEntity(x.rows[0].entity_id).then(() => x))
    .then(x => {
      let createdProfile = x.rows[0];
      let toUpdate = {};
      if (description && !createdProfile.description.trim()) {
        toUpdate.description = description
      }
      if (general_score && !createdProfile.general_score) {
        toUpdate.general_score = general_score
      }
      if (financial_description && !createdProfile.financial_description.trim()) {
        toUpdate.financial_description = financial_description
      }
      if (location && (!createdProfile.location || createdProfile.location === {})) {
        toUpdate.location = location
      }
      if (date_founded && !createdProfile.date_founded) {
        toUpdate.date_founded = date_founded
      }
      if (financial_revenue && !createdProfile.financial_revenue) {
        toUpdate.financial_revenue = financial_revenue
      }
      if (technology_score && !createdProfile.technology_score) {
        toUpdate.technology_score = technology_score
      }
      if (kvstorage.oneliner && (!createdProfile.kvstorage || !createdProfile.kvstorage.oneliner)) {
        createdProfile.kvstorage = createdProfile.kvstorage || kvstorage;
        createdProfile.kvstorage.oneliner = kvstorage.oneliner;
        toUpdate.kvstorage = createdProfile.kvstorage;
      }
      let updateKeys = Object.getOwnPropertyNames(toUpdate);
      let promise;
      if (updateKeys.length > 0) {
        promise = db(`UPDATE entities_profile_v1 SET ${updateKeys.map((x,i)=>`${x} = $${i+4}`).join(', ')},
        user_id = (SELECT user_id FROM user_profile_v1 WHERE email = $2), client_id = $3
        WHERE entity_id = $1
      `, [createdProfile.entity_id, userEmail, clientId].concat(updateKeys.map(x => toUpdate[x])))
      } else {
        promise = Q('good!');
      }
      return promise.then(() => {
        console.log(name, 'added successfully!')
      })
    })
    .fail(x => console.log('failed adding entity', name, x));
}

function removeEntity(entity_id) {
  return db(`DELETE FROM entities_v1 WHERE entity_id = $1`, [entity_id])
    .then(x => e.delete(entity_id))
    .then(x => console.log('removed', entity_id))
    .fail(x => console.log(`couldn't remove entity: ${entity_id}'`))
}

module.exports = {
  addCompany,
  parse,
};

// let records  = []; fs.readFile('./water_tech_list_lux_research.csv', 'utf8', (err, _data) => records = scripts.parse(_data, {columns: true}))
// scripts.addCompany(651, records[0]);
