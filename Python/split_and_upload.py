"""
Take the results of sql query:
`\COPY (SELECT row_to_json(t)
        FROM (
            SELECT entity_id,  website AS url
            FROM entities_v1
            WHERE name IS NOT null
            AND name <> ''
            AND website IS NOT null
            AND website <> '' limit 100) t) TO '/tmp/keyword_test_1.txt'`
and run this program on the output file
"""
from __future__ import print_function
import sys
sys.path.append('..')
import json
import tldextract
import boto3
import viq_url_utils

with open(sys.argv[1]) as entity_list:
    i = 0
    for line in entity_list:
        try:
            entity = json.loads(line.strip())
            print('Splitting: ', entity['url'])
            url = unicode(entity['url']).strip()
            entity_id = unicode(entity['entity_id']).strip()
            json_filename = u'{}-{}.json'.format(viq_url_utils.parse_domain(url), entity_id)
            with open(json_filename, 'w+') as entity_json:
                entity_json.write(line.strip())
                i += 1
        except Exception as e:
            print('Exception line: ', i)
