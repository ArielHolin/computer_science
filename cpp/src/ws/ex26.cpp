/*******************************************************************************
 *   ex26.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>
using namespace std;

class X;

int operator+(const X& x1_, const X& x2_)
{
    return 7;
}

//ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
    bool operator==(const X& o_) const { return m_a == o_.m_a; }
    int GetMa() const;
    //ostream& operator<<(ostream& os_);
    //Java style inline - not allowed in our coding standard
    friend ostream& operator<<(ostream& os_, const X& x_);
private:
    int m_a;
};

int X::GetMa() const
{
    return m_a;
}

int main()
{
    X x1;
    X x2;

    cout<< " x1+x2:" << x1 + x2 <<
           " x1==x2:" << (x1 == x2) <<
           " x1:" << x1 <<
           " x2:" << x2 << endl;

    return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a;
}

/********** Comments ***********************************************************
 * 
 *   b. Differences between member and global operators:
 *      1. member operators have access to private class members.
 *      2. member operators receive only one argument (as 'this' invoked while 
 *         calling the member operator), while global operators receive two arguments.
 *      3. When passing two arguments into member operator, the inovked member function 
 *         is of the first argument, and the second argument is passed as user defined argument.
 *      
 *   e. Friend keyword allows access of global function/other classes/structs 
 *      to private members of the class calling friend.
 * 
 *   f.  We can discard friend keyword, and use getters methods in order to access
 *       private members.
 * 
 *   h. Using friend keyword breaks encapsulation, and should be used in a limited manner.
 * 
 *   j. Friend is considered by the compiler as an outsource function, even if defined
 *      inside the class.
 * 
 *   k. Probably we should declare friend inside the private scope to emphasys 
 *      that an outsource function now has access to private members.
 *      No other functionality is influenced by public/private section of declaration.
 * 
 * ****************************************************************************/