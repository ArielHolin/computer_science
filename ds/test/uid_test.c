/*******************************************************************************
*  uid_test.c                                                                  *
*  Author: Ariel                                                               *
*  Reviewer: Eli                                                               *  
*******************************************************************************/
#include <stdio.h> /* size_t */
#include <assert.h> /* assert */
#include "uid.h"

#define RED	    "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW	"\033[0;33m"
#define WHITE   "\033[0;37m"

enum is_successful 
{
	ILRD_FALSE = 0, 
	ILRD_TRUE  = 1 
};

enum is_same 
{
	NOT_EQUAL  = 0, 
	EQUAL = 1  
};

/* test functions */
void TestUidCreate(void);
void TestUidIsSame(void);
void TestUidGetBadUid(void);

/* print start & end of tests functions */
static void BeginingOfTests(const char *test_name);
static void EndOfTests(void);


/*******************************************************************************
************************************ The Main  ********************************/

int main ()
{  
	const char *tests_name = "UID Tests";

	BeginingOfTests(tests_name);

	/* The main test functions */ 
	TestUidCreate();
	TestUidIsSame();
	TestUidGetBadUid();


	EndOfTests();
	
	return 0; 
}

/*******************************************************************************
******************************** Test Uid Create ******************************/

void TestUidCreate(void)
{
	uid_ty new_uid = UidCreate();

	printf("\n the new uid time is    : %ld \n",new_uid.time);
	printf("\n the new uid counter is : %lu \n",new_uid.counter);
	printf("\n the new uid pid is     : %u \n",new_uid.pid);

}
/*******************************************************************************
******************************** Test Uid Is Same *****************************/

void TestUidIsSame(void)
{
	const char *test_name = "IS SAME";
	const char *test_object= "uid test";

	int test_is_successful_flag = ILRD_TRUE;

	uid_ty uid_1 = UidCreate();
	uid_ty uid_2 = UidCreate();

	int comper1 = UidIsSame(uid_1,uid_2);
	int comper2 = UidIsSame(uid_1,uid_1);
	int comper3 = UidIsSame(uid_2,uid_2);

	if(NOT_EQUAL != comper1)
	{
		printf(RED);
		printf("\nThe is_empty test fail for %s %s at line %u\n",
		                                      test_name, test_object, __LINE__);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(EQUAL != comper2)
	{
		printf(RED);
		printf("\nThe init counter test fail for %s %s at line %u\n",
		                                      test_name, test_object, __LINE__);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(EQUAL != comper3)
	{
		printf(RED);
		printf("\nThe results.begin test fail for %s %s at line %u\n",
		                                      test_name, test_object, __LINE__);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(test_is_successful_flag == ILRD_TRUE)
	{
		printf(GREEN);
		printf("\n %s %s passed !\n", test_name ,test_object);
	} 
}

/*******************************************************************************
****************************** Test Uid Get Bad Uid ***************************/

void TestUidGetBadUid(void)
{
	const char *test_name = "GET BAD";
	const char *test_object= "uid test";

	int test_is_successful_flag = ILRD_TRUE;
	int comper1 = 0; 

	uid_ty bad_uid = UidGetBadUid();
	uid_ty bad_uid_exp = {0};

	bad_uid_exp.time = 0;
	bad_uid_exp.counter = 0;
	bad_uid_exp.pid = 0;

	comper1 = UidIsSame(bad_uid,bad_uid_exp);

	if(EQUAL != comper1)
	{
		printf(RED);
		printf("\nThe is_empty test fail for %s %s at line %u\n",
		                                      test_name, test_object, __LINE__);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(test_is_successful_flag == ILRD_TRUE)
	{
		printf(GREEN);
		printf("\n %s %s passed !\n", test_name ,test_object);
	} 
}

/*******************************************************************************
******************************* Begining Of Tests *****************************/

static void BeginingOfTests(const char *tests_name)
{
	printf(YELLOW);
	printf("\n______________________ %s _____________________\n\n", tests_name);
}

/*******************************************************************************
********************************** End Of Tests *******************************/

static void EndOfTests(void)
{
	const char *end = "End Of Tests";

	printf(YELLOW);
	printf("\n_________________________ %s _______________________\n\n", end);
}
