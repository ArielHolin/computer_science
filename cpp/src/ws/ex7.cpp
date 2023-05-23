/*******************************************************************************
 *   ex7.cpp                                                                   *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

using namespace std;

int main(void)
{
    float *f = new float(12);
    delete f;

    f = new float[15];

    cout << sizeof(f) << endl;

    delete[] f;

    return 0;
}

/************* Conclusions *****************************************************
 * 
 *   How does new prevent bugs?
 *   
 *   1. new is type safe: we can't initialize variable like:
 *      float *f = new int(12), however in C we can do that with malloc.
 * 
 *   2. The initialization of variable is taking place within the new statement,
 *      unlike with malloc.
 * 
 * 
 * ****************************************************************************/