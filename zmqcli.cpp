//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

#include <stdio.h>
#include <time.h>
#define NUM_REQUESTS 1000000

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    printf("Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
    //std::cerr << ts
    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != NUM_REQUESTS; request_nbr++) {
        zmq::message_t request (6);
        memcpy ((void *) request.data (), "Hello", 5);
        //std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        //std::cout << "Received World " << request_nbr << std::endl;
    }
    clock_gettime(CLOCK_MONOTONIC, &ts);
    //std::cerr << ts;
    printf("Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
    return 0;
}


