/*******************************************************************************
 *   ex19.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

struct X
{
    explicit X();//Initialization function without parameters is named.
             //Default constructor (often abbreviated as: Ctor).
    explicit X(int a, int b = 8);// Regular (non default) Ctor.
    ~X();//Deinitialization function is called destructor (Dtor).
    X (const X& other); //Copy initialization function is called copy costructor or CCtor.
    X& operator= (const X& other);//Assignment operator.

    int m_a;
    const int m_b;
};

struct Y
{
    explicit Y();
    X m_x;
    int m_i;
};

Y::Y() : m_x(X(2, 3)), m_i(5)
{
    std::cout << "this:" << this << " Y defaults Ctor." << std::endl;
}

X::X( ) : m_a (3), m_b (4) 
//Implementation of the default Ctor. Why the X::X? The code after the colon is called an initialization list.
{

    // m_a = 3;
    // m_b = 4;

    std:: cout << "this:" << this << "X default Ctor. m_a:" << m_a <<
    "m_b:" << m_b << std:: endl;
}

X:: X (int a_, int b_): m_a(a_), m_b(b_) //Implementation of the second Ctor.
{
    std:: cout<< "this:" << this << "X int int Ctor. m_a:" << m_a <<
    "m_b:" << m_b << std:: endl;

}

X::X( const X& other): m_a (other. m_a), m_b (other.m_b) //Implementation of the copy Ctor.
{
    std:: cout<< "this:" << this <<" X copy Ctor. m_a:" << m_a <<
    "m_b:" << m_b << std:: endl;
}


X& X:: operator=(const X& other)
{
    m_a= other. m_a; //mb= other.m_b;
    std:: cout << "this;" << this <<
     "X assignment operaton. m_a:"<< m_a <<
    " does not change m_b:" << m_b << std:: endl;
    return *this;
}

X:: ~X ( )
{
    std:: cout << "this:" << this <<
    " X Dtor. m_a:" << m_a <<
    "m_b:" << m_b << std:: endl;
}

int main()
{
    X x1;
    X x2 (7) ;
    X *px = new X(x2);
    X x3(9,10) ;
    X x4 (X x1) ;

    x1 = x3;

    X *xp = new X[10];
    delete[] xp;

    delete px; px= 0;

    std::cout << "----------" << std::endl;

    Y y1;
    y1.m_x.m_a = 250;
    //y1.m_x.m_b = 750;
    Y y2(y1);
    Y y3;

    y3 = y1;

    return 0;
}

/*******************************************************************************
 * 
 *   Qusetion 20 comments:
 *   
 *   We can manage without delete[], because we can use the Dtor definition to
 *   deallocate memory of array, and then delete when invoke the Dtor will do
 *   the whole work.
 *   Also we can use the old version of free (in C) instead, which can 
 *   deallocate memory of array.
 *  
 * 
 *   In order to use new[] X should have default Ctor, because new[] won't let 
 *   us initialize every entry of the array, hence we need the default Ctor.
 * 
 * ****************************************************************************/
