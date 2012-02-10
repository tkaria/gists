
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <boost/lambda/construct.hpp>
#include <boost/lambda/lambda.hpp>

// testing 123
// testing 456
// testing 789
// this is getting boring

class en 
{

public: 
	en(const int x, const std::string y):_x(x), _y(y) { std::cerr << "ctor" << std::endl;};

	bool operator < (en& rhs) {
		std::cerr << "operator<" << std::endl;
		return (this->_x < rhs.getX());
	}
	bool operator > (en& rhs) {
		std::cerr << "operator>" << std::endl;
		return (this->_x > rhs.getX());
	}

	const int getX() const { return _x; };
	
	~en() { std::cout << "~en()" << std::endl; }

protected:
	int _x;
	std::string _y;

};


std::vector<en>::iterator 
f(std::vector<en>& v, unsigned int level) 
{
	std::vector<en>::iterator it = v.begin();
	unsigned int i = 0;
	while(i<level-1 && it != v.end()) { i++; it++;};
	return it;

}

std::vector<en>::iterator 
fi(std::vector<en>& v, en e) 
{
	std::vector<en>::iterator it = v.begin();
	//std::vector<en>::iterator prev = it;
	while(it != v.end() && e > *it) {
			//prev=it;
			it++;
	};
	return it;

}

int main()
{
	std::vector<en> v;
	std::vector<en*> vp;
	
	for (int i = 0; i < 10; i++) {
		vp.push_back(new en(i, "abc"));
	}

	std::for_each(vp.begin(), vp.end(), boost::lambda::delete_ptr());



	std::vector<en>::iterator it;
	v.insert(it, en(5, "a"));
	it = fi(v, en(6, "b"));
	v.insert(it, en(6, "b"));
	it = fi(v, en(7, "c"));
	v.insert(it, en(7, "b"));
	it = fi(v, en(4, "f"));
	v.insert(it, en(4, "f"));
	
	std::cout << "TOP OF VEC: " << v[0].getX() << std::endl;
	std::cout << "TOP OF VEC: " << v[1].getX() << std::endl;

/*
	v.push_back(en(32, "c"));
	v.push_back(en(12321, "c"));
	v.push_back(en(2132, "c"));
	v.push_back(en(89898, "c"));
	v.push_back(en(4958, "c"));
	v.push_back(en(249, "c"));
	v.push_back(en(7726, "c"));

	std::cout << "v.size(): " << v.size() << std::endl;
	it = f(v, 9);
	if (it == v.end()) { 
		std::cout << "v.end()" << std::endl;
	}
	else {
		std::cout << it->getX() << std::endl;	
		v.erase(it, v.end());
	}
	//if (it != v.end()) {
		//it->getX();
	//}
	//v.insert(it, en(128, "a"));
*/
	int i = 0;
	for (std::vector<en>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << ++i << " " << it->getX() << std::endl;
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
