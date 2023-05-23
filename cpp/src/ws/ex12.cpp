/*******************************************************************************
 *   ex12.cpp                                                                  *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <iostream>

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo()
    {
        std::cout << "This is Foo!" << std::endl;
    }

    namespace wasteoftyme
    {
        void Foo()
        {
            std::cout << "This is Foo!" << std::endl;
        }
    } // namespace wasteoftyme
} // namespace useless

namespace stupid
{
    void Foo()
    {
        std::cout << "This is Foo!" << std::endl;
    }

    void Bar()
    {
        std::cout << "This is Bar!" << std::endl;
    }

    void DoNothing(unsigned int) {}
} //namespace stupid

namespace useless
{
    void DoNothing(int) {}
} //namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    stupid::Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() {}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    //Foo(); //try uncommenting this line, solve the error
    Bar(); //why doesn't this line create an error?
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
}//namespace useless

int main(void)
{
    return 0;
}