/*******************************************************************************
 *   ex11.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>
#include <dlfcn.h>

using namespace std;

typedef void (*BarFunc)(void);

void Foo() 
{
    cout << "This is Foo void" << endl;
}

void Foo(int i)
{
    cout << "This is Foo int: " << i << endl;
}

void Foo(char c)
{
    cout << "This is Foo char: " << c << endl;
}

int main(void)
{   
    Foo();
    Foo(2);
    Foo('c');

    void *lib_handle = dlopen("libso1.so", RTLD_LAZY);
    if(NULL == lib_handle)
    {
        char *error = dlerror();
        return -1;
    }

    BarFunc Bar1 = reinterpret_cast<BarFunc>(dlsym(lib_handle, "_Z4Bar1v"));

    if(NULL == Bar1)
    {
        return -1;
    }

    Bar1();

    dlclose(lib_handle);

    return 0;
}