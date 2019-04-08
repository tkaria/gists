#include <iostream>

struct Foo
{
    Foo() { std::cout << "standard" << std::endl; }
    Foo(const Foo&) { std::cout << "copy" << std::endl; }
    Foo(int) { std::cout << "int" << std::endl; }
    Foo(int, int) { std::cout << "int, int" << std::endl; }
    Foo(const Foo&, int) { std::cout << "Foo, int" << std::endl; }
    Foo(int, const Foo&) { std::cout << "int, Foo" << std::endl; }
};

void f(Foo) {}

struct Bar
{
    int m_i;
    int m_j;

    Bar()
    {
        f(Foo(m_i, m_j));
        f(Foo(m_i));
        Foo(m_i, m_j);
        Foo(m_i);
        Foo(m_i, m_j);
    }
};

int main()
{
    Bar();
}
