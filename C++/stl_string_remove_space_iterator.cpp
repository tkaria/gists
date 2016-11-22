#include <algorithm>
#include <iostream>
#include <string>

int main() {
  int x = 60000000;
  std::cout << x << std::endl;
  std::cout << std::scientific << x << std::endl;

  std::string s("abc def");
  std::cerr << "BEFORE(" << s << ")";
  // s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
  std::string::iterator i = std::remove(s.begin(), s.end(), ' ');
  s.erase(i, s.end());
  // s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
  std::cerr << "AFTER(" << s << ")";
}
