#include <assert.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <uuid/uuid.h>

using namespace boost::posix_time;
int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <num_iterations>" << std::endl;
    return -1;
  }

  int iterations = atoi(argv[1]);
  timespec ts;
  char buf[37];

  ptime time_start(microsec_clock::local_time());
  // clock_gettime(CLOCK_MONOTONIC, &ts);
  // printf("1) Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
  for (int i = 0; i < iterations; i++) {
    uuid_t u1;
    uuid_generate(u1);
    // uuid_unparse(u1, buf);
    // buf[36] = 0;
  }
  // clock_gettime(CLOCK_MONOTONIC, &ts);
  // printf("2) Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
  ptime time_end(microsec_clock::local_time());
  time_duration duration(time_end - time_start);
  std::cout << "Duration: " << duration << std::endl;

  time_start = microsec_clock::local_time();
  // clock_gettime(CLOCK_MONOTONIC, &ts);
  // printf("3) econds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
  for (int i = 0; i < iterations; i++) {
    uuid_t u2;
    uuid_generate_random(u2);
    // uuid_unparse(u2, buf);
    // buf[36] = 0;
  }
  // clock_gettime(CLOCK_MONOTONIC, &ts);
  // printf("4) Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
  time_end = microsec_clock::local_time();
  duration = time_end - time_start;
  std::cout << "Duration: " << duration << std::endl;
}
