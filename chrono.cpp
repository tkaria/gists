#include <iostream>
#include <chrono>
#include "chrono_io"

int main()
{
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    auto t2 = Clock::now();
    std::cout << t2-t1 << '\n';
}
