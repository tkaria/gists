#!/bin/sh
# Connects to www.whatismyip.com every 12 hours to get IP address and checks if it has changed

WHO = 'me@mail.com'
output_filename="/tmp/ip_history.txt"
save_up_filename="/tmp/current_ip.txt"
while [ 1 ]
  do IPADR2=$IPADR;
  IPADR=$(wget http://automation.whatismyip.com/n09230945.asp -O - -q)
  echo $IPADR > $save_ip_filename
  dttim=$(date +"%d %b %Y @ %H:%M:%S")
  echo Current IP: $IPADR
  if [ "$IPADR" != "$IPADR2" ]; then
    echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >> $output_filename
    echo ~~~~~ IP Address has changed ... $dttim >> $output_filename
    echo ~~~~~ Our Old IP Address was -- $IPADR2 >> $output_filename
    echo ~~~~~ Our New IP Address is --- $IPADR >> $output_filename
    echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >> $output_filename

    mail -s "IP Changed" tkaria@gmail.com << E_O_M
Good day Master,

  I Regret to Inform You That Our IP Has Changed

  Our Old IP Address was -- $IPADR2
  Our New IP Address is --- $IPADR

  This Occurred Within The Past 12 Hours From -- $dttim

  Our Records Will Need To Be Updated At
     https://my.registrar.com

  Reference: $output_filename
E_O_M

  else
    mail -s "IP UNCHANGED" $WHO << EOM
    No change to up - still $IPADR2
EOM
    echo IP Address is the same ... as of $dttim ... $IPADR  >> $output_filename
  fi
  sleep 43200 # 12h = 43200
done
