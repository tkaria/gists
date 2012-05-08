#!/bin/bash
g++ -std=c++0x -O3 hashId.cpp  ../../collectors/utils/KTimeUtils.cpp -I../ -I../../collectors/utils -I/usr/local/boost -L ../../collectors/utils/ -L/usr/local/src/quickfix/lib -L/usr/local/boost/stage/lib  -lquickfix -lrt  -lboost_date_time -o hashId
