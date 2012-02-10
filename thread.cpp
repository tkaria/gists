#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <iostream>

boost::mutex io_mutex;

struct count
{
  count(int id) : id(id) { }

  void operator()()
  {
    for (int i = 0; i < 10; ++i)
    {
      boost::mutex::scoped_lock
        lock(io_mutex);
      std::cout << id << ": "
        << i << std::endl;
		sleep(1);
    }
  }
  int id;
};

int main(int argc, char* argv[])
{
  boost::thread thrd1(count(1));
  boost::thread thrd2(count(2));
    //sleep(1);
    //std::cerr << "return start thread2" << std::endl;
  thrd1.join();
  thrd2.join();
  return 0;
}

