
#include <vector>
#include <string>
#include <iostream>

class en 
{

public: 
	en(int x, std::string y):_x(x), _y(y) { std::cerr << "ctor(" << x << "," << y << ")" << std::endl;};

	en( const en& e):_x(e._x), _y(e._y) { std::cerr << "copy(" << e._x << "," << e._y << ")" << std::endl; };

	bool operator < (en& rhs) {
		std::cerr << "operator<" << std::endl;
		return (this->_x < rhs.getX());
	}
	

	int getX() const { return _x; };

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
	std::vector<en>::iterator prev = it;
	while(*it<e && it != v.end()) {
			prev=it;
			it++;
	};
	return it;

}

void 
b(std::vector<en>& v) 
{
	std::vector<en>::iterator it = v.begin();
	while(it != v.end()) {
			std::cout << it->getX() << std::endl;
			it++;
	}
}

void 
a(std::vector<en>& v)
{
		for (int i =0; i<10; i++) {
			v.push_back(en(i, "xxx"));
		}	
}

int main()
{
	// Create empty vector
	std::vector<en> v;
	a(v);
	b(v);	

}
