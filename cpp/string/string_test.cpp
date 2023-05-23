/*******************************************************************************
 *  string_test.cpp                                                            *
 *  Author: Ariel                                                              *
 *  Reviewer: Maayan                                                           *
 * ****************************************************************************/
#include <iostream>  /* cout, endl */
#include <cstdio>    /* printf     */

#include "string.hpp"

using namespace hrd20;

static const bool YES = 1;
static const bool NO  = 0;                                   

struct Results
{  
	size_t length;
	bool is_equal;
	bool is_bigger;
	bool is_smaller;
};

void InitializeStringTests(void);
void ContcatenatesStringTests(void);
void ChangeVarStringTests(void);
void ComparisonStringTests(void);
void StreamStringTests(void);

void EndOfTests(void);

/* helper */
static void TestResultComper(Results results, Results expected_results,
                                            const char *test_name, size_t line);

/*******************************************************************************
************************************ The Main  ********************************/

int main ()
{  
	InitializeStringTests();
	ContcatenatesStringTests();
	ChangeVarStringTests();
	ComparisonStringTests();
	StreamStringTests();

	EndOfTests();
	
	return 0; 
}

/*******************************************************************************
**************************** Initialize String Test ***************************/

void InitializeStringTests(void)
{ 
	const char *test_name1 = "str;     - Initialize String ";
	const char *test_name2 = "str("")  - Initialize String ";
	const char *test_name3 = "str = "" - Initialize String ";

	const char* tmp_1 = "";
	const char* tmp_2 = "hello1";
	const char* tmp_3 = "hello2";
	
	String str_1;
	String str_2 = "hello1";
	String str_3("hello2");

	Results expected_results;
	Results results;

	/*________________________________ case 1 ________________________________*/

	expected_results.length = 0;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;

	results.length   =  str_1.Length();
	results.is_equal = (str_1 == tmp_1);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name1, __LINE__);

	std::cout << "\nExpected String : "  << tmp_1 << 
				 "\nString          : "  << str_1 << std::endl;

	/*________________________________ case 2 ________________________________*/

	expected_results.length = 6;
	expected_results.is_equal = YES;

	results.length   =  str_2.Length();
	results.is_equal = (str_2 == tmp_2);
		
	TestResultComper(results, expected_results, test_name2, __LINE__);

	std::cout << "\nExpected String : "  << tmp_2 << 
				 "\nString          : "  << str_2 << std::endl;

	/*________________________________ case 3 ________________________________*/

	expected_results.length = 6;
	expected_results.is_equal = YES;

	results.length   =  str_3.Length();
	results.is_equal = (str_3 == tmp_3);
		
	TestResultComper(results, expected_results, test_name3, __LINE__);

	std::cout << "\nExpected String : "  << tmp_3 << 
				 "\nString          : "  << str_3 << std::endl;
}

/*******************************************************************************
************************** Contcatenates String Test **************************/

void ContcatenatesStringTests(void)
{ 
	const char *test_name1 = "s1 += s2;              - Contcatenates String ";
	const char *test_name2 = "s1 += \"hello\";       - Contcatenates String ";
	const char *test_name3 = "s1 = s2 + s3;          - Contcatenates String ";
	const char *test_name4 = "s1 = \"he\" + \"llo\"; - Contcatenates String ";
	const char *test_name5 = "s1(\"he\" + \"llo\");  - Contcatenates String ";

	const char* exp_1 = "hello1";
	const char* exp_2 = "hello2";
	const char* exp_3 = "hello3";
	const char* exp_4 = "hello4";
	const char* exp_5 = "hello5";

	Results expected_results;
	Results results;

	/*________________________________ case 1 ________________________________*/

	String str1  = "he";
	String str1a = "llo1";

	str1 += str1a; 
	
	expected_results.length = 6;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;

	results.length   =  str1.Length();
	results.is_equal = (str1 == exp_1);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name1, __LINE__);

	std::cout << "\nExpected String : "  << exp_1 << 
				 "\nString          : "  << str1 << std::endl;

	/*________________________________ case 2 ________________________________*/

	String str2 = "he";

	str2 += "llo2"; 
	
	expected_results.length = 6;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;

	results.length   =  str2.Length();
	results.is_equal = (str2 == exp_2);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name2, __LINE__);

	std::cout << "\nExpected String : "  << exp_2 << 
				 "\nString          : "  << str2 << std::endl;


	/*________________________________ case 3 ________________________________*/

	String str3 = "aaaaaa";
	String str3a = "he";
	String str3b = "llo3";

	str3 = str3a + str3b; 
	
	expected_results.length = 6;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;
	
	results.length   =  str3.Length();
	results.is_equal = (str3 == exp_3);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name3, __LINE__);

	std::cout << "\nExpected String : "  << exp_3 << 
				 "\nString          : "  << str3 << std::endl;


	/*________________________________ case 4 ________________________________*/

	String str4 = "aaaaaa";
	String str4a = "he";

	str4 = str4a + "llo4"; 
	
	expected_results.length = 6;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;
	
	results.length   =  str4.Length();
	results.is_equal = (str4 == exp_4);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name4, __LINE__);

	std::cout << "\nExpected String : "  << exp_4 << 
				 "\nString          : "  << str4 << std::endl;

	/*________________________________ case 5 ________________________________*/

	String str5a = "llo5";
	String str5("he" + str5a); 
	
	expected_results.length = 6;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;
	
	results.length   =  str5.Length();
	results.is_equal = (str5 == exp_5);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name5, __LINE__);

	std::cout << "\nExpected String : "  << exp_5 << 
				 "\nString          : "  << str5 << std::endl;
}


/*******************************************************************************
**************************** ChangeVar String Test ****************************/

void ChangeVarStringTests(void)
{ 
	const char *test_name1 = "str1[3] = 'a' - ChangeVar in String ";
	const char *test_name2 = "const str1[3] = 'a' - ChangeVar in String ";

	Results expected_results;
	Results results;

	/*________________________________ case 1 ________________________________*/

	String str1 = "hello";
	String exp1 = "helly";

	str1[4] = 'y';

	expected_results.length = 5;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;

	results.length   =  str1.Length();
	results.is_equal = (str1 == exp1);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name1, __LINE__);

	std::cout << "\nExpected String : "  << exp1 << 
				 "\nString          : "  << str1 << std::endl;

	/*________________________________ case 2 ________________________________*/
/*
	const String str2 = "hello";
	const String exp2 = "hello";

	str2[4] = 'y';

	expected_results.length = 5;
	expected_results.is_equal = YES;
	expected_results.is_bigger  = 0;
	expected_results.is_smaller = 0;

	results.length   =  str2.Length();
	results.is_equal = (str2 == exp2);
	results.is_bigger  = 0;
	results.is_smaller = 0;
		
	TestResultComper(results, expected_results, test_name2, __LINE__);

	std::cout << "\nExpected String : "  << exp2 << 
				 "\nString          : "  << str2 << std::endl;
*/
}


/*******************************************************************************
**************************** Comparison String Test ***************************/

void ComparisonStringTests(void)
{ 
	const char *test_name1 = "abc > aaa Comparison String";

	Results expected_results;
	Results results;

	/*________________________________ case 1 ________________________________*/

	String str1 = "abc";
	String str2 = "aaa";

	expected_results.length = 3;
	expected_results.is_equal = NO;
	expected_results.is_bigger  = YES;
	expected_results.is_smaller = NO;

	results.length   =  str1.Length();
	results.is_equal = (str1 == str2);
	results.is_bigger  = (str1 > str2);
	results.is_smaller = (str1 < str2);
		
	TestResultComper(results, expected_results, test_name1, __LINE__);

	std::cout << "\nString from user: "  << str1 << std::endl;
}

/*******************************************************************************
**************************** Comparison String Test ***************************/

void StreamStringTests(void)
{ 
	const char *test_name = "Get String From User";

	printf("\n\n\ntest %s: OK\n", test_name);

	/*________________________________ case 1 ________________________________*/

	String str1;

	std::cin >> str1; 

	std::cout << "\nExpected String : "  << str1 << 
				 "\nString          : "  << str1 << std::endl;
}

/*******************************************************************************
******************************* Test Result Comper ****************************/

static void TestResultComper(Results results, Results expected_results,
                                    const char *test_name, size_t line)
{ 
	int flag = 0;

	if(results.length != expected_results.length)
	{
		printf("\nThe is not equal test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	}
	if(results.is_equal != expected_results.is_equal)
	{
		printf("\nThe is equal test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	} 
	if(results.is_bigger != expected_results.is_bigger)
	{
		printf("\nThe is bigger test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	}
	if(results.is_smaller != expected_results.is_smaller)
	{
		printf("\nThe is smaller test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	} 

	if(0 == flag)
	{
		printf("\n\n\ntest %s: OK\n", test_name);
	}
}

/*******************************************************************************
********************************** End Of Tests *******************************/

void EndOfTests(void)
{
	printf("\n_________________________End Of Tests________________________\n");
}