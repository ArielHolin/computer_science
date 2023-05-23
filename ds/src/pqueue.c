/*******************************************************************************
*  pqueue.c                                                                    *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <assert.h> /* assert       */
#include <stdlib.h> /* malloc, free */

#include "sorted_list.h"
#include "pqueue.h"

struct pqueue
{
	sorted_list_ty *list;
};

typedef struct match_adapter
{
	void *data;
	is_match_ty match_func;
}match_adapter_ty;

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

static int MatchToCompare(const void *data, const void *strct);

/***** PQCreate ***************************************************************/

pqueue_ty *PQCreate(cmp_func_ty cmp_func)
{
	pqueue_ty *new_pq = (pqueue_ty *)malloc(sizeof(pqueue_ty));
	
	if( !new_pq )
	{
		return NULL;
	}
	
	assert(cmp_func);
	
	new_pq->list = SortedListCreate(cmp_func);
	
	if( !new_pq->list )
	{
		free(new_pq);
		new_pq = NULL;
	}
	
	return new_pq;
}

/***** PQDestroy **************************************************************/

void PQDestroy(pqueue_ty *pqueue)
{
	assert(pqueue);
	
	if( pqueue->list )
	{
		SortedListDestroy(pqueue->list);
		
		free(pqueue);
		pqueue = NULL;
	}
}

/***** PQEnqueue **************************************************************/

int PQEnqueue(pqueue_ty *pqueue, void *data)
{
	sorted_list_iter_ty insert_res = {0};
	sorted_list_iter_ty end_list = {0};
	
	assert(pqueue);
	assert(pqueue->list);
	
	end_list = SortedListEnd(pqueue->list);
	
	insert_res = SortedListInsert(pqueue->list, data);
	
	if( SortedListIsEqual(end_list, insert_res) ) return ILRD_FAILURE;
	
	return ILRD_SUCCESS; 
}

/***** PQDequeue **************************************************************/

void *PQDequeue(pqueue_ty *pqueue)
{	
	assert(pqueue);
	assert(pqueue->list);
	assert( !SortedListIsEmpty(pqueue->list) );
	
	return SortedListPopBack(pqueue->list);
}

/***** PQPeek *****************************************************************/

void *PQPeek(const pqueue_ty *pqueue)
{
	sorted_list_iter_ty top_iter = {0};
	
	assert(pqueue);
	assert(pqueue->list);
	assert( !SortedListIsEmpty(pqueue->list) );
	
	top_iter = SortedListPrev(SortedListEnd(pqueue->list));
	
	return SortedListGetData(top_iter);
}

/***** PQSize *****************************************************************/

size_t PQSize(const pqueue_ty *pqueue)
{
	assert(pqueue);
	assert(pqueue->list);
	
	return SortedListSize(pqueue->list);
}

/***** PQIsEmpty **************************************************************/

int PQIsEmpty(const pqueue_ty *pqueue)
{
	assert(pqueue);
	assert(pqueue->list);
	
	return SortedListIsEmpty(pqueue->list);
}

/***** PQClear ****************************************************************/

void PQClear(pqueue_ty *pqueue)
{
	sorted_list_iter_ty begin = {0};
	sorted_list_iter_ty end = {0};
	
	assert(pqueue);
	assert(pqueue->list);
	
	begin = SortedListBegin(pqueue->list);
	end = SortedListEnd(pqueue->list);
	
	while( !SortedListIsEqual(begin, end) )
	{
		SortedListPopFront(pqueue->list);
		
		begin = SortedListBegin(pqueue->list);
	}
}

/***** PQErase ****************************************************************/

void *PQErease(pqueue_ty *pqueue, is_match_ty is_match_func, void *user_data)
{
	sorted_list_iter_ty ret_iter = {0};
	sorted_list_iter_ty begin = {0};
	sorted_list_iter_ty end = {0};
	match_adapter_ty match_adapter = {0};
	void *erased_data = NULL;

	assert(pqueue);
	assert(pqueue->list);
	assert(is_match_func);
	
	begin = SortedListBegin(pqueue->list);
	end = SortedListEnd(pqueue->list);
	
	match_adapter.data = user_data;
	match_adapter.match_func = is_match_func;
	
	ret_iter = SortedListFindIf(MatchToCompare, begin, end, &match_adapter);
	
	if( SortedListIsEqual(ret_iter, end) ) return NULL;
	
	erased_data = SortedListGetData(ret_iter);
	
	SortedListRemove(ret_iter);
	
	return erased_data;
}

/***** PQMatchToCompare *******************************************************/

static int MatchToCompare(const void *data, const void *strct)
{
	int res = ((match_adapter_ty *)strct)->match_func(data, 
	                                         ((match_adapter_ty *)strct)->data);
	
	return ( (0 == res) ? -1 : 0 );
}
