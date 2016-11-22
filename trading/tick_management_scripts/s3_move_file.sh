#!/bin/bash

export PYTHONPATH=:/usr/local/lib/python2.7/site-packages:/usr/local/lib/python2.7/site-packages:/usr/local/lib/python2.7/site-packages

export AWS_SECRET_ACCESS_KEY=
export AWS_ACCESS_KEY_ID=


python_cmd=`which python`

$python_cmd ~/upload_and_queue.py -n true -f $1
