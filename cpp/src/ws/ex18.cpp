/*******************************************************************************
 *   ex18.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

void Foo(const double& num)
{
    std::cout << "This is num of Foo: " << num << std::endl;
    std::cout << "This is address of num Foo: " << &num << std::endl;
}

void Bar(double& num)
{
    std::cout << "This is num of Bar: " << num << std::endl;
    std::cout << "This is address of num Bar: " << &num << std::endl;
}

int main()
{
    int i = 5;

    Foo(i);
    Bar(reinterpret_cast<double&>(i));
    std::cout << "num address: " << &i << std::endl;
    return 0;
}
