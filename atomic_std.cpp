#include <cstdatomic>
#include <boost/atomic.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread.hpp>
#include <assert.h>
#include <iostream>
 
//std::atomic<bool> x,y;
//std::atomic<int> z;
int x; 
boost::atomic<int> ai;
boost::atomic<int> i;
boost::mutex m;

std::atomic<int> stdx;

std::atomic<int> ai2;

std::atomic<double> ad;

/*
void write_x()
{
    x.store(true,std::memory_order_seq_cst);     
}
 
void write_y()
{
    y.store(true,std::memory_order_seq_cst);   
}
 
void read_x_then_y()
{
    while(!x.load(std::memory_order_seq_cst));
    if(y.load(std::memory_order_seq_cst))     
        ++z;
}
 
void read_y_then_x()
{
    while(!y.load(std::memory_order_seq_cst));
    if(x.load(std::memory_order_seq_cst))   
        ++z;
}
 
*/

void no_lock()
{
	while (i < 1000000) {
		x++;
		m.lock();
		std::cout  << "(" << boost::this_thread::get_id() << ") " << x << std::endl;
		m.unlock();
		i++;
	}
}

void with_mutex()
{
	while (x < 1000000) {
		m.lock();
		x++;
		std::cout  << "(" << boost::this_thread::get_id() << ") " << x << std::endl;
		m.unlock();
	}
}

void with_atomic2()
{
	while (ai < 1000000) {
		ai2.fetch_add(1);
		m.lock();
		std::cout  << "(" << boost::this_thread::get_id() << ") " << ai2.load() << std::endl;
		m.unlock();
	}
}


void with_atomic()
{
	while (ai < 1000000) {
		//ai.fetch_add(1);//, boost::memory_order_consume);
		ai.fetch_add(1, boost::memory_order_consume);
		m.lock();
		std::cout  << "(" << boost::this_thread::get_id() << ") " << ai << std::endl;
		m.unlock();
	}
}

int main()
{
	boost::thread a(with_atomic2);
	//m.lock(); std::cout << "Thread a: " << a.get_id() << std::endl; m.unlock();
	boost::thread b(with_atomic2);
	//m.lock(); std::cout << "Thread b: " << b.get_id() << std::endl; m.unlock();
	boost::thread c(with_atomic2);
	//m.lock(); std::cout << "Thread c: " << c.get_id() << std::endl; m.unlock();
	boost::thread d(with_atomic2);
	//m.lock(); std::cout << "Thread d: " << d.get_id() << std::endl; m.unlock();
	boost::thread e(with_atomic2);
	//m.lock(); std::cout << "Thread e: " << e.get_id() << std::endl; m.unlock();
	boost::thread f(with_atomic2);
	//m.lock(); std::cout << "Thread f: " << f.get_id() << std::endl; m.unlock();

	a.join();
	b.join();
	c.join();
	d.join();
	e.join();
	f.join();
	std::cout << "Done" << std::endl;
/*
    x=false;
    y=false;
    z=0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load()!=0);                   
*/
}
