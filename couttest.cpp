#include <iostream>
#include <iomanip>
#include <time.h>

std::ostream& operator<<(std::ostream& out, const timespec& ts) {
//   out << ts.tv_sec << ":" << ts.tv_nsec;
    out << std::setfill('0') << std::setprecision(9);
    out << ts.tv_sec << ":" << std::setw(9) << ts.tv_nsec;
    return out;
}

int main(int argc, char** argv) {
  timespec ts;
  ts.tv_sec = 19192920292;
  ts.tv_nsec = 9000;
  //for (int i=0; i<10000000; i++) {
    //clock_gettime(CLOCK_MONOTONIC, &ts);
    std::cout << ts << std::endl;
  //}

}

