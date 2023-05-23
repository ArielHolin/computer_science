/*******************************************************************************
 * ex36.cpp                                                                    *
 * Author: Ariel                                                               *
 * ****************************************************************************/
#include <iostream>

class X
{
public:    
    X()
    {
        std::cout << "X ctor " << this <<  std::endl;
    }
    virtual ~X() 
    {
        std::cout << "X dtor " << this <<  std::endl;
    }

private:
    double m_a;
};


class Y: public X
{
public:    
    Y() {std::cout << "Y ctor " << this <<  std::endl;}
    ~Y() {std::cout << "Y dtor " << this << std::endl;}

private:
    int m_b;
};

void Foo(const X& x)
{
    std::cout << sizeof(x) << std::endl;
}

int main()
{
    /*X *xp = new Y[5];

    std::cout << "after allocation" << std::endl;
    std::cout << sizeof(X) << std::endl;
    std::cout << sizeof(Y) << std::endl;

    delete[] xp;*/

    Y y1;
    Foo(y1);

    return 0;
}

/************* Comments ********************************************************
 * 
 * Late binding (runtime) is done in accordance with the content of the pointer,
 * and early binding (compile time) is done according to the type of the pointer.
 * 
 * Since in general the size of the derived class is different to the size of 
 * the base class, polymorphism and pointer arithmetic don't play together nicely.
 * 
 * We cannot have polymorphic arrays in C++. Arrays rely on pointer arithmetic 
 * and pointer arithmetic relies on the compiler knowing object sizes. 
 * Any access to any element of the array beyond the zeroth is undefined.
 * 
 * ****************************************************************************/