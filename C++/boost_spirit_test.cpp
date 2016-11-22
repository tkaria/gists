#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::spirit;

typedef void (*void_func)(int);
void measure_time(const char *str, void_func func, int number_of_repeat) {
    using namespace boost::posix_time;
    ptime tStart = microsec_clock::local_time();
    (*func)(number_of_repeat);
    ptime tEnd = microsec_clock::local_time();
    time_duration tVal = tEnd - tStart;
    std::cout << str << " (" << number_of_repeat << " rep): " << to_simple_string(tVal)  << std::endl;
}

const char* nstr="123456";
const char* const nstr2="123456";

void test_spirit(int number_of_repeat) {
    int val=0;
    for(int i=0; i < number_of_repeat; i++) {
        qi::parse(nstr,nstr+6,int_,val);
        if (val != 123456)
            std::cout << "Spirit Errror! val=" << val << std::endl;
    }
}

void test_atol(int number_of_repeat) {
    long val=0;
    for(int i=0; i < number_of_repeat; i++) {
        val=atoi(nstr2);
        if (val != 123456)
            std::cout << "Atoi Errror! val=" << val << std::endl;
    }
}

int main(int argc, char **argv) {
    measure_time("atol   =", test_atol, 10000000);
    measure_time("spirit =", test_spirit, 10000000);
    return 0;
}
