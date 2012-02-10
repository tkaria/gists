#include "zmqshim.h"
#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to talk to server
    std::cout << "Biatch…\n" << std::endl;
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");

    //  Subscribe to zipcode, default is NYC, 10001
    //const char *filter = (argc > 1)? argv [1]: "10001";
    const char* filter = "T";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));
    //subscriber.setsockopt(ZMQ_SUBSCRIBE, NULL, 0);

    int update_nbr;
    timespec startts, endts;
    clock_gettime(CLOCK_MONOTONIC, &startts);
    printf("Seconds: %d, Nanos: %ld\n", startts.tv_sec, startts.tv_nsec);
    for (update_nbr = 0; update_nbr < 1000000; update_nbr++) {

        zmq::message_t update;

        subscriber.recv(&update);
        char* str = (char*)(update.data());
        std::cerr << str[0] << "\n";
        
    }
    std::cerr << "Received 1e06 msgs\n";
    clock_gettime(CLOCK_MONOTONIC, &endts);
    printf("Seconds: %d, Nanos: %ld\n", endts.tv_sec, endts.tv_nsec);
    if (startts.tv_sec == endts.tv_sec) {
        printf("ns diff = %d", endts.tv_nsec = startts.tv_nsec);
    }

    return 0;
}
