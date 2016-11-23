#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <limits>

// Test case 16 should be 262142
// Test case 19 should be 65535


pair<int, int> findMin(vector<int> a) {
  int min = std::numeric_limits<int>::max();
  int min2 = std::numeric_limits<int>::max();
  for (int j = 0; j< a.size(); j++) {
    //cout << "C1: " << a[j] << "<min(" << min << ") <min2(" << min2 << endl;
    if (a[j] < min) {
      //cout << "Swapping min and min2" << endl;
      min2 = min;
      min = a[j];
    }
    //cout << "C2: " << a[j] << "<min2(" << min2 << ") <min(" << min << endl;
    if (a[j] < min2 && a[j] > min) {
      //cout << "Assigning min2" << endl;
      min2 = a[j];
    }
  }
  return make_pair(min, min2);
}

void s(vector<int> a) {
  pair<int, int>  mins = findMin(a);
  int  min = mins.first;
  int  min2 = mins.second;
  //cout << "Mins: (" << min << ", " <<  min2 << ")" << endl;
  int  Si = (((min & min2) ^ (min | min2)) &  (min ^ min2));
  //cout << "Si for mins: " << Si << endl;
  cout << Si << endl;

}

void s2(vector<long long> a) {
   long long maxSi = std::numeric_limits<long long>::min();
   long long  min; 
   long long  min2;
   long long tmp;
   for (int j = 0; j< a.size()-1; j++) {
     min = a[j];
     min2 = a[j+1];
     /*
     if (a[j+1] < a[j]) {
       min = a[j+1];
       min2 = a[j];
     }
     */
     //long long Si = (((min & min2) ^ (min | min2)) & (min ^ min2));
     long long Si = min ^ min2;
     //int Si = (((a[j] & a[j+1]) ^ (a[j] | a[j+1])) &  (a[j] ^ a[j+1]));
     if (Si > maxSi) {
       maxSi = Si;
     }
   }
   //return maxSi;
   cout << maxSi << endl;
}



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int alen = 0;
    vector<long long> a;
    cin >> alen;
    //cout << "Reading " << alen << " items" << endl;
    for (int i = 0; i<alen; i++) {
      int k;
      cin >> k;
      //cout << "Read: " << k << endl;
      a.push_back(k);
    }  

    //s(a);
    s2(a);
    /*
    for (int j = 0; j< a.size(); j++) {
      cout << a[j] << ' ';
    }
    */
    
    return 0;
}

