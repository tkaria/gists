/**
 * Build string: g++ -I /opt/src  msync.cpp  -o msync -lgtest -lpthread -lrt
 * -lboost_date_time -ggdb
 */

#include <gtest/gtest.h>

#include "boost/date_time/posix_time/posix_time.hpp"
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_CHAR_WRITE 1024 * 1024 * 50

using namespace boost::posix_time;

TEST(WriteTest, TestFwrite) {
  FILE *fp = fopen("./fopen.txt", "w+");
  ASSERT_TRUE(fp != NULL);
  unsigned int seed = time(0);
  ptime start(microsec_clock::local_time());
  char c;
  for (int i = 0; i < MAX_CHAR_WRITE; i++) {
    c = (rand_r(&seed) % (255 - 33) + 33);
    fwrite(&c, sizeof(char), 1, fp);
  }
  ptime stop(microsec_clock::local_time());
  time_duration duration(stop - start);
  std::cout << "TIME: " << to_simple_string(duration) << std::endl;
}

TEST(WriteTest, TestMsync) {
  int result;
  size_t len = MAX_CHAR_WRITE;
  unsigned int seed = time(0);
  int fd = open("./msync.mem", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd == 0) {
    fprintf(stderr, "Can't open memmap file");
    ASSERT_TRUE(0);
  }
  if (lseek(fd, len - 1, SEEK_SET) == -1) {
    perror("Seek failed");
    ASSERT_TRUE(0);
  }
  result = write(fd, "", 1);
  if (result != 1) {
    perror("Write failed");
  }
  char *map =
      (char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    close(fd);
    perror("Error mapping file");
    exit(-1);
  }
  assert(map);
  ptime start(microsec_clock::local_time());
  for (int i = 0; i < len - 1; i++) {
    map[i] = (rand_r(&seed) % (255 - 33) + 33);
  }
  msync(map, MAX_CHAR_WRITE, MS_SYNC | MS_INVALIDATE);
  ptime stop(microsec_clock::local_time());
  if (munmap(map, MAX_CHAR_WRITE) == -1) {
    perror("munmap");
  }
  time_duration duration(stop - start);
  std::cout << "TIME: " << to_simple_string(duration) << std::endl;
}

TEST(WriteTest, TestIostream) {
  unsigned int seed = time(0);
  std::ofstream *f =
      new std::ofstream("iostream.txt", std::ios::binary | std::ios::out);
  if (!f) {
    fprintf(stderr, "ofstream failed");
  }
  ptime start(microsec_clock::local_time());
  for (int i = 0; i < MAX_CHAR_WRITE; i++) {
    char c = (rand_r(&seed) % (255 - 33) + 33);
    *f << c;
  }
  ptime stop(microsec_clock::local_time());
  time_duration duration(stop - start);
  std::cout << "TIME: " << to_simple_string(duration) << std::endl;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
}
