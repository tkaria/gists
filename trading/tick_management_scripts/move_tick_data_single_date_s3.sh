#!/bin/bash

# Use this script to move a single days tick data only.
# It does not move logs or expect to run the day after so it is not suitable 
# for cron usage unless you pass yesterday as the day to move. 

# Where to find and put the tick data
localtickdir="/home/timir"
remotetickdir=$localtickdir

#remoteuser="timir"
# Where are the collector binaries and pid files?
bindir="/home/timir/collectors/collect-fix"

# Check usage
if [ $# -le 1 ]; then
    echo "Usage: $0 YYYY-MM-DD MIC1 MIC2 ..."
fi

# Which day are we moving 
date_to_move=$1

# Convert the data argument to proper format for directory structure
date=$(date --date="$date_to_move" "+%Y_%m_%d")
echo "Moving tick files from: $date"
shift

# Foreach MIC on date_to_move
#   compress all files in date_to_move directory
#   move all compressed files in that directory to S3

while [ $# -gt 0 ]
do 
MIC=$1
MIC_LOWERCASE="${MIC,,}"

# Zip up tick files and copy them over to S3
echo "Compressing tick data"
nice -n 1 gzip $remotetickdir/$MIC/$date/*.csv
sh s3_upload_tick_dir.sh $remotetickdir/$MIC/$date/ capk-$MIC_LOWERCASE

echo "DO NOT FORGET to delete $remotetickdir/$MIC/$date"

shift
done

