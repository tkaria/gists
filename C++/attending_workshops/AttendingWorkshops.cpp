#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/***********************************************************************/
struct Workshop {
  int start_time;
  int duration;
  int end_time;
};

struct Available_Workshops {
  int n;
  Workshop* workshops;
  Available_Workshops(int n) {
    //workshops = malloc(sizeof(struct Workshop) * n);    
    workshops = new struct Workshop[n];    
  }
};

Available_Workshops* initialize(int start_time[], int duration[], int n) {
  Available_Workshops* a = new Available_Workshops(n);
  a->n = n;
  for (int i = 0; i<n; i++) {
    a->workshops[i].start_time = start_time[i];
    a->workshops[i].duration = duration[i];
    a->workshops[i].end_time = start_time[i] + duration[i];
  }
  return a;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    int num = 0;
    int min_end; 
    int count = ptr->n;
    int min_index = -1;
    while (count > 0) {
    min_end = 10000000; 
    for (int i = 0; i < ptr->n; i++) {
      // find the mind end_time
      cout << "Inspecting: " << ptr->workshops[i].end_time << " with min_end = " << min_end << endl;
      if (ptr->workshops[i].end_time >= 0 && 
          ptr->workshops[i].end_time < min_end) {
        min_end = ptr->workshops[i].end_time;
        min_index = i;
        //cout << "Setting new min: " << min_end << " with index = " << min_index << endl;
      }
    }
    cout << "Found min end_time: " << min_end << " at " << min_index << endl;
    // "remove" item with min end_time
    ptr->workshops[min_index].end_time = -1;
    count --;
    num++;
    cout << "Num so far: " << num << endl;
    for (int j = 0; j < ptr->n; j++) {
      // remove overlapping intervals
      cout << "Min index: " << min_index << endl;
      cout << "Looking for removals - j: (" << ptr->workshops[j].start_time << "," << ptr->workshops[j].end_time << ")" << 
          " against (" <<  ptr->workshops[min_index].start_time << "," << ptr->workshops[min_index].start_time + ptr->workshops[min_index].duration << ")" << endl;
      if (ptr->workshops[j].end_time >= 0 &&
          // i.e. item j ends in the middle of min
          ((ptr->workshops[j].end_time > ptr->workshops[min_index].start_time && 
           ptr->workshops[j].end_time < ptr->workshops[min_index].start_time + ptr->workshops[min_index].duration) 
           ||
          // i.e. item j starts in the middle of min
          (ptr->workshops[j].start_time > ptr->workshops[min_index].start_time &&
           ptr->workshops[j].start_time < ptr->workshops[min_index].start_time + ptr->workshops[min_index].duration) 
           || 
          // i.e. item j overlaps min entirely
          (ptr->workshops[j].start_time <= ptr->workshops[min_index].start_time &&
           ptr->workshops[j].end_time >= ptr->workshops[min_index].start_time + ptr->workshops[min_index].duration)
           || 
          // i.e. item j fits inside min item entirely
          (ptr->workshops[j].start_time > ptr->workshops[min_index].start_time &&
           ptr->workshops[j].end_time < ptr->workshops[min_index].start_time + ptr->workshops[min_index].duration))) {
        
            cout << "\tRemoving overlapping interval (start, end): (" << ptr->workshops[j].start_time << "," << ptr->workshops[j].end_time << ")" << endl;
            count--;
            ptr->workshops[j].end_time = -1;
      }
    }
    //count--;
    cout << "Items reminaing: " << count << endl;
    }
    return num;
}

/***********************************************************************/
int main()
{
    int n;
    cin>>n;
    int start_time[n],duration[n];
    for(int i=0;i<n;i++) {
        cin>>start_time[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>duration[i];
    }
    
    Available_Workshops * ptr;
    ptr=initialize(start_time,duration,n);
    cout<<CalculateMaxWorkshops(ptr)<<endl;
    return 0;
}
