
#include "google/sparsetable"


#include <string>
#include <iostream>
#include <sparsehash/dense_hash_map>
#include <string.h>
#include <set>
#include <map>
#include <utility>

using google::dense_hash_map;      // namespace where class lives by default
using std::cout;
using std::endl;
using std::tr1::hash;  // or __gnu_cxx::hash, or maybe tr1::hash, depending on your OS
using namespace std;

void TestHash();
void TestArray();
void CreateKeys(char** ptr, int num_keys, int key_len);

int 
main(int argc, char** argv)
{
    char* keys;  
    CreateKeys(&keys, atoi(argv[1]), atoi(argv[2]));
//  TestHash();
//  TestArray();
};


struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
  }
};

char
RandAsciiChar()
{
    int min = 'A';
    int max = 'Z';
    double x = rand()/static_cast<double>(RAND_MAX);
    char ch = min + static_cast<char>(x*max - min);
    return ch;
}

void
RandCharArray(char** ptr, int size)
{
    if (!ptr && *ptr) {
        return;
    }
    for(int i = 0; i< size; i++) {
        *ptr[i] = RandAsciiChar();
    }
}

void
CreateKeys(char** ptr, int num_keys, int key_len)
{
    if (!ptr && *ptr) {
        return;
    }
    *ptr = (char*)malloc(num_keys * sizeof(char[key_len + 1]));
    for (int i = 0; i < num_keys; i++) {
        RandCharArray(&(*ptr[i]), key_len);
        &(ptr[i][key_len+1]) = NULL; // null terminate
        fprintf(stderr, "%s\n", *ptr[i]);
    }
}

void
TestHash();
{
  dense_hash_map<const char*, int, hash<const char*>, eqstr> months;
  
  months.set_empty_key(NULL);
  months["ABCDEF"] = 1;
  months["BCDEFG"] = 2;
  months["CDEFGH"] = 3;
  months["DEFGHI"] = 4;
  months["EFGHIJ"] = 5;
  months["june"] = 5;
  months["july"] = 7;
  months["august"] = 8;
  months["september"] = 9;
  months["october"] = 10;
  months["november"] = 11;
  months["december"] = 12;
  months["january"] = 13;


  dense_hash_map<const char*, int, hash<const char*>, eqstr>::iterator it;
  for (it = months.begin(); it != months.end(); it++) {
    cout << it->first << ", " << it->second << "\n";
  }


  cout << "september -> " << months["september"] << endl;
  cout << "april     -> " << months["april"] << endl;
  cout << "june      -> " << months["june"] << endl;
  cout << "november  -> " << months["november"] << endl;


  // Set and map test
   pair<int, int> p1(1, 1);
  pair<int, int> p2(1, 2);
  set< pair<int, int> > s;
  s.insert(p1);
  s.insert(p2);
  map<int, int> m;
  m.insert(p1);
  m.insert(p2);
  cout << "Set size = " << s.size() << "\nMap size = " << m.size() << endl;  
}
