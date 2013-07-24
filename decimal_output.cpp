#include <iostream>
#include <iomanip>


int main(int argv, char** argc)
{
  double price = 1.12350;

  std::cout << "No formatting:   " << price << std::endl;

  std::cout << std::setprecision(5);
  std::cout << "setprecision(5): " << price << std::endl;
  std::cout.unsetf(std::ios::fixed);

  std::cout << std::setprecision(6);
  std::cout << "setprecision(6): " << price << std::endl;
  std::cout.unsetf(std::ios::fixed);

  std::cout << std::setprecision(5);
  std::cout << std::setiosflags(std::ios_base::fixed);
  std::cout << "setprecision(5)&& setiosflags(std::ios_base::fixed): " << price << std::endl;
  std::cout.unsetf(std::ios::fixed);

}
