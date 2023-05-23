/*******************************************************************************
 *   ex16.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>
#include <typeinfo>

template <typename T>
void foo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

template <>
void foo<int>(int num)
{
    std::cout << num << " specialized foo template for " << typeid(num).name() 
              << std::endl;
}

void foo(int t)
{
    std::cout << t << " function foo (for int param)\n";
}

int main ()
{
    foo(4.2);
    foo(5);
    foo<int>(5);

    return 0;
}