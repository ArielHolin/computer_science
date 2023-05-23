/*******************************************************************************
*  scheduler_test.c                                                            *
*  Author: Ariel                                                               *
*  Reviewer: Liel                                                              *
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "task.h"
#include "scheduler.h"

#define NON_EMPTY 0
#define EMPTY     1

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAIL = 1
};

static int DummySchedulerFunc(void *param)
{
	return 0;
}

static int SchedulerFuncStop(void *scheduler)
{
	SchedulerStop((scheduler_ty *)scheduler);
	return ILRD_SUCCESS;
}

static int SchedulerFuncTaskErr(void *param)
{
	return TASK_ERROR;
}

void TestSchedulerCreateDestroy(void);
void TestSchedulerSizeIsEmptyClear(void);
void TestSchedulerStop(void);
void TestSchedulerRemove(void);
void TestSchedulerAdd(void);
void TestSchedulerRun(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestSchedulerCreateDestroy();
	TestSchedulerSizeIsEmptyClear();
	TestSchedulerStop();
	TestSchedulerRemove();
	TestSchedulerAdd();
	TestSchedulerRun();
	return 0;
}

/***** TestSchedulerCreate ****************************************************/

void TestSchedulerCreateDestroy(void)
{
	scheduler_ty *new_scheduler = SchedulerCreate();
	
	Test(EMPTY, SchedulerIsEmpty(new_scheduler), 
	     "TestSchedulerCreateDestroy()", __FILE__, __LINE__);
	     
	SchedulerDestroy(new_scheduler);
	
	printf("----------\n");
}

/***** TestSchedulerSizeIsEmptyClear ******************************************/

void TestSchedulerSizeIsEmptyClear(void)
{
	scheduler_ty *new_scheduler = SchedulerCreate();
	int dummy_param = 1;
	
	Test(EMPTY, SchedulerIsEmpty(new_scheduler), 
	     "TestSchedulerIsEmpty()", __FILE__, __LINE__);
	     
	Test(0, SchedulerSize(new_scheduler), "TestSchedulerSize()", __FILE__, 
	     __LINE__);
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	Test(NON_EMPTY, SchedulerIsEmpty(new_scheduler), "TestSchedulerIsEmpty()",
	     __FILE__, __LINE__);
	     
	Test(3, SchedulerSize(new_scheduler), "TestSchedulerSize()", __FILE__, 
	     __LINE__);
	     
	SchedulerClear(new_scheduler);
	
	Test(EMPTY, SchedulerIsEmpty(new_scheduler), "TestSchedulerClear()",
	     __FILE__, __LINE__);
	
	SchedulerDestroy(new_scheduler);
	
	printf("----------\n");
}

/***** TestSchedulerStop ******************************************************/

void TestSchedulerStop(void)
{
	scheduler_ty *new_scheduler = SchedulerCreate();
	status_of_execution_ty run_res = SUCCESS;
	int dummy_param = 1;
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, SchedulerFuncStop, new_scheduler);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	run_res = SchedulerRun(new_scheduler);
	
	Test(STOPPED, run_res, "TestSchedulerStop()", __FILE__, __LINE__);
	
	SchedulerClear(new_scheduler);
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	run_res = SchedulerRun(new_scheduler);
	
	Test(SUCCESS, run_res, "TestSchedulerStop()", __FILE__, __LINE__);
	
	SchedulerDestroy(new_scheduler);
	
	printf("----------\n");
}

/***** TestSchedulerRemove *******************************************************/

void TestSchedulerRemove(void)
{
	scheduler_ty *new_scheduler = SchedulerCreate();
	uid_ty uid1 = {0};
	uid_ty uid2 = {0};
	uid_ty uid3 = {0};
	uid_ty uid4 = {0};
	int dummy_param = 1;
	int remove_status = ILRD_SUCCESS;
	
	uid1 = SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	uid2 = SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	uid3 = SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	remove_status = SchedulerRemove(new_scheduler, uid1);
	
	Test(ILRD_SUCCESS, remove_status, "TestSchedulerRemove()", __FILE__, 
	     __LINE__);
	     
	remove_status = SchedulerRemove(new_scheduler, uid4);
	
	Test(ILRD_FAIL, remove_status, "TestSchedulerRemove()", __FILE__, __LINE__);
	
	remove_status = SchedulerRemove(new_scheduler, uid2);
	
	Test(ILRD_SUCCESS, remove_status, "TestSchedulerRemove()", __FILE__, 
	     __LINE__);
	     
	remove_status = SchedulerRemove(new_scheduler, uid3);
	
	Test(ILRD_SUCCESS, remove_status, "TestSchedulerRemove()", __FILE__, 
	     __LINE__);
	     
	SchedulerDestroy(new_scheduler);
	
	printf("----------\n");
}

/***** TestSchedulerAdd *******************************************************/

void TestSchedulerAdd(void)
{
	scheduler_ty *new_scheduler = SchedulerCreate();
	int dummy_param = 1;
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	Test(1, SchedulerSize(new_scheduler), "TestSchedulerAdd()", __FILE__, 
	     __LINE__);
	     
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	Test(2, SchedulerSize(new_scheduler), "TestSchedulerAdd()", __FILE__, 
	     __LINE__);
	     
	SchedulerDestroy(new_scheduler);
	
	printf("----------\n");
}

/***** TestSchedulerRun *******************************************************/

void TestSchedulerRun(void)
{
	scheduler_ty *new_scheduler = SchedulerCreate();
	status_of_execution_ty run_res = SUCCESS;
	int dummy_param = 1;
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	run_res = SchedulerRun(new_scheduler);
	
	Test(SUCCESS, run_res, "TestSchedulerRun()", __FILE__, __LINE__);
	
	SchedulerClear(new_scheduler);
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, SchedulerFuncStop, new_scheduler);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	
	run_res = SchedulerRun(new_scheduler);
	
	Test(STOPPED, run_res, "TestSchedulerRun()", __FILE__, __LINE__);
	
	SchedulerClear(new_scheduler);
	
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, DummySchedulerFunc, &dummy_param);
	SchedulerAdd(new_scheduler, 1, SchedulerFuncTaskErr, &dummy_param);
	
	run_res = SchedulerRun(new_scheduler);
	
	Test(TASK_ERROR, run_res, "TestSchedulerRun()", __FILE__, __LINE__);
	
	SchedulerClear(new_scheduler);
	
	SchedulerDestroy(new_scheduler);
	
	printf("----------\n");
}

/***** Test Template **********************************************************/

static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num)
{
	if (expected_res == res)
	{
		printf("%s success\n", test_name);
	}
	
	else 
	{
		printf("%s failed in file %s at line %li\n", 
		       test_name, filename, line_num);
	}
}
