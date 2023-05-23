/*******************************************************************************
 *   ex5.cpp                                                                   *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

using namespace std;

int main(void)
{
    foo();
    return 0;
}

void foo()
{
    cout << "I am foo" << endl;
}

/************** Conclusions ****************************************************
 * 
 *   In .c files undeclared function are implicitly declared, hence the compiler
 *   prints "warning: implicit declaration of function".
 *   
 *   In this case the compiler implicitly decalres the function, and the default
 *   return value is int, so if later in the code we define the function with 
 *   return type != int, the compiler will through an error.
 * 
 *   In cpp, there is no implicit declaration, and when there is no explicit
 *   declaration the compiler will through an error.
 * 
 * ****************************************************************************/