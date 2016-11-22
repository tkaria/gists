#!/bin/bash

remotetickdir="/home/timir"
localtickdir=$remotetickdir

# FOR TESTING - use localhost
#remoteserver="127.0.0.1"
#remoteserver="172.16.2.101"

#remoteuser="timir"
#bindir="/home/timir/capitalk.repo/src/dataCollector"
bindir="/home/timir/collectors/collect-fix"
shelldir="/home/timir"

today="$(date +%Y_%m_%d)"
echo "Today: $today"

yesterday=$(date --date=" -1 day" "+%Y_%m_%d")
echo "Yesterday: $yesterday"

# Pass MIC names to script to move associated ticks and logs
while [ $# -gt 0 ]
do 
MIC=$1
MIC_LOWERCASE="${MIC,,}"

# Dispaly some info
echo "===DISK REPORT BEFORE MOVE==="
df -h $remotetickdir/$MIC/$yesterday/

# Stop the collector
echo "Stopping collect"
cat $bindir/collect.$MIC.pid | xargs kill -15

# Rename raw message logs while collector stopped
echo "Renaming logs"
cd $remotetickdir/$MIC/log && for w in *.log; do mv $w $yesterday-$w; done

# Restart the collector
echo "Restarting collect" 
# FOR TESTING - remove the uncomment below and comment the next line
#cd $bindir && $bindir/collect.$MIC.dev.sh
cd $bindir && $bindir/collect.$MIC.prod.sh

# Zip up tick files and copy them over to S3
echo "Compressing tick data"
nice -n 1 gzip $remotetickdir/$MIC/$yesterday/*.csv
sh $shelldir/s3_upload_tick_dir.sh $remotetickdir/$MIC/$yesterday/ capk-$MIC_LOWERCASE

###############################################################################
# LOG FILES SHOULD USE AMAZON GLACIER WHEN IT IS SUPPORTED BY BOTO
# KTK TODO 20120906
###############################################################################
# Compress log files 
#echo "Compressing logs" 
#nice -n 1 gzip $remotetickdir/$MIC/log/$yesterday-*.log
#echo "Moving logs to S3 buckets" 
#/bin/bash s3_multipart_upload_dir.sh $remotetickdir/$MIC/log/*.gz capk-$MIC_LOWERCASE

# Delete log files that are ZIPPED ONLY - collector will be running again at this point
echo "Delete $yesterday logfiles"
rm -f $remotetickdir/$MIC/log/*$yesterday*.log

# Dispaly some info
echo "===DISK REPORT AFTER MOVE AND DELETE==="
df -h $remotetickdir

mail -s "Tick file move to s3 $today" tkaria@capitalkpartners.com << E_O_M
    DISK REPORT AFTER MOVE $MIC
    `df -h`
E_O_M


shift
done

