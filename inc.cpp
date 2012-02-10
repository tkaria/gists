#include <stdint.h>
#include <boost/date_time/posix_time/posix_time.hpp>
int main()
{
    using namespace boost::posix_time;
    ptime time_start(microsec_clock::local_time());
    int64_t x, y;  
    x = y = 0;
    for (int x = 0; x < 500*1000000; x++) {
        y++;
    }
    ptime time_end(microsec_clock::local_time());
    time_duration duration(time_end - time_start);
    std::cout << duration << '\n';
}
