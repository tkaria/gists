#!/bin/bash

if test "`id -u`" -ne 0
    then
    echo "Install must be run as root"
    exit
fi

echo "This will install system_kr - enter 'y' to continue"
read RESPONSE
if [ "$RESPONSE" != "y" ] #and "$RESPONSE" != "Y" ]
then
    echo "Exiting"
    exit 1
fi


INSTALLDIR="/usr/local/capk"

if [ "$1" == "" ]
then
    echo "Using default installation directory: '$INSTALLDIR'"
else 
    INSTALLDIR=$1
fi

echo
echo "Using installation directory: '$INSTALLDIR'"
echo

echo "Installing ..."

if [ -d $INSTALLDIR ] 
then
    echo "Installation directory '$INSTALLDIR' exists"
fi

    install -d $INSTALLDIR/bin

    MARKET_DATA=$INSTALLDIR/market_data
    install -d $MARKET_DATA
    install -d $MARKET_DATA/cfg
    install -d $MARKET_DATA/spec

    ORDER_ENTRY=$INSTALLDIR/order_entry
    install -d $ORDER_ENTRY
    install -d $ORDER_ENTRY/cfg
    install -d $ORDER_ENTRY/spec

    SCRIPTS=$INSTALLDIR/scripts
    install -d $SCRIPTS

    CONFIGURATION_SERVER=$INSTALLDIR/configuration_server
    install -d $CONFIGURATION_SERVER
    install -d $CONFIGURATION_SERVER/proto_objs

    TRADE_SERIALIZER=$INSTALLDIR/trade_serializer
    install -d $TRADE_SERIALIZER
    
    AGGREGATED_BOOK=$INSTALLDIR/aggregated_book
    install -d $AGGREGATED_BOOK
#fi

# Install market data components
echo "Installing market data components to: $MARKET_DATA"
install -p ./system_kr/market_data/collect-fix/collect $MARKET_DATA
install -p ./system_kr/market_data/collect-fix/*.sh $MARKET_DATA
install -t $MARKET_DATA/cfg ./system_kr/market_data/collect-fix/cfg/*
install -t $MARKET_DATA/spec ./system_kr/market_data/collect-fix/spec/*

# Install scripts (cron, s3, etc)
install -t $SCRIPTS ./common/scripts/*

# Install order entry components
echo "Installing order entry components to: $MARKET_DATA"
install -p ./system_kr/order_entry/order-fix/order-fix $ORDER_ENTRY
#install -p ./system_kr/order_entry/order-fix/*.sh $ORDER_ENTRY
install -t $ORDER_ENTRY/cfg ./system_kr/market_data/collect-fix/cfg/*
install -t $ORDER_ENTRY/spec ./system_kr/market_data/collect-fix/spec/*

# Install trade serializer
install -p ./system_kr/trade_serializer/trade_serializer $TRADE_SERIALIZER

# Install configuration server
install -p ./system_kr/configuration_server/configuration_server.py $CONFIGURATION_SERVER
install -p ./system_kr/configuration_server/*.cfg $CONFIGURATION_SERVER
install -d $INSTALLDIR/configuration_server/proto_objs && install -p ./system_kr/configuration_server/proto_objs/* $CONFIGURATION_SERVER/proto_objs/ 

# Create symlinks
install -d $INSTALLDIR/bin
ln -s $MARKET_DATA/collect $INSTALLDIR/bin/collect 
