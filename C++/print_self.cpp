#include <iostream.h>
#include <stdio.h>
#include <string>
#define Q(x) #x
// This is a C++ program to print its own source code based on
// the recursion theorem in Sipser's book _Theory_Of_Computation_.
// This program was compiled and tested on LINUX 6.0 with egcs-2.91.66.
// Permission is granted to copy, modify, and distribute provided
// this comment is maintained at the top.  Emin Martinian, 10/2000.
const char *const MakeProgramToPrintString(const char *const s) {
  char quote[2];
  char newline[2];
  sprintf(quote, Q(% c), 34);
  sprintf(newline, Q(% c), 10);
  quote[1] = 0;
  newline[1] = 0;
  string prog(Q());
  prog = prog + Q(int main() {) + newline;
           prog = prog + Q(string tape;) + newline;
           prog = prog + Q(tape = tape +) + quote + s + quote + Q(;) + newline;
           prog = prog + Q(DoPartB(tape.c_str());) + newline;
  prog = prog + Q(return 0;) + newline + Q(
         }) +
         newline;
  return prog.c_str();
}

void DoPartB(const char *const s) { cout << s << MakeProgramToPrintString(s); }

int main() {
  string tape;
  tape = tape +
         "#include <iostream.h>
#include <stdio.h>
#include <string>
#define Q(x) #x
             // This is a C++ program to print its own source code based on
             // the recursion theorem in Sipser's book _Theory_Of_Computation_.
             // This program was compiled and tested on LINUX 6.0 with
             // egcs-2.91.66.
             // Permission is granted to copy, modify, and distribute provided
             // this comment is maintained at the top.  Emin Martinian, 10/2000.
             const char *
             const MakeProgramToPrintString(const char *const s) {
    char quote[2];
    char newline[2];
    sprintf(quote, Q(% c), 34);
    sprintf(newline, Q(% c), 10);
    quote[1] = 0;
    newline[1] = 0;
    string prog(Q());
    prog = prog + Q(int main() {) + newline;
             prog = prog + Q(string tape;) + newline;
             prog =
                 prog + Q(tape = tape +) + quote + s + quote + Q(;) + newline;
             prog = prog + Q(DoPartB(tape.c_str());) + newline;
  prog = prog + Q(return 0;) + newline + Q(
           }) +
           newline;
    return prog.c_str();
  }

  void DoPartB(const char *const s) {
    cout << s << MakeProgramToPrintString(s);
  }

  ";
      DoPartB(tape.c_str());
  return 0;
}
