
#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <boost/lambda/construct.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/shared_ptr.hpp>


// testing 123
// testing 456
// testing 789
// this is getting boring

#include "x.h"

class C;


typedef boost::shared_ptr<C> pC;

class C 
{

public: 
	C(const double x, const std::string y):_x(x), _y(y) { std::cerr << "ctor" << std::endl;};

	bool operator < (C& rhs) const  {
		std::cerr << "operator<" << std::endl;
		return (this->_x < rhs.getX());
	}
	bool operator > (C& rhs) const {
		std::cerr << "operator>" << std::endl;
		return (this->_x > rhs.getX());
	}

    bool operator==(C& rhs) const {
        std::cerr << "operator==" << std::endl;
        return (this->_x == rhs.getX());
    }

	const double getX() const { return _x; };
	
	~C() { std::cout << "~C()" << std::endl; }

protected:
	double _x;
	std::string _y;

};
/*
struct Ccomp : public std::binary_function<pC, pC, bool> {

    bool operator() (pC const & a, pC const & b) {
            return *(a.get()) < *(b.get());
    }; 
};
*/

typedef std::set<pC, Ccomp> Cset;


Cset::iterator 
_find(Cset& s, double d)
{
    C* c = new C(d, "B");
    Cset::iterator it = s.find(pC(c));
    return it;
} 

int main()
{
    Cset s;
    C* element = new C(1.0000, "A");
    pC pc(element);
    s.insert(pc);
    Cset::iterator it = _find(s, 1.000);

    if (it == s.end()) {
        std::cerr << "ELEMENT NOT FOUND" << std::endl;
    }
    else {
        std::cerr << "FOUND BY SEARCH" << std::endl;
    }
    
    it = s.find(pc);
    if (it == s.end()) {
        std::cerr << "ELEMENT NOT FOUND" << std::endl;
    }
    else {
        std::cerr << "FOUND SMART POINTER" << std::endl;
    }


#if 0
	for (int i=50; i<55; i++) {
		v.push_back(en(i, "foo"));
	}

	for (int i=60; i<65; i++) {
		v.push_back(en(i, "foo"));
	}
	// find 3rd element in vector
	std::vector<en>::iterator it = f(v, 3);
	if (it == v.end()) std::cout << "v.end()" << std::endl;
 	// **************** TEST CODE ***************
	//if (it == v.end()) v.push_back(en(99, "zbar"));
	//else v.insert(it, en(102, "xsdf"));
	//v.insert(it, en(102, "xsdf"));
 	// **************** TEST CODE ***************
 	

	// find where to insert 40
	it = fi(v, en(40, "abc")); 
	// should be beginning
	v.insert(it, en(40, "def"));

	// find where to isnert 102
	it = fi(v, en(102, "abc")); 
	// should be end
	v.insert(it, en(102, "def"));

	// find where to insert 101
	it = fi(v, en(101, "abc")); 
	// should ebe right before 102
	v.insert(it, en(101, "def"));

	// insert to middle of vec
	it = fi(v, en(56, "abc")); 
	v.insert(it, en(56, "def"));
	for (std::vector<en>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << it->getX() << std::endl;
	}
#endif
	

}
