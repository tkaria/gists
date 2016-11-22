
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

using namespace boost::posix_time;

int main(int argc, char **argv) {
  ptime time_start(microsec_clock::local_time());
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  printf("Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);

  ptime now = second_clock::universal_time();
  std::cout << "Current Time is: " << to_iso_extended_string(now) << std::endl;
  ptime now_2 = microsec_clock::universal_time();
  std::cout << "Current Time is: " << to_iso_extended_string(now_2)
            << std::endl;

  // VALID ISO STRING
  std::string iso("20110330T202304020555");
  ptime t(from_iso_string(iso));
  std::string out_iso = to_simple_string(t);
  std::cout << "TIME FROM ISO STRING: \t\t" << out_iso << std::endl;

  // VALID
  std::string stringtime("2011-03-30 20:11:06.12345678");
  // FROM FIX LOGS - doesn't work - INVALID
  // std::string tt("20110330-20:23:04.020");
  // std::string tstring(time_from_string(tt));
  ptime t2(time_from_string(stringtime));

  std::string out_time = to_simple_string(t2);
  std::cout << "TIME FROM STRING: \t\t" << out_time << std::endl;

  //... execution goes here ...
  ptime time_end(microsec_clock::local_time());
  time_duration duration(time_end - time_start);
  std::cout << duration << '\n';

  return 0;
}
