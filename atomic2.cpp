
#include <boost/atomic.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread.hpp>
#include <assert.h>
#include <iostream>
 
//std::atomic<bool> x,y;
//std::atomic<int> z;
 
boost::atomic<int> ai;
boost::atomic<int> i;
boost::mutex m;
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

void plus_one()
{
	while (i < 1000000) {
		ai.fetch_add(1, boost::memory_order_consume);
		//fprintf(stderr, "%d\n", ai);
		//m.lock();
		//std::cerr << ai << "(" << boost::this_thread::get_id() << ")" << std::endl;
		//std::cout  << "(" << boost::this_thread::get_id() << ")" << std::endl;
		//m.unlock();
		i++;
	}
}

int main()
{
	boost::thread a(plus_one);
	//m.lock(); std::cout << "Thread a: " << a.get_id() << std::endl; m.unlock();
	boost::thread b(plus_one);
	//m.lock(); std::cout << "Thread b: " << b.get_id() << std::endl; m.unlock();
	boost::thread c(plus_one);
	//m.lock(); std::cout << "Thread c: " << c.get_id() << std::endl; m.unlock();
	boost::thread d(plus_one);
	//m.lock(); std::cout << "Thread d: " << d.get_id() << std::endl; m.unlock();
	boost::thread e(plus_one);
	//m.lock(); std::cout << "Thread e: " << e.get_id() << std::endl; m.unlock();
	boost::thread f(plus_one);
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
