#!/bin/sh
#g++ s.cpp -I ../czmq/include/ -L ../czmq/src/.libs/ -l czmq -l zmq  -o srv
g++ s2.cpp -I ../czmq/include/ -l czmq -l zmq  -o srv
