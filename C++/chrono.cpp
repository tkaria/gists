#include "chrono_io"
#include <chrono>
#include <iostream>

int main() {
  typedef std::chrono::high_resolution_clock Clock;
  auto t1 = Clock::now();
  auto t2 = Clock::now();
  std::cout << t2 - t1 << '\n';
}
