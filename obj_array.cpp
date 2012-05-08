
#include <iostream>
#include <boost/thread.hpp>

class foo 
{
	public:

	foo(int x):_x(x) {
		std::cerr << "foo::foo(" << _x << ")" << std::endl;
	}

	void
	run() {
		while (1) {
			sleep(1);
			std::cerr << _x << std::endl;
		}
	}

	private:

		int _x;
};


int 
main()
{
	foo* af[3];	
	boost::thread_group tg;
	tg.create_thread(boost::bind(&foo::run, new foo(22)));
	tg.join_all();
}
