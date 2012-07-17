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

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
  }
};

int main()
{
  dense_hash_map<const char*, int, hash<const char*>, eqstr> months;
  
  months.set_empty_key(NULL);
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  months["january"] = 99;
  

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
