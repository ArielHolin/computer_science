/*******************************************************************************
 *   ex25.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <cstdio>

class X
{
public:
    explicit X(int a_);
    void Foo();
    int GetMa() const;

private:
    int m_a;
};

int X::GetMa() const
{
    return m_a;
}

X::X(int a_) : m_a(a_)
{}

void X::Foo()
{
    printf("%d\n", m_a);
}

void Foo(const X& x_)
{
    printf("%d\n", x_.GetMa());
}

int main()
{
    X x1(1);

    x1.Foo();
    printf("%d\n", x1.GetMa());
    Foo(x1);

    return 0;
}