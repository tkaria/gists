// modify flags
#include <iostream>
using namespace std;

int main () {
  cout.setf ( ios::hex, ios::basefield );       // set hex as the basefield
  cout.setf ( ios::showbase );                  // activate showbase
  cout << 100 << endl;
  cout.setf ( 0, ios::showbase );               // deactivate showbase
  cout << 100 << endl;
  return 0;
}
