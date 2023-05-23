/*******************************************************************************
 *   ws9.cpp                                                                   *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

using namespace std;

void Foo(int i, int j, int k = 8);

int main(void)
{
    Foo(1, 2);
    return 0;
}

void Foo(int i, int j, int k)
{
    cout << "this is i " << i << endl;
    cout << "this is j " << j << endl;
    cout << "this is k " << k << endl;
}

/*************** Conclusions ***************************************************
 * 
 *   It is impossible to initialize variable in decleration, and then skip
 *   initializing variables.
 *   E.g, after initializing variable all precede varaiables must be initialized
 * 
 * ****************************************************************************/