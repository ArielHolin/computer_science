/*******************************************************************************
*  Queue.c                                                                     *
*  Author: Ariel                                                               *
*  Reviewer: Nisan                                                             *
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <stddef.h> /* size_t       */

#include "queue.h"
#include "slist.h"

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

struct queue
{
	slist_ty *slist;
};

/**** QueueCreate *************************************************************/

queue_ty *QueueCreate(void)
{
	queue_ty *new_queue = (queue_ty *)malloc(sizeof(queue_ty));
	
	if( !new_queue )
	{
		return NULL;
	}
	
	new_queue->slist = SlistCreate();
	
	return new_queue;
}

/**** QueueDestroy ************************************************************/

void QueueDestroy(queue_ty *queue)
{
	assert(queue);
	
	SlistDestroy(queue->slist);
	
	free(queue);
}

/**** QueueIsEmpty ************************************************************/

int QueueIsEmpty(const queue_ty *queue)
{
	assert(queue);
	
	return SlistIsEmpty(queue->slist);
}

/**** QueuePeek ***************************************************************/

void *QueuePeek(const queue_ty *queue)
{
	void *ret = NULL;
	
	assert(queue);
	assert(!QueueIsEmpty(queue));
	
	ret = SlistGetData(SlistBegin(queue->slist));
	
	return ret;
}

/**** QueueEnqueue ************************************************************/

int QueueEnqueue(queue_ty *queue, void *element)
{
	slist_iter_ty slist_end = NULL;
	slist_iter_ty ret = NULL;
	
	assert(queue);
	
	slist_end = SlistEnd(queue->slist);
	ret = SlistInsert(element, SlistEnd(queue->slist));
	
	if( !SlistIsEqual(ret, slist_end) ) /* In case of success ret should be
	                                       equal to previos slist_end */
	{
		return FAIL;
	}
	
	return SUCCESS;
}

/**** QueueDequeue ************************************************************/

void QueueDequeue(queue_ty *queue)
{
	slist_iter_ty slist_begin = NULL;
	
	assert(queue);
	
	slist_begin = SlistBegin(queue->slist);
	SlistRemove(slist_begin);
}

/**** QueueSize ***************************************************************/

size_t QueueSize(const queue_ty *queue)
{	
	assert(queue);
	
	return SlistCount(queue->slist);
}

/**** QueueAppend *************************************************************/

queue_ty *QueueAppend(queue_ty *q_dest, queue_ty *q_src)
{
	q_dest->slist = SlistMerge(q_dest->slist, q_src->slist);
	
	return q_dest;
}
