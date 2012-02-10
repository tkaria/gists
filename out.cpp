
//#include <chrono>
#include <iostream>
#include <fstream>

//#include <sys/time.h>
#include <stdio.h>
#include <time.h>
//#include <linux/time.h>

//#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

using namespace boost::posix_time;
//using namespace boost::gregorian;

std::ofstream logfile;


int 
main(int argc, char** argv)
{
    logfile.open("out.log", std::ios::out | std::ios::app);
    ptime time_start(microsec_clock::local_time());
#define THREE 1
    //... execution goes here ...
    for (int i = 0; i< 1000000; i++) {
#ifdef ONE
        logfile << "01234567890123456789012345678901234567890123456789\n"; 
#endif
        //printf("%s", "01234567890123456789012345678901234567890123456789\n");
#ifdef TWO
        logfile << "0";
        logfile << "1";
        logfile << "2";
        logfile << "3";
        logfile << "4";
        logfile << "5";
        logfile << "6";
        logfile << "7";
        logfile << "8";
        logfile << "9";
        logfile << "0";
        logfile << "1";
        logfile << "2";
        logfile << "3";
        logfile << "4";
        logfile << "5";
        logfile << "6";
        logfile << "7";
        logfile << "8";
        logfile << "9";
        logfile << "0";
        logfile << "1";
        logfile << "2";
        logfile << "3";
        logfile << "4";
        logfile << "5";
        logfile << "6";
        logfile << "7";
        logfile << "8";
        logfile << "9";
        logfile << "0";
        logfile << "1";
        logfile << "2";
        logfile << "3";
        logfile << "4";
        logfile << "5";
        logfile << "6";
        logfile << "7";
        logfile << "8";
        logfile << "9";
        logfile << "0";
        logfile << "1";
        logfile << "2";
        logfile << "3";
        logfile << "4";
        logfile << "5";
        logfile << "6";
        logfile << "7";
        logfile << "8";
        logfile << "9";
#endif
#ifdef THREE
        logfile << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "0" << "1" << "2" << "3"  << "4" << "5" << "6" << "7" << "8" << "9" << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
#endif
    } 
 
   
    ptime time_end(microsec_clock::local_time());
    time_duration duration(time_end - time_start);
    std::cout << duration << '\n';


    return 0;

}
