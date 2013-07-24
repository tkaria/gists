#!/usr/bin/env python
"""Move a set of ticks in csv.gz format to s3. Can take directory or file

Usage:
s3_move_ticks.py <directory_or_file>  [-f create buckets if they don't exist] 

"""
import os
import sys
import glob
import subprocess
import errno
import commands
from optparse import OptionParser
import s3_multipart_upload
import boto
import mics
from mics import MIC_LIST
from boto.sqs.message import MHMessage


BUCKET_PREFIX="capk-"

def check_s3_bucket_exists(s3cxn, bucket_name):
    if s3cxn is None:
        print "No connection to s3"
    bucket = s3cxn.get_bucket(bucket_name)
    if bucket is None:
        return False
    else:
        return bucket


if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("-f", "--create-buckets", action='store_true', dest="create_buckets", help="Create buckets on s3 if they don't exist now", default=False)
    (options, args) = parser.parse_args()

    if len(args) < 1:
        print __doc__
        sys.exit()
        exit(-1)

    start_date = args[0]
    end_date = args[1]
    if end_date is None:
        print "Assuming single date: ",  start_date
    
    # Check that all buckets exist or create them if needed
    for f in files:
        basefile = os.path.basename(f)
        mic = basefile.split("_")[0]
        bucket_name = BUCKET_PREFIX+mic.lower()
        try:
            print "Checking bucket: ", bucket_name
            bucket = check_s3_bucket_exists(s3cxn, bucket_name)    
        except Exception:
            if options.create_buckets == True:
                print "Creating bucket: ", bucket_name
                s3cxn.create_bucket(bucket_name)
            else:
                sys.exit(errno.ENFILE)
    
        bucket = s3cxn.get_bucket(bucket)
        key = bucket.get_key(basefile)
        exists = (key is not None)
        if exists == True:
            print "Key exists - skipping upload"
        else:
            print "Uploading: ", f
            s3_multipart_upload.main(f, bucket_name)         
