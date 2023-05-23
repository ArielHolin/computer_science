/*******************************************************************************
 *   ex3.cpp                                                                   *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

using namespace std;

int main(void)
{
    bool b1 = false;
    bool b2;
    int i = b1;
    i = 7;
    b2 = i;
    
    cout << sizeof(b1) << endl;
    cout << b2 << endl;

    return 0;
}

/************ Conclusions ******************************************************
 * 
 *   The size of boolean variable is 1 byte, but can change sometimes.
 * 
 *   The value of uninitialized boolean variable is 0.
 * 
 *   The value of true is always 1.  If a boolean variable receives a value
 *   different than 0, the compiler will always assign it to 1.
 *   (Some compilers give performance warning, because of this conversion.)
 * 
 ******************************************************************************/