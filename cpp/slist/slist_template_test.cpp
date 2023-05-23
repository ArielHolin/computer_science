/*******************************************************************************
 *  slist_template_test.cpp                                                    *
 *  Author: Ariel                                                              *
 *  Reviewer: Liel                                                             *
 * ****************************************************************************/
#include <cstdio> //printf

#include "slist_template.hpp"

struct Results
{  
	bool is_empty;
    int data;
	size_t q_size;		
};

static void IntegratedTest(void);
static void TestResultComper(Results results, Results expected_results,
                                            const char *test_name, size_t line);

using namespace hrd20;

int main()
{
	IntegratedTest();
	
}

static void IntegratedTest(void)
{
	const char* TEST_NAME = "IntegratedTest";
	const size_t TEST_SIZE = 10;

	SList<int> slist;
	Results results = { slist.IsEmpty(), 0, slist.Size() };
	Results exp_results = { true, 0, 0 };

	TestResultComper(results, exp_results, TEST_NAME, __LINE__);

	exp_results.is_empty = false;
	for (size_t i = 0; i < TEST_SIZE; ++i)
	{
		slist.PushFront(static_cast<int>(i));
		exp_results.data = static_cast<int>(i);
		++exp_results.q_size;

		results.is_empty = slist.IsEmpty();
		results.data = slist.Peek();
		results.q_size = slist.Size(); 

		TestResultComper(results, exp_results, TEST_NAME, __LINE__);
	}

	for (size_t i = TEST_SIZE - 1; i > 0; --i)
	{
		exp_results.data = static_cast<int>(i);

		results.is_empty = slist.IsEmpty();
		results.data = slist.Peek();
		results.q_size = slist.Size(); 

		TestResultComper(results, exp_results, TEST_NAME, __LINE__);
		
		slist.PopFront();
		--exp_results.q_size;
	}
	
	
}

static void TestResultComper(Results results, Results expected_results,
                                            const char *test_name, size_t line)
{ 
	int flag = 0;
	if(results.is_empty != expected_results.is_empty)
	{
		printf("\nThe is_empty test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	}
	if(results.q_size != expected_results.q_size)
	{
		printf("\nThe init counter test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	} 
	if(results.data != expected_results.data)
	{
		printf("\nThe get_data test fail for %s test at line %lu\n",
		                                                       test_name, line);
		flag = 1;
	} 
	if(0 == flag)
		printf("test %s: OK\n", test_name);
}


