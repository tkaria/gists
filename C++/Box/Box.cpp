#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int BoxesCreated,BoxesDestroyed;

class Box {
  private:
    int l;
    int b;
    int h;
//Implement the class Box
//l,b,h are integers representing the dimensions of the box
  public:
// The class should have the following functions :
// Constructors:
// Box();
  Box() {
    this->l = 0;
    this->b = 0;
    this->h = 0;
    BoxesCreated++;
  }
// Box(int,int,int);
  Box(int l, int b, int h) {
    this->l = l;
    this->b = b;
    this->h = h;
    BoxesCreated++;
  }
// Box(Box);
  Box(const Box& rhs) {
    this->l = rhs.l;
    this->b = rhs.b;
    this->h = rhs.h;
    BoxesCreated++;
  }

// Destructor
// ~Box()
  ~Box()  {
      BoxesDestroyed++;
  }

// int getLength(); // Return box's length
  int getLength() {
    return this->l;
  }
// int getBreadth (); // Return box's breadth
  int getBreadth() {
    return this->b;
  }
// int getHeight ();  //Return box's height
  int getHeight() {
    return this->h;
  }
// long long CalculateVolume(); // Return the volume of the box
  long long CalculateVolume() {
    return (long long)this->l *(long long) this->b *(long long) this->h;
  }

//Overload operator < as specified
//bool operator<(Box &b)
  bool operator<(Box& b) {
    return (this->l < b.l ||
      (this->b < b.b and this->l == b.l) ||
      (this->h < b.h and this->b == b.b and this->l == b.l)
    );
  }

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box B)
  friend ostream& operator<<(ostream& out, Box B) {
      out << B.l << ' ' << B.b << ' ' << B.h ;
      return out;
  }
};

void check2()
{
int n;
cin>>n;
Box temp;
for(int i=0;i<n;i++)
    {
    int type;
    cin>>type;
    if(type ==1)
        {
            cout<<temp<<endl;
        }
        if(type == 2)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            temp=NewBox;
            cout<<temp<<endl;
        }
        if(type==3)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            if(NewBox<temp)
            {
                cout<<"Lesser"<<endl;
        }
            else
            {
                cout<<"Greater"<<endl;
            }
        }
        if(type==4)
        {
            cout<<temp.CalculateVolume()<<endl;
        }
        if(type==5)
        {
            Box NewBox(temp);
            cout<<NewBox<<endl;
        }

    }
}

int main()
{
    BoxesCreated = 0;
    BoxesDestroyed = 0;
    check2();
    cout<<"Boxes Created : "<<BoxesCreated<<endl<<"Boxes Destroyed : "<<BoxesDestroyed<<endl;
}

