#include <iostream>
#include <cstdio>

int main() {

  // Input consists of the following space-separated values: int, long, long
  // long, char, float, and double, respectively.
  //
  int one;
  long two; 
  long long three;
  char four;
  float five;
  double six;
  scanf("%d %ld %llu %c %f %lf", &one, &two, &three, &four, &five, &six); 

  printf("%d\n%ld\n%llu\n%c\n%f\n%lf\n", one, two, three, four, five, six);

  return 0;
}
