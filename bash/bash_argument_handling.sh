#!/bin/bash

# Where to find and put the tick data
remotetickdir="/home/timir"
localtickdir=$remotetickdir

#remoteuser="timir"
#bindir="/home/timir/capitalk.repo/src/dataCollector"
# Where is the collector and pid files?
bindir="/home/timir/collectors/collect-fix"

if [ $# -le 1 ]; then
    echo "Usage: $0 YYYY-MM-DD MIC1 MIC2 ..."
fi

# Pass MIC names to script to move associated ticks and logs
date_to_move=$1
echo "Using start date: $date_to_move"
extension=$(date --date="$date_to_move" "+%Y_%m_%d")
echo "Today: $extension"
shift

while [ $# -gt 0 ]
do 
MIC=$1


echo "Processing:  $MIC $extension"

shift
done

