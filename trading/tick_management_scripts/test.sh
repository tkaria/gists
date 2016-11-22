#!/bin/bash

#remotetickdir="/home/timir"
#localtickdir="/mnt/raid/tickdata"
#remoteserver="172.16.2.101"
#bindir="/home/timir/capitalk.repo/src/dataCollector"
#
#yesterday="$(date +%Y_%m_%d --date "-1 day")"
#echo "Yesterday: $yesterday"
#
today="$(date +%Y_%m_%d)"
echo "Today: $today"

# Dispaly some info
#ssh timir@$remoteserver "ls -alh $remotetickdir"
#ssh timir@172.16.2.101 "ls -alh $remotetickdir/$MIC/$yesterday/"

F=`df -h`

mail -s "Tick file move to s3 $today" tkaria@gmail.com << E_O_M
    DISK REPORT AFTER MOVE 
    `df -h`
    ------------
    $F
E_O_M
