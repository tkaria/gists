#include <iostream>

class a {
	public:
	a() {};
	virtual ~a() {};
	virtual void m() = 0;
};

class b:public a {
	public:
	b() {};
	virtual ~b() {};
	void m() { std::cerr << "THIS IS M()" << std::endl; };
};

int
main(int argc, char **argv)
{

	b bee;
	bee.m();
	return 0;
}
