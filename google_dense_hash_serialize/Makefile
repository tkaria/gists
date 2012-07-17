CC=g++

INCLUDE=-I/usr/local/boost/ \
		-I/usr/local/include/ -I. \
        -I/usr/local/src/quickfix/include \
		-I.. \
		-I../../collectors/ \
		-I $(PANTHEIOS_ROOT)/include \
		-I $(STLSOFT)/include 

LIBS= -L/usr/local/src/quickfix/lib/ \
		-L/usr/local/lib \
      	-lquickfix \
		-lboost_date_time \
		-lboost_program_options \
		-lgtest \
		-lzmq \
		-lprotobuf \
		-lrt \
		-lboost_thread

UTILS=../../collectors/utils

CFLAGS=-Wall -std=c++0x -pthread -O3 -DLOG

dbg = 1

ifeq ($(dbg),1)
        CFLAGS = -Wall -std=c++0x -pthread -DDEBUG -ggdb -g  -DLOG
endif

LDFLAGS=-static

all: serialize_cache_test

#.cpp.o:
	#$(CC) $(CFLAGS) -c $(.IMPSRC)

main: main.o
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@
main2: main2.o
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@

serialize_cache_test.o: serialize_cache_test.cpp
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

JenkinsHash.o: JenkinsHash.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

serialize_cache_test: serialize_cache_test.o JenkinsHash.o
	$(CC) $(CFLAGS) serialize_cache_test.o JenkinsHash.o $(LIBS) $(PANTHEIOS_LIBS) -o $@ 

clean :
	rm -f *.o main main2 serialize_cache_test
	rm -f hashtable.data

