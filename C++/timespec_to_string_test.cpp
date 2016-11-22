#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string>

#define NANOS_PER_SECOND 1000000000
#define TIME_STR_LEN 26 + 1

char *timespec2str(timespec ts, char *buf, size_t buflen) {
  struct tm tm;
  time_t t_secs = ts.tv_sec + (ts.tv_nsec / NANOS_PER_SECOND);
  assert(buf);
  if (buf && (buflen >= TIME_STR_LEN)) {
    return ctime_r(&t_secs, buf);
  } else {
    buf[0] = NULL;
    return buf;
  }
}

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " seconds:nanos" << std::endl;
    return (-1);
  }

  std::string in(argv[1]);

  std::cout << "Read: " << in << std::endl;
  size_t pos = in.find(':');
  if (pos == std::string::npos) {
    std::cerr << "Time string must contain one \':\'" << std::endl;
    return (-1);
  }
  std::string secstr(in, 0, pos);
  std::string nanostr(in, pos + 1, in.size());

  timespec ts;
  ts.tv_sec = atoi(secstr.c_str());
  ts.tv_nsec = atoi(nanostr.c_str());
  printf("Using Seconds: %d, Nanos: %ld\n", ts.tv_sec, ts.tv_nsec);
  char buf[TIME_STR_LEN];
  std::cout << timespec2str(ts, buf, sizeof(buf)) << std::endl;
}
