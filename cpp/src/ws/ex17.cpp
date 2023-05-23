/*******************************************************************************
 *   ex17.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>
#include <typeinfo>

int main()
{
    int i = 8;
    int i2 =45;
    char c = 'a';
    double d = 1.2;
    bool b = true;
    float f = 0.2;
    //char str[] = "alibaba";

    int& ip = i;
    char& cp = c;
    double& dp = d;
    bool& bp = b;
    float& fp = f;
    ip = i2;
    //char[]& strp = str;
    std::cout << typeid(ip).name() << " " << typeid(i).name() << std::endl;

    std::cout << " i bf: " << i;
    std::cout << " i2 bf: " << i2;
    std::cout << " c bf: " << c;
    std::cout << " d bf: " << d;
    std::cout << " b bf: " << b;
    std::cout << " f bf: " << f << std::endl;
   // std::cout << " bf: " << str << std::endl;
    

    cp = 'b';
    dp = 2.2;
    bp = false;
    fp = 0.5;
    //strp = "alliexpress";
    ip = 9;
    std::cout << " i af: " << i;
    std::cout << " i2 af: " << i2;
    std::cout << " c af: " << c;
    std::cout << " d af: " << d;
    std::cout << " b af: " << b;
    std::cout << " f af: " << f << std::endl;
    //std::cout << " bf: " << str << std::endl;

    std::cout << " i address: " << &i << std::endl;
    std::cout << " ip address: " << &ip << std::endl;
    
    std::cout << "size of int& " << sizeof(ip) << std::endl;
    std::cout << "size of char& " << sizeof(cp) << std::endl;
    std::cout << "size of double& " << sizeof(dp) << std::endl;
    std::cout << "size of bool& " << sizeof(bp) << std::endl;
    std::cout << "size of float& " << sizeof(fp) << std::endl;

    return 0;
}