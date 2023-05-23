/*******************************************************************************
 *   ex15.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

#include "ex15.hpp"

int main()
{
    int arr[12];

    std::cout << Max<int>(3,5) << " " << Max<double> (3.7, 12.9) << " ";
    std::cout << Max<int *>(arr,arr + 8) << std::endl;

    std::cout << Max('a','b') << std::endl;
    std::cout << Max(25.0,30.5) << std::endl;
    // std::cout << Max(25,30.5) << std::endl; // Won`t work .. 
    std::cout << Max<char>(25,'a') << std::endl;

    std::cout << Max(static_cast<int>('A'),90) << std::endl;
    return 0;
}