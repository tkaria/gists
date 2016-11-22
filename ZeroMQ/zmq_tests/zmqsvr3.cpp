//
//  Weather update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
//
#include "zmqshim.h"
#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main () {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");
    publisher.bind("ipc://weather.ipc");

    while (1) {

        //  Send message to all subscribers
        zmq::message_t message(2);
        snprintf ((char *) message.data(), 2 , "%c0x0", 'T');
        publisher.send(message);

    }
    return 0;
}
