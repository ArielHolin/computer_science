/*******************************************************************************
 *   ex13.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

int main(void)
{
    const int i = 3;
    int *ip = (int *)&i;
    *ip = 5;
    /*int arr[i];*/

    std::cout << i << " " << *ip << std::endl;
    return 0;
}