CC=g++

INCLUDE=-I/usr/local/boost/ -I/usr/local/include/ -I../capitalk/src/quickfix/ -I/home/timir/capitalk/src/quickfix/include/quickfix -I./boost-log-1.0

#-I../src/dataCollector.baxter -I./boost-log-1.0
LIBS=-L../src/quickfix/lib -L/usr/local/boost_1_45_0/stage/lib/ -lquickfix -lboost_date_time -lboost_thread -lboost_date_time -lrt
CFLAGS=-Wall  -std=c++0x -g -pthread -D DEBUG_BOOK
SRC=../src/dataCollector.baxter

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(input) -o $(output)

test : test.o
	$(CC) -o $@ $^  

test.o: test.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

time : time.o
	$(CC) $(LIBS) -o $@ $^  

time.o: time.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

vec : vec.o
	$(CC) -o $@ $^  

vec.o: vec.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

scope : scope.o
	$(CC) -o $@ $^  

scope.o: scope.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

book : book.o KPriceDepthOrderBook.o KOrderBook.o 
	$(CC) $(LIBS) -o $@ $^  

book.o: book.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

replay.o: replay.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

replay: replay.o
	$(CC) $(LIBS) -o $@ $^

KPriceDepthOrderBook.o: KPriceDepthOrderBook.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

KOrderBook.o: KOrderBook.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

foreach: foreach.o
	$(CC) $(LIBS) -o $@ $^

foreach.o: foreach.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

date : date.o
	$(CC) $(LIBS) -o $@ $^  

date.o: date.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

thread: thread.o
	$(CC) $(LIBS) -o $@ $^

thread.o: thread.cpp 
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

ptr: ptr.o
	$(CC) $(LIBS) -o $@ $^

ptr.o: ptr.cpp
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

#book : book.o 
clean :
	rm -f *.o scope vec test book date replay scope foreach date thread time macro 

