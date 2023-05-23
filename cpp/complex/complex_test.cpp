/*******************************************************************************
 *  complex_test.cpp                                                           *
 *  Author: Ariel                                                              *
 *  Reviewer: Doron                                                            *
 * ****************************************************************************/
#include <cstdio> /* printf */

#include "complex.hpp"

using namespace hrd20;

static const bool YES = 1;
static const bool NO  = 0;                                   

struct Results
{  
	bool isnt_equal;
	bool is_equal;
	double real;		
    double imag;
};

void InitializeComplexTests(void);
void SetComplexTests(void);

void MembersFunctionOperatorPlusTests(void);
void MembersFunctionOperatorMinusTests(void);
void MembersFunctionOperatorMultiplicationTests(void);
void MembersFunctionOperatorDivisionTests(void);

void NonMembersFunctionOperatorPlusTests(void);
void NonMembersFunctionOperatorMinusTests(void);
void NonMembersFunctionOperatorMultiplicationTests(void);
void NonMembersFunctionOperatorDivisionTests(void);

void EndOfTests(void);

/* helper */
static void TestResultComper(Results results, Results expected_results,
                                            const char *test_name, size_t line);

/*******************************************************************************
************************************ The Main  ********************************/

int main ()
{  
	InitializeComplexTests();
	SetComplexTests();

	// Members Function
	MembersFunctionOperatorPlusTests();
	MembersFunctionOperatorMinusTests();
	MembersFunctionOperatorMultiplicationTests();
	MembersFunctionOperatorDivisionTests();

	// Non - Members Function
	NonMembersFunctionOperatorPlusTests();
	NonMembersFunctionOperatorMinusTests();
	NonMembersFunctionOperatorMultiplicationTests();
	NonMembersFunctionOperatorDivisionTests();

	EndOfTests();
	
	return 0; 
}

/*******************************************************************************
**************************** Initialize Complex Test **************************/

/*	test case: checking all the Complex parameter after initializing
*/
void InitializeComplexTests(void)
{ 
	const char *test_name = "Initialize Complex";
	
	Complex complex_1;
	Complex complex_2(1,1);

	Results expected_results;
	Results results;

	expected_results.isnt_equal = YES;
	expected_results.is_equal  = NO;
	expected_results.real = 0;
	expected_results.imag = 0;

	results.isnt_equal = (complex_1 != complex_2);
	results.is_equal   = (complex_1 == complex_2);
	results.real = complex_1.GetReal();
	results.imag = complex_1.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : "  << "0 + 0i" << 
				 "\nComplex number   : " << complex_1 << std::endl;
}

/*******************************************************************************
**************************** Initialize Complex Test **************************/

/*	test case: checking all the Complex parameter after initializing
*/
void SetComplexTests(void)
{ 
	const char *test_name = "Set Complex";
	
	Complex complex_1;
	Complex complex_2(1,1);

	Results expected_results;
	Results results;

	complex_1.SetReal(1);
	complex_1.SetImag(complex_2.GetImag());

	expected_results.isnt_equal = NO;
	expected_results.is_equal  = YES;
	expected_results.real = complex_2.GetReal();
	expected_results.imag = complex_2.GetImag();

	results.isnt_equal = (complex_1 != complex_2);
	results.is_equal   = (complex_1 == complex_2);
	results.real = complex_1.GetReal();
	results.imag = complex_1.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : "  << complex_2 << 
				 "\nComplex number   : "  << complex_1 << std::endl;
}

/*******************************************************************************
********************* Members Function Operator Plus Tests ********************/

/*	test case: checking all the Complex parameter after initializing
*/
void MembersFunctionOperatorPlusTests(void)
{ 
	const char *test_name = "Members Function Operator (+)";
	
	Complex complex_1(1,1);
	Complex complex_2(1,4);
	Complex expected(2,5);

	Results expected_results;
	Results results;

	complex_1 += complex_2;

	expected_results.isnt_equal = YES;
	expected_results.is_equal  = NO;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (complex_1 != complex_2);
	results.is_equal   = (complex_1 == complex_2);
	results.real = complex_1.GetReal();
	results.imag = complex_1.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << complex_1 << std::endl;
}

/*******************************************************************************
******************** Members Function Operator Minus Tests ********************/

/*	test case: checking all the Complex parameter after initializing
*/
void MembersFunctionOperatorMinusTests(void)
{ 
	const char *test_name = "Members Function Operator (-)";
	
	Complex complex_1(1,1);
	Complex complex_2(3,7);
	Complex expected(-2,-6);

	Results expected_results;
	Results results;

	complex_1 -= complex_2;

	expected_results.isnt_equal = YES;
	expected_results.is_equal  = NO;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (complex_1 != complex_2);
	results.is_equal   = (complex_1 == complex_2);
	results.real = complex_1.GetReal();
	results.imag = complex_1.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << complex_1 << std::endl;
}

/*******************************************************************************
*************** Members Function Operator Multiplication Tests ****************/

/*	test case: checking all the Complex parameter after initializing
*/
void MembersFunctionOperatorMultiplicationTests(void)
{ 
	const char *test_name = "Members Function Operator (*)";
	
	Complex complex_1(1,1);
	Complex complex_2(3,7);
	Complex expected(-4,10);

	Results expected_results;
	Results results;

	complex_1 *= complex_2;

	expected_results.isnt_equal = YES;
	expected_results.is_equal  = NO;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (complex_1 != complex_2);
	results.is_equal   = (complex_1 == complex_2);
	results.real = complex_1.GetReal();
	results.imag = complex_1.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << complex_1 << std::endl;
}
/*******************************************************************************
***************** Members Function Operator Division Tests ********************/

/*	test case: checking all the Complex parameter after initializing
*/
void MembersFunctionOperatorDivisionTests(void)
{ 
	const char *test_name = "Members Function Operator (/)";
	
	Complex complex_1(2,2);
	Complex complex_2(2,2);
	Complex expected(1,0);

	Results expected_results;
	Results results;

	complex_1 /= Complex(2,2);

	expected_results.isnt_equal = YES;
	expected_results.is_equal  = NO;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (complex_1 != complex_2);
	results.is_equal   = (complex_1 == complex_2);
	results.real = complex_1.GetReal();
	results.imag = complex_1.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << complex_1 << std::endl;
}

/*******************************************************************************
***************************** Non Members Function ****************************/


/*******************************************************************************
******************** Non Members Function Operator Plus Tests *****************/

/*	test case: checking all the Complex parameter after initializing
*/
void NonMembersFunctionOperatorPlusTests(void)
{ 
	const char *test_name = "NON - Members Function Operator (+)";
	
	Complex c_result;
	Complex expected(2,5);

	Results expected_results;
	Results results;

	c_result = Complex(1,1) + Complex(1,4);

	expected_results.isnt_equal = NO;
	expected_results.is_equal  = YES;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (c_result != expected);
	results.is_equal   = (c_result == expected);
	results.real = c_result.GetReal();
	results.imag = c_result.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << c_result << std::endl;
}

/*******************************************************************************
******************* Non Members Function Operator Minus Tests *****************/

/*	test case: checking all the Complex parameter after initializing
*/
void NonMembersFunctionOperatorMinusTests(void)
{ 
	const char *test_name = "NON - Members Function Operator (-)";
	
	Complex complex_1(1,1);
	Complex c_result;
	Complex expected(-2,-6);

	Results expected_results;
	Results results;

	c_result = complex_1 - Complex(3,7);

	expected_results.isnt_equal = NO;
	expected_results.is_equal  = YES;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (c_result != expected);
	results.is_equal   = (c_result == expected);
	results.real = c_result.GetReal();
	results.imag = c_result.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << c_result << std::endl;
}

/*******************************************************************************
************** Non Members Function Operator Multiplication Tests *************/

/*	test case: checking all the Complex parameter after initializing
*/
void NonMembersFunctionOperatorMultiplicationTests(void)
{ 
	const char *test_name = "NON - Members Function Operator (*)";
	
	Complex complex_1(1,1);
	Complex complex_2(3,7);
	Complex c_result;
	Complex expected(-4,10);

	Results expected_results;
	Results results;

	c_result = Complex(1,1) * complex_2;

	expected_results.isnt_equal = NO;
	expected_results.is_equal  = YES;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (c_result != expected);
	results.is_equal   = (c_result == expected);
	results.real = c_result.GetReal();
	results.imag = c_result.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << c_result << std::endl;
}
/*******************************************************************************
***************** Members Function Operator Division Tests ********************/

/*	test case: checking all the Complex parameter after initializing
*/
void NonMembersFunctionOperatorDivisionTests(void)
{ 
	const char *test_name = "NON - Members Function Operator (/)";
	
	Complex complex_1(2,2);
	Complex complex_2(2,2);
	Complex c_result;
	Complex expected(1,0);

	Results expected_results;
	Results results;

	c_result = complex_1 / complex_2;

	expected_results.isnt_equal = NO;
	expected_results.is_equal  = YES;
	expected_results.real = expected.GetReal();
	expected_results.imag = expected.GetImag();

	results.isnt_equal = (c_result != expected);
	results.is_equal   = (c_result == expected);
	results.real = c_result.GetReal();
	results.imag = c_result.GetImag();
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	std::cout << "\nExpected complex : " << expected << 
				 "\nComplex number   : " << c_result << std::endl;
}
/*******************************************************************************
******************************* Test Result Comper ****************************/

static void TestResultComper(Results results, Results expected_results,
                                    const char *test_name, size_t line)
{ 
	int flag = 0;

	if(results.isnt_equal != expected_results.isnt_equal)
	{
		printf("\nThe is not equal test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	}
	if(results.is_equal != expected_results.is_equal)
	{
		printf("\nThe isequal test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	} 
	if(results.real != expected_results.real)
	{
		printf("\nThe get real test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	}
	if(results.imag != expected_results.imag)
	{
		printf("\nThe get imag test fail for %s test at line %lu\n",
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