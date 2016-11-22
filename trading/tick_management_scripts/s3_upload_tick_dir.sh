#!/bin/bash

export PYTHONPATH=:/usr/local/lib/python2.7/site-packages

# User access
export AWS_SECRET_ACCESS_KEY=
export AWS_ACCESS_KEY_ID=


python_cmd=`which python`

$python_cmd ~/s3_upload_tick_dir.py -f $1 $2
