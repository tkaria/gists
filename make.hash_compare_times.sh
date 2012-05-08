#!/bin/bash
g++ -std=c++0x -O3 hash_compare_times.cpp MurmurHash3.cpp spooky.cpp city.cc JenkinsHash.cpp ../../collectors/utils/KTimeUtils.cpp -I. -I../ -I../../collectors/utils -I/usr/local/boost -L ../../collectors/utils/ -L/usr/local/src/quickfix/lib -L/usr/local/boost/stage/lib  -lquickfix -lrt  -luuid -lboost_date_time -o hash_times
