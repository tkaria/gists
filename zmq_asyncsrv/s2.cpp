//  KTK - modified to use REQ -> ROUTER rather than dealer
//
//  Asynchronous client-to-server (DEALER to ROUTER)
//
//  While this example runs in a single process, that is just to make
//  it easier to start and stop the example. Each task has its own
//  context and conceptually acts as a separate process.

#include "czmq.h"

//  ---------------------------------------------------------------------
//  This is our client task
//  It connects to the server, and then sends a request once per second
//  It collects responses as they arrive, and it prints them out. We will
//  run several client tasks in parallel, each with a different random ID.

static void *
client_task (void *args)
{
    zctx_t *ctx = zctx_new ();
    void *client = zsocket_new (ctx, ZMQ_ROUTER);

    //  Set random identity to make tracing easier
    char identity [10];
    sprintf (identity, "%04X-%04X", randof (0x10000), randof (0x10000));
    zsockopt_set_identity (client, identity);
    zsocket_connect (client, "tcp://localhost:5570");

    int request_nbr = 0;
    while (1) {
        int err = zstr_sendf (client, "request(a) #%d", ++request_nbr);
		fprintf(stderr, "1) ERR WAS %d\n", err);
		if (err == -1) break;
        zmsg_t *msg = zmsg_recv (client);
        err = zstr_sendf (client, "request(b) #%d", ++request_nbr);
		fprintf(stderr, "2) ERR WAS %d\n", err);
		if (err == -1) break;
        msg = zmsg_recv (client);
/*
        zmsg_t *msg = zmsg_recv (client);
        zframe_print (zmsg_last (msg), identity);
		fprintf(stderr, "==> Post recv 1\n");
        zmsg_t *msg = zmsg_recv (client);
        zframe_print (zmsg_last (msg), identity);
		fprintf(stderr, "==> Post recv 2\n");
        zmsg_destroy (&msg);
*/
    }
    zctx_destroy (&ctx);
    return NULL;
}

//  ---------------------------------------------------------------------
//  This is our server task
//  It uses the multithreaded server model to deal requests out to a pool
//  of workers and route replies back to clients. One worker can handle
//  one request at a time but one client can talk to multiple workers at
//  once.

static void server_worker (void *args, zctx_t *ctx, void *pipe);

void *server_task (void *args)
{
    zctx_t *ctx = zctx_new ();

    //  Frontend socket talks to clients over TCP
    void *frontend = zsocket_new (ctx, ZMQ_ROUTER);
    zsocket_bind (frontend, "tcp://*:5570");

    //  Backend socket talks to workers over inproc
    void *backend = zsocket_new (ctx, ZMQ_DEALER);
    zsocket_bind (backend, "inproc://backend");

    //  Launch pool of worker threads, precise number is not critical
    int thread_nbr;
    for (thread_nbr = 0; thread_nbr < 5; thread_nbr++)
        zthread_fork (ctx, server_worker, NULL);

    //  Connect backend to frontend via a queue device
    //  We could do this:
    //      zmq_device (ZMQ_QUEUE, frontend, backend);
    //  But doing it ourselves means we can debug this more easily

    //  Switch messages between frontend and backend
    while (1) {
        zmq_pollitem_t items [] = {
            { frontend, 0, ZMQ_POLLIN, 0 },
            { backend,  0, ZMQ_POLLIN, 0 }
        };
        zmq_poll (items, 2, -1);
        if (items [0].revents & ZMQ_POLLIN) {
            zmsg_t *msg = zmsg_recv (frontend);
            //puts ("Request from client:");
            //zmsg_dump (msg);
            zmsg_send (&msg, backend);
        }
        if (items [1].revents & ZMQ_POLLIN) {
            zmsg_t *msg = zmsg_recv (backend);
            //puts ("Reply from worker:");
            //zmsg_dump (msg);
            zmsg_send (&msg, frontend);
        }
    }
    zctx_destroy (&ctx);
    return NULL;
}

//  Accept a request and reply with the same text a random number of
//  times, with random delays between replies.
//
static void
server_worker (void *args, zctx_t *ctx, void *pipe)
{
    void *worker = zsocket_new (ctx, ZMQ_DEALER);
    zsocket_connect (worker, "inproc://backend");

    while (1) {
        //  The DEALER socket gives us the address envelope and message
        zmsg_t *msg = zmsg_recv (worker);
		zmsg_dump(msg);
        zframe_t *address = zmsg_pop (msg);
        zframe_t *content = zmsg_pop (msg);
        assert (content);
        zmsg_destroy (&msg);

        //  Send 0..4 replies back
        //int reply, replies = randof (5);
        //for (reply = 0; reply < replies; reply++) {
            //  Sleep for some fraction of a second
            //zclock_sleep (randof (1000) + 1);
            zframe_send (&address, worker, ZFRAME_REUSE + ZFRAME_MORE);
            zframe_send (&content, worker, ZFRAME_REUSE);
        //}
        zframe_destroy (&address);
        zframe_destroy (&content);
    }
}

//  This main thread simply starts several clients, and a server, and then
//  waits for the server to finish.
//
int main (void)
{
    zctx_t *ctx = zctx_new ();
    zthread_new (client_task, NULL);
    zthread_new (client_task, NULL);
    zthread_new (client_task, NULL);
    zthread_new (server_task, NULL);

    //  Run for 5 seconds then quit
    zclock_sleep (5 * 1000);
    zctx_destroy (&ctx);
    return 0;
}
