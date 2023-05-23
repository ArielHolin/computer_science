/*******************************************************************************
 *  rcstring_test.cpp                                                          *
 *  Author: Ariel                                                              *
 *  Reviewer: Maayan                                                           *
 * ****************************************************************************/
#include <iostream>
#include <cstring>
#include <fstream>

#include "rcstring.hpp"
#include "utills.hpp"

using namespace hrd20;
///////////////////////////FunctionDeclarations/////////////////////////////////
void TestCtorsDtorAndEqual(RCString testName = "TestCtorsDtorAndEqual");
void TestLength(RCString testName = "TestLength");
void TestCstr(RCString testName = "TestCstr");
void TestPlusOperators(int exeFlag, RCString testName = "TestPlusOperators");
void TestGreaterThenLessThenOperators(RCString testName = 
                                                 "TestGreaterThenLessOperator");
void TestBracketsOperator(RCString testName = "TestBracktesOperator");
void TestIstreamOperator(RCString testName = "TestIstreamOperator");


void TestGrayBoxFeatures(RCString testName = "TestGrayBoxFeatures");
void TestCharProxyAddedFunctionality(RCString testName = "TestProxyAddedFunctionality");
///////////////////////////////Main/////////////////////////////////////////////
int main()
{
    TestCtorsDtorAndEqual();
    TestLength();
    TestCstr();
    TestPlusOperators(0);
    TestPlusOperators(1);
    TestGreaterThenLessThenOperators();
    TestBracketsOperator();
    
    TestGrayBoxFeatures();
    // TestIstreamOperator();
    TestCharProxyAddedFunctionality();
    
    return 0;
}

void TestCtorsDtorAndEqual(RCString testName)
{
    PrintTestName(testName.CStr());

    RCString defaultTest;
    unsigned int errorCounter = 0;

    if ("" != defaultTest)
    {
        ++errorCounter;
    }

    RCString cctorTest("cctorTest");
    RCString cctorTest2(cctorTest);

    if (cctorTest != cctorTest2 || cctorTest == defaultTest)
    {
        ++errorCounter;
    }

    defaultTest = cctorTest;

    if (defaultTest != cctorTest)
    {
        ++errorCounter;
    }

    SuccessCheck(errorCounter, testName.CStr());
}

void TestLength(RCString testName)
{
    PrintTestName(testName.CStr());

    const char* strArr[] = {"niso", "shnerko", "", "tw", "malloc"};
    size_t lengthArr[] = {4, 7, 0, 2, 6};

    RCString* strObjArr = new RCString[ARR_SIZE(strArr)];

    for (size_t i = 0; i < ARR_SIZE(strArr); ++i)
    {
        strObjArr[i] = strArr[i];
    }

    unsigned int errorCounter = 0;
    for (size_t i = 0; i < ARR_SIZE(lengthArr); ++i)
    {
        CmpResults(strObjArr[i].Length(), lengthArr[i], 
                                             &errorCounter, i, testName.CStr());
    }

    SuccessCheck(errorCounter, testName.CStr());
    delete[] strObjArr;

}

void TestCstr(RCString testName)
{
    PrintTestName(testName.CStr());

    const char* strArr[] = {"niso", "shnerko", "", "tw", "malloc"};
    RCString* strObjArr = new RCString[ARR_SIZE(strArr)];

    for (size_t i = 0; i < ARR_SIZE(strArr); ++i)
    {
        strObjArr[i] = strArr[i];
    }

    unsigned int errorCounter = 0;
    for (size_t i = 0; i < ARR_SIZE(strArr); ++i)
    {
        if (strcmp(strObjArr[i].CStr(), strArr[i]) != 0)
        {
            ++errorCounter;
        }                                   
    }

    SuccessCheck(errorCounter, testName.CStr());
    delete[] strObjArr;
}

void TestPlusOperators(int exeFlag, RCString testName)
{
    PrintTestName(testName.CStr());

    const char* strArr[] = {"infinity", "nisan ", "hello", "gadsar ", "malloc"};
    const char* addedStr[] = {" labs", "ohana", "world", "carmeli", " and new"};


    const char* appendedStr[] = {"infinity labs", "nisan ohana", 
                             "helloworld", "gadsar carmeli", "malloc and new"};


    RCString* strObjArr = new RCString[ARR_SIZE(strArr)];

    for (size_t i = 0; i < ARR_SIZE(strArr); ++i)
    {
        
        switch (exeFlag)
        {
        case 0:
            strObjArr[i] = RCString(strArr[i]);
            strObjArr[i] += RCString(addedStr[i]);
            std::cout  << "this is "<< strObjArr[i] << std::endl;

            break;
        case 1:
            strObjArr[i] =  RCString(strArr[i]) + RCString(addedStr[i]);
            break;
        }

    }
    unsigned int errorCounter = 0;
    for (size_t i = 0; i < ARR_SIZE(appendedStr); ++i)
    {
        // std::cout << strObjArr[i] << std::endl;
        if (strObjArr[i] != RCString(appendedStr[i]))
        {
            ++errorCounter;
        }
    }

    SuccessCheck(errorCounter, testName.CStr());
    delete[] strObjArr;

}

void TestGreaterThenLessThenOperators(RCString testName)
{
    PrintTestName(testName.CStr());

    const char* smallStr[] = {"a", "b", "c", "d", "e"};
    const char* greaterStr[] = {"hel", "tel", "mel", "del", "rel"};

    RCString smallStrObj[ARR_SIZE(smallStr)];
    RCString bigStrObj[ARR_SIZE(greaterStr)];

    for (size_t i = 0; i < ARR_SIZE(smallStr); ++i)
    {
        smallStrObj[i] = RCString(smallStr[i]);
        bigStrObj[i] = RCString(greaterStr[i]);
    }

    unsigned int errorCounter = 0;
    for (size_t i = 0; i < ARR_SIZE(smallStr); ++i)
    {
        if (bigStrObj[i] < smallStrObj[i] || bigStrObj[i] <= smallStrObj[i])
        {
            ++errorCounter;
        }

        if (bigStrObj[i] > smallStrObj[i] && bigStrObj[i] >= smallStrObj[i])
        {
            bigStrObj[i] = smallStrObj[i];
            continue;
        }

        ++errorCounter;
    }

    for (size_t i = 0; i < ARR_SIZE(smallStr); ++i)
    {
        if(bigStrObj[i] >= smallStrObj[i] && smallStrObj[i] <= bigStrObj[i])
        {
            continue;
        }

        ++errorCounter;
    }

    SuccessCheck(errorCounter, testName.CStr());

}

void TestBracketsOperator(RCString testName)
{
    PrintTestName(testName.CStr());

    const char* strArr[] = {"infinity", "nisan", "hello", "gadsar", "malloc"};
    const char* afterChangeArr[] = {"anfinity", "nasan", "healo", "gadaar", "mallac"};

    const size_t OBJ_ARR_SIZE = ARR_SIZE(strArr);

    RCString objStrArr[OBJ_ARR_SIZE];

    for (size_t i = 0; i < ARR_SIZE(strArr); ++i)
    {
        objStrArr[i] = RCString(strArr[i]);
    }

    unsigned int errorCounter = 0;
    for (size_t i = 0; i < ARR_SIZE(strArr); ++i)
    {
        size_t charIdx = i;
        
        objStrArr[i][charIdx] = 'a';

        if (objStrArr[i] != RCString(afterChangeArr[i]))
        {
            std::cout << objStrArr[i] << std::endl;
            ++errorCounter;
        }

    }

    const RCString constObj("infinity");

    if (constObj[0] == 'a')
    {
        ++errorCounter;
    }

    // try to change const object
    // constObj[0] = 'a';

    SuccessCheck(errorCounter, testName.CStr());
}

void TestIstreamOperator(RCString testName)
{
    PrintTestName(testName.CStr());

    RCString s1("nisa");
    RCString s2;
    
    // std::cin >> s1 >> s2; 

    std::cin >> s1;
    std::cin >> s2;

    std::cout << s1 << " " << s1.CStr() << " "  << s1.Length() << std::endl;
    std::cout << s2 << " " << s2.CStr() << " "  << s2.Length() << std::endl;

    SuccessCheck(0, testName.CStr());
}
void TestGrayBoxFeatures(RCString testName)
{
    PrintTestName(testName.CStr());

    RCString test1 = "nisan";

    RCString test2(test1);


    RCString test4  = "just for test";

    test4 = test1;
    unsigned int errorCounter = 0;


    if (3 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    test4 += RCString(" ohana");

    if (2 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    test2[1] = 'a';

    std::cout << "this is test2" << test2 << std::endl;

    if (1 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    RCString test3 = test2;

    if (2 != test2.GetRCDataSize() && 2 != test3.GetRCDataSize())
    {
        ++errorCounter;
    }

    test3 += RCString(" elef");
    if (1 != test2.GetRCDataSize() && 1 != test3.GetRCDataSize())
    {
        ++errorCounter;
    }
    std::cout << test1 << std::endl;
    std::cout << test2 << std::endl;
    std::cout << test3 << std::endl;
    std::cout << test4 << std::endl;
    

    SuccessCheck(errorCounter, testName.CStr());
}
void TestCharProxyAddedFunctionality(RCString testName)
{
    PrintTestName(testName.CStr());

       RCString test1 = "nisan";

    RCString test2(test1);


    RCString test3  = "just for test";

    test3 = test1;
    unsigned int errorCounter = 0;

    if (3 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    char cTest = test3[1];

    if (cTest != test3[1])
    {
        ++errorCounter;
    }

    if (3 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    test2[1] = 'a';

    if (2 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    RCString test4 = test2;

    if (2 != test2.GetRCDataSize() && 2 != test4.GetRCDataSize())
    {
        ++errorCounter;
    }


    test3[2] = test4[3];


    if (1 != test1.GetRCDataSize())
    {
        ++errorCounter;
    }

    test4 += RCString(" hasan");

    if (1 != test2.GetRCDataSize())
    {
        ++errorCounter;
    }

    std::cout << test1 << std::endl;
    std::cout << test2 << std::endl;
    std::cout << test3 << std::endl;
    std::cout << test4 << std::endl;
    

    SuccessCheck(errorCounter, testName.CStr());
}