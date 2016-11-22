
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace XXXX {
class en {
 public:
  en(const int x, const std::string y) : _x(x), _y(y) {
    std::cerr << "ctor" << std::endl;
  };

  bool operator<(en &rhs) {
    std::cerr << "operator<" << std::endl;
    return (this->_x < rhs.getX());
  }
  bool operator>(en &rhs) {
    std::cerr << "operator>" << std::endl;
    return (this->_x > rhs.getX());
  }

  const int getX() const { return _x; };
  friend std::ostream &operator<<(std::ostream &out, const en &);

 protected:
  int _x;
  std::string _y;
};

std::ostream &operator<<(std::ostream &out, const en &e) {
  out << "getX() returned: " << e.getX();
  return out;
}

};  // closing namespace

using namespace XXXX;
std::vector<en>::iterator f(std::vector<en> &v, unsigned int level) {
  std::vector<en>::iterator it = v.begin();
  unsigned int i = 0;
  while (i < level - 1 && it != v.end()) {
    i++;
    it++;
  };
  return it;
}

std::vector<en>::iterator fi(std::vector<en> &v, en e) {
  std::vector<en>::iterator it = v.begin();
  // std::vector<en>::iterator prev = it;
  while (it != v.end() && e > *it) {
    // prev=it;
    it++;
  };
  return it;
}

std::vector<int>::iterator find(std::vector<int> &v, int i) {
  std::vector<int>::iterator it = v.begin();
  while (it != v.end() && i < *it) {
    it++;
  }
  return it;
}

int main() {
  // std::vector<en> v;
  // std::vector<en> v2;
  std::vector<int> iv(3, -1);
  std::vector<int>::iterator ivit;

  ivit = std::find(iv.begin(), iv.end(), 3);
  if (ivit != iv.end()) {
    std::cout << "3 already exists using std::find" << std::endl;
  } else {
    std::cout << "DOES NOT EXIST" << std::endl;
  }

  ivit = find(iv, 3);

  if (ivit != iv.end() && ivit != iv.begin()) {
    std::cout << "3 already exists" << std::endl;
  } else {
    // std::cout << ivit << std::endl;
    if (ivit == iv.end()) {
      std::cout << "iterator end()" << std::endl;
    }
    if (ivit == iv.begin()) {
      std::cout << "iterator begin()" << std::endl;
    }
    if (iv.begin() == iv.end()) {
      std::cout << "EMPTY vec" << std::endl;
    }
    iv.insert(iv.begin(), 3);
  }

  if (ivit == iv.end()) {
    std::cout << "iterator end()" << std::endl;
  }
  if (ivit == iv.begin()) {
    std::cout << "iterator begin()" << std::endl;
  }
  iv.insert(ivit, 3);
  ivit = find(iv, 1);
  iv.insert(ivit, 1);
  ivit = find(iv, 2);
  iv.insert(ivit, 2);
  ivit = find(iv, 4);
  iv.insert(ivit, 4);
  ivit = find(iv, 3);
  if (ivit != iv.end() && *ivit == 3) {
    std::cout << "3 already exists" << std::endl;
  } else {
    iv.insert(ivit, 3);
  }
  std::cout << "Vector contains: " << iv.size() << " elements." << std::endl;
  for (std::vector<int>::iterator it = iv.begin(); it != iv.end(); it++) {
    std::cout << *it << std::endl;
  }

/*
        std::vector<en>::iterator it;
        v.insert(it, en(5, "a"));
        it = fi(v, en(6, "b"));
        v.insert(it, en(6, "b"));
        it = fi(v, en(7, "c"));
        v.insert(it, en(7, "b"));
        it = fi(v, en(4, "f"));
        v.insert(it, en(4, "f"));

        std::cout << "v[0]: " << v[0];
*/
// std::cout << "TOP OF VEC: " << v[0].getX() << std::endl;
// std::cout << "TOP OF VEC: " << v[1].getX() << std::endl;

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
        int i = 0;
        for (std::vector<en>::iterator it = v.begin(); it != v.end(); it++) {
                std::cout << ++i << " " << it->getX() << std::endl;
        }

        int j = 0;
        for (std::vector<en>::iterator it2 = v2.begin(); it2 != v2.end(); it2++)
   {
                std::cout << ++i << ":" << (int)it << std::endl;
        }
*/

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
