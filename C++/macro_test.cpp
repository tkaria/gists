
#include <iostream>
#include <string>

#define IF_DBG(x, y)                                                           \
  if (dbg) {                                                                   \
    x                                                                          \
  } else {                                                                     \
    y                                                                          \
  }

int main(int argc, char **argv) {

  bool dbg = true;
  std::cout << "Enter" << std::endl;
  IF_DBG(std::cout << "In debug mode" << std::endl;
         , std::cout << "NOT in debug" << std::endl;)
  IF_DBG(std::cout << "In debug mode" << std::endl;, )

  std::cout << "Exit" << std::endl;
}
