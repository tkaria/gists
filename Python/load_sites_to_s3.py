"""
Take export from PG and load to S3 stage1 bucket
"""
from __future__ import print_function
import sys
import logging
import json
import boto3
import botocore
import os
import tldextract

LOGGER = logging.getLogger()
S3_CLIENT = boto3.client('s3')

def loader(site_file):
    """
    Read line from sites.txt, output file, upload to s3
    """
    with open(site_file, 'r') as infile:
        for line in infile:
            if line:
                json_rep = json.loads(line)
                entity_id = json_rep['entity_id']
                url = json_rep['url']
                extract = tldextract.extract(url)
                url_for_filename =  extract.domain + '.' + extract.suffix
                json_rep['url'] = url_for_filename
                outfilename  = '{}-{}.json'.format(url_for_filename, entity_id)
            try:
                with open(outfilename, 'w+') as outfile:
                    print(line, '->', json.dumps(json_rep))
                    outfile.write(json.dumps(json_rep))
                    outfile.close()
                    S3_CLIENT.upload_file(outfile.name, 'ventureiq-entity-1', outfile.name)
                os.unlink(outfilename)
            except botocore.exceptions.ClientError as boto_error:
                LOGGER.warn(boto_error)

if __name__ == '__main__':
    if len(sys.argv) >= 2:
        SITES = sys.argv[1]
    else:
        SITES = 'sites.txt'
    LOGGER.info('Reading input from: {}'.format(SITES))
    loader(SITES)
