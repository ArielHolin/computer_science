/*******************************************************************************
 *  ex28.cpp                                                                   *
 *  Author: Ariel                                                              *
 * ****************************************************************************/
#include <iostream>

class X
{
public:
    X(): m_id(++s_cntr){}
    int GetId() {std::cout << m_id << std::endl; return m_id;}

private:
    int m_id;
    static int s_cntr;
};

int X::s_cntr = 0;

int main()
{

    X x1;
    X x2;
    x1.GetId();
    x2.GetId();

    return 0;
}

/************** Comments *******************************************************
 * 
 * a. When you declare a member of a class as static it means no matter how many
 *    objects of the class are created, there is only one copy of the static 
 *    member. A static member is shared by all objects of the class.
 * 
 * 
 * 
 * ****************************************************************************/
