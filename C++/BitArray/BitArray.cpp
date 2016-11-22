#include <cstdio>
int main() {
  unsigned int mask = 0x00000001;
  unsigned int x = 0xFFFFFFFF;
  for (int i = 0; i< 32; i++) {
    printf("%d", x && mask);
    mask <<= 1;
  }
}
