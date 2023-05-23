/*******************************************************************************
 *   ex2.cpp                                                                     *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

using namespace std;

enum E {AA, BB, CC, DD};
enum E2 {TT, KK}; 
/*enum E e = 2;
enum E2 e2 = AA;*/

E a;

/*******************************************************************************
************************************** main ***********************************/

int main(void)
{    
    /*++e;
    int x = AA;*/
    int x = 4;
    E a = x;
    cout << a << endl;

    return 0;
}

/************************** Conclusions ****************************************
 *   In cpp we can assign enum to int, but we can't assign int to enum.
 *   
 *   The value of an uninitialized global enum varialbe is 0.
 *   The value of an uninitialized local enum variable is garbage.
 * 
 *   The implications are that whenever we declare a vaiable we must initialize
 *   it, so it doesn't get garbage variable.
 * 
 * ****************************************************************************/