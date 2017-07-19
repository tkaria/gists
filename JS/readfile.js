const readline = require('readline');
const fs = require('fs');
const parse = require('csv-parse');

const rl = readline.createInterface({
      input: fs.createReadStream('sample.txt')
});

rl.on('line', (line) => {
      parse(line, {delimiter: ','}, function(err, data) {

        console.log('Parsed?:', data );
        console.log('Orig:', line );
        console.log(`Line: ${line}`);
      })
});
