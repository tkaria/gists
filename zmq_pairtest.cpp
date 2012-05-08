
#include <iostream>
#include <string>
#include <exception>

#include <stdio.h>

#include <boost/program_options.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

#include <zmq.hpp>


class book_manager
{
    public: 
        book_manager(zmq::context_t* context, const std::string& connectAddr): 
                _context(context), 
                _connectAddr(connectAddr), 
                _stopRequested(false) {};
        void run();
        void stop(); 
    private: 
        zmq::context_t* _context;
        std::string _connectAddr;
        volatile bool _stopRequested;
};

void 
book_manager::stop() {
    _stopRequested = true;
}

void 
book_manager::run() {
    try {
        zmq::socket_t receiver(*_context, ZMQ_PULL); 
        receiver.bind(_connectAddr.c_str());
        fprintf(stdout, "book_manager: connect address: %s\n", _connectAddr.c_str());
        fprintf(stdout, "book_manager: stop requested: %d\n", _stopRequested);

        while (1 && _stopRequested == false) {
            zmq::message_t msg;
            receiver.recv(&msg);
        }
    }
    catch (std::exception& e) {
        std::cerr << "EXCEPTION: " << __FILE__ << __LINE__ << e.what();
    }
}

class worker
{   
    public:
        worker(zmq::context_t* context, const std::string& connectAddr, const std::string& inprocAddr): _context(context), _connectAddr(connectAddr), _inprocAddr(inprocAddr),  _stopRequested(false) {};
        void run();
        void stop();
        ~worker();
 
    private:
        zmq::context_t* _context;
        std::string _connectAddr;
        std::string _inprocAddr;
        zmq::socket_t* _inproc;
        volatile bool _stopRequested;
        
};

worker::~worker() {
    if (_inproc) delete _inproc;
}

void 
worker::stop() {
    _stopRequested = true;
}

void
worker::run () {
    try {
        assert(_context != NULL);
        
        _inproc = new zmq::socket_t(*_context, ZMQ_PUSH);
        assert(_inproc);
        _inproc->connect(_inprocAddr.c_str());
        fprintf(stdout, "worker: inproc address: %s\n",  _inprocAddr.c_str());
    } 
    catch (std::exception& e) {
        std::cerr << "EXCEPTION: " << __FILE__ << __LINE__ << e.what();
    }
}


const std::string AGGREGATE_OB = "inproc://ob";
int 
main(int argc, char** argv)
{

    try { 
		// Global context for ZMQ
		zmq::context_t context(1);
		
        // connect to inproc socket for orderbook
        book_manager ob(&context, AGGREGATE_OB);
        boost::thread* t0 = new boost::thread(boost::bind(&book_manager::run, &ob));
		sleep(2);
        // subscribers
        worker w1(&context, "", AGGREGATE_OB);
        worker w2(&context, "", AGGREGATE_OB);
        worker w3(&context, "", AGGREGATE_OB);
        boost::thread* t1 = new boost::thread(boost::bind(&worker::run, &w1));
        boost::thread* t2 = new boost::thread(boost::bind(&worker::run, &w2));
        boost::thread* t3 = new boost::thread(boost::bind(&worker::run, &w3));
        t0->join();
        t1->join();
        t2->join();
        t3->join();
    } 
    catch(std::exception& e) {
        std::cerr << "EXCEPTION: " << __FILE__ << __LINE__ << e.what();
        return (-1);
    }
}
