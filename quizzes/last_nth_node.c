/*******************************************************************************
*  last_nth_node.c quiz                                                        *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h>  /* printf */

#include "slist.h"

#define LIST_SIZE 5

slist_iter_ty FindLastNthNode(slist_ty *slist, size_t n);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	slist_ty *new_slist = SlistCreate();
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	Test(elements[0], *(size_t *)SlistGetData(FindLastNthNode(new_slist, 5)),
	     "TestFindLastNthNode()", __FILE__, __LINE__);
	Test(elements[1], *(size_t *)SlistGetData(FindLastNthNode(new_slist, 4)),
	     "TestFindLastNthNode()", __FILE__, __LINE__);
	Test(elements[2], *(size_t *)SlistGetData(FindLastNthNode(new_slist, 3)),
	     "TestFindLastNthNode()", __FILE__, __LINE__);
	Test(elements[3], *(size_t *)SlistGetData(FindLastNthNode(new_slist, 2)),
	     "TestFindLastNthNode()", __FILE__, __LINE__);
	Test(elements[4], *(size_t *)SlistGetData(FindLastNthNode(new_slist, 1)),
	     "TestFindLastNthNode()", __FILE__, __LINE__);
	     
	SlistDestroy(new_slist);
	
	return 0;
}

slist_iter_ty FindLastNthNode(slist_ty *slist, size_t n)
{
	slist_iter_ty ret_iter = NULL;
	slist_iter_ty gap_iter = NULL;
	size_t i = 0;
	
	assert(slist);
	
	ret_iter = SlistBegin(slist);
	gap_iter = SlistBegin(slist);
	
	for( i = 0; i < n+1; ++i )
	{
		gap_iter = SlistNext(gap_iter);
	}
	
	while( gap_iter )
	{
		ret_iter = SlistNext(ret_iter);
		gap_iter = SlistNext(gap_iter);
	}
	
	return ret_iter;
}

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
