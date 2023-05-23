/*******************************************************************************
 *   ex24.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

struct X
{
    explicit X(int);
    ~X();
    void Foo();
    void Bar() const;

    int m_a;
    int *m_p;
};

X::X(int a_): m_a( a_), m_p(new int(a_)) {}

X::~X() { delete m_p; m_p=0; }

void X::Foo() { ++m_a; --(*m_p); }

void X::Bar() const
{
    std::cout << m_a << std::endl;
    std::cout << *m_p << std::endl;
    std::cout << m_p << std::endl;
    //m_a = 0; //---1---
    //m_p = 0; //---2---
    //*m_p = 0; //---3---
    //Foo(); //---5---
}

void Fifi(const X& x_)
{
    //x_.Foo(); //---4---
    x_.Bar();
}

int main()
{
    X x1(1);

    x1.Foo();
    Fifi(x1);

    return 0;
}

/************ Comments *********************************************************
 * 
 *   explicit constructor make sure that an argument of type X is passed to a 
 *   function for every function that receives X as an argument.
 *   If, for example I have void Func(X x) {} and I pass Func(42), explicit
 *   doesn't allow this.  However, if I discard the explicit than the compiler
 *   will convert type X to 42, since it knows that the constructor receives int. 
 * 
 *   a. const struct X means that a variable of type X is const. 
 * 
 *   e. Commenting line number 3 is different from other comments, because all 
 *      other commentes lines doesn't compile, and line three compile.
 *      The reason is that const after Bar definition probably declare each member
 *      of X as const, hence const int *mp makes the pointer mp const, but the
 *      value inside mutable.
 * 
 *   f. A "const function", denoted with the keyword const after a function 
 *      declaration, makes it a compiler error for this class function to change 
 *      a member variable of the class. However, reading of a class variables is 
 *      okay inside of the function, but writing inside of this function will 
 *      generate a compiler error.
 *      Another way of thinking about such const is as
 *      int X_Bar(const X * const, ...) meaning that this argument that is hidden 
 *      passed as an argument to the function is passed as const (both the 
 *      struct and the value).
 *      Without const after the definition only the pointer is const, and with 
 *      const the data also becomes const.
 * 
 *   i. The new habit that we must have is putting const after method that doesn't
 *      change the values of the struct.
 *      This is important because if the method is long, we want to prevent from
 *      anyone to change the members of the struct.
 *     
 * ****************************************************************************/