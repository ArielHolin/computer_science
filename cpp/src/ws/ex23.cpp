/*******************************************************************************
 *   ex23.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{}

void X::Inc()
{
    ++m_a;
    ++m_b;

    std::cout << "this: " << this << std::endl;
}

void X::Dec()
{
    --m_a;
    --m_b;

    std::cout << "this: " << this << std::endl;
}

void Inc()
{}

int main()
{
    X x1(7, -55);
    X x2(x1);

    Inc();
    x1.Inc();
    x1.Inc();
    x2.Dec();

    std::cout << "sizeof X: " << sizeof(X) << std::endl;

    return 0;
}