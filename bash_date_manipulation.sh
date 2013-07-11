#!/bin/bash

#remotetickdir="/home/timir"
localtickdir="/mnt/raid/tickdata"
remotetickdir=$localtickdir

# FOR TESTING - use localhost
#remoteserver="127.0.0.1"
#remoteserver="172.16.2.101"

#remoteuser="timir"
#bindir="/home/timir/capitalk.repo/src/dataCollector"
bindir="/home/timir/collectors/collect-fix"

# Pass MIC names to script to move associated ticks and logs
while [ $# -gt 1 ]
do 
MIC=$2
MIC_LOWERCASE="${MIC,,}"

#today="$(date +%Y_%m_%d)"
start_date=$1
echo "Today: $start_date"
today=$(date --date="$start_date" "+%Y_%m_%d")
echo "Today: $today"

yesterday=$(date --date="$start_date -1 day" "+%Y_%m_%d")
echo "Yesterday: $yesterday"


shift
done

