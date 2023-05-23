/*********************************************************************
* Description: BitSet Test
* Name: Ariel
* Reviewer - 
* Date: 3.1.22
* Versions: 1.0
* 0.1 - ready for review
*********************************************************************/
#include <iostream>

#include "bitset.hpp"

using namespace hrd20;

void CheckOperatorBracket();
void ChecklogicOrOperator();
void ChecklogicAndOperator();


int main()
{
    CheckOperatorBracket();
    ChecklogicOrOperator();
    ChecklogicAndOperator();

    return 0;
}

void ChecklogicAndOperator()
{
    BitSet<128> bs1;
    BitSet<128> bs2;
    BitSet<128> bs3;

    bs1[0] = true;
    bs1[2] = true;
    bs1[10] = true;
    bs1[100] = true;

    bs2[1] = true;
    bs2[2] = true;
    bs2[50] = true;
    bs2[100] = true;

    bs3[2] = true;
    bs3[100] = true;

    bs2 &= bs1;

    if (bs2 == bs3)
    {
        std::cout << "And test pass" << std::endl;
    }
    else
    {
        std::cout << "And Errr" << std::endl;
    }
}

void ChecklogicOrOperator()
{
    BitSet<128> bs1;
    BitSet<128> bs2;

    bs1[0] = true;
    bs1[2] = true;
    bs1[10] = true;
    bs1[100] = true;
    bs1[101] = true;
    bs1[106] = true;

    bs2 |= bs1;

    if ((6 ==  bs2.CountBitsOn()) && bs2 == bs1)
    {
        std::cout << "or test pass" << std::endl;
    }
    else
    {
        std::cout << "Errrror ..." << std::endl;
    }
}

void CheckOperatorBracket()
{
    BitSet<128> bs1;
    BitSet<128> bs2;

    bs1[0] = true;
    bs1[2] = true;
    bs1[10] = true;
    bs1[10] = false;
    bs1[12] = false;

    bs2 = bs1;

    if (bs1[1])
    {
        std::cout << "Error !" << std::endl;        
    }

    if (bs1[2])
    {
        std::cout << "Nice " << std::endl;        
    }

    if ((2 ==  bs2.CountBitsOn()) && bs2 == bs1)
    {
        std::cout << "Nice twice" << std::endl;
    }
    else
    {
        std::cout << "Errrror ..." << std::endl;
    }
}