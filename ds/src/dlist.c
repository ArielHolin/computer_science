/*******************************************************************************
*  dlist.c                                                                     *
*  Author: Ariel                                                               *
*  Reviewer: Maayan                                                            *
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "dlist.h" 

struct dlist
{
	struct dlist_node *head;
	struct dlist_node *tail;
};

struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
};

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

/***** DListBegin *************************************************************/

dlist_iter_ty DListBegin(const dlist_ty *list)
{
	assert(list);
	
	return list->head->next;
}

/***** DListEnd ***************************************************************/

dlist_iter_ty DListEnd(const dlist_ty *list)
{
	assert(list);
	
	return list->tail;
}

/***** DListNext **************************************************************/

dlist_iter_ty DListNext(const dlist_iter_ty iter)
{
	assert(iter);
	assert(iter->next);
	
	return iter->next;
}

/***** DListPrev **************************************************************/

dlist_iter_ty DListPrev(const dlist_iter_ty iter)
{
	assert(iter);
	assert(iter->prev);
	
	return iter->prev;
}

/***** DListGetData ***********************************************************/

void *DListGetData(dlist_iter_ty iter)
{
	assert(iter);
	assert(iter->next);
	assert(iter->prev);
	
	return iter->data;
}

/***** DListSetData ***********************************************************/

void DListSetData(dlist_iter_ty iter, void *data)
{
	assert(iter);
	assert(iter->next);
	assert(iter->prev);
	
	iter->data = data;
}

/***** DListIsEqual ***********************************************************/

int DListIsEqual(const dlist_iter_ty iter1, const dlist_iter_ty iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

/***** DListCreate ************************************************************/

dlist_ty *DListCreate(void)
{
	dlist_ty *new_dlist = (dlist_ty *)malloc(sizeof(dlist_ty));
	
	if( !new_dlist )
	{
		return NULL;
	}
	
	new_dlist->head = (dlist_iter_ty)malloc(sizeof(struct dlist_node));
	
	if( !new_dlist->head )
	{
		free(new_dlist);
		new_dlist = NULL;
		
		return NULL;
	}
	
	new_dlist->tail = (dlist_iter_ty)malloc(sizeof(struct dlist_node));
	
	if( !new_dlist->tail )
	{
		free(new_dlist->head);
		new_dlist->head = NULL;
		
		free(new_dlist);
		new_dlist = NULL;
		
		return NULL;
	}
	
	new_dlist->head->prev = NULL;
	new_dlist->head->next = new_dlist->tail;
	
	new_dlist->tail->prev = new_dlist->head;
	new_dlist->tail->next = NULL;
	
	return new_dlist;
}

/***** DListDestroy ***********************************************************/

void DListDestroy(dlist_ty *list)
{
	dlist_iter_ty begin = NULL;
	dlist_iter_ty end = NULL;
	
	assert(list);
	
	begin = DListBegin(list);
	end = DListEnd(list);
	
	while( !DListIsEqual(begin, end) )
	{
		DListRemove(begin);
		
		begin = DListBegin(list);
	}
	
	begin = NULL;
	
	free(list->head);
	list->head = NULL;
	
	free(list->tail);
	list->tail = NULL;
	
	free(list);
	list = NULL;	
}

/***** DListInsert ************************************************************/

dlist_iter_ty DListInsert(dlist_iter_ty iter, void *element)
{
	dlist_iter_ty prev_node = NULL;
	dlist_iter_ty new_node = NULL;
	
	assert(iter);
	assert(iter->prev);
	
	prev_node = iter->prev;
	
	new_node = (dlist_iter_ty)malloc(sizeof(struct dlist_node));
	
	if( !new_node )
	{
		while( iter->next )
		{
			iter = iter->next;
		}
		
		return iter;
	}
	
	new_node->data = element;
	new_node->prev = prev_node;
	new_node->next = iter;
	
	prev_node->next = new_node;
	iter->prev = new_node;
	
	return new_node;
}

/***** DListPushFront *********************************************************/

dlist_iter_ty DListPushFront(dlist_ty *list, void *element)
{
	dlist_iter_ty begin = NULL;
	dlist_iter_ty new_node = NULL;
	
	assert(list);
	
	begin = DListBegin(list);
	
	new_node = (dlist_iter_ty)malloc(sizeof(struct dlist_node));
	
	if( !new_node )
	{
		return list->tail;
	}
	
	new_node->data = element;
	new_node->prev = list->head;
	new_node->next = begin;
	
	list->head->next = new_node;
	begin->prev = new_node;
	
	return new_node;
}

/***** DListPushBack **********************************************************/

dlist_iter_ty DListPushBack(dlist_ty *list, void *element)
{
	dlist_iter_ty iter_before_end = NULL;
	dlist_iter_ty new_node = NULL;
	
	assert(list);
	
	iter_before_end = DListPrev(DListEnd(list));
	
	new_node = (dlist_iter_ty)malloc(sizeof(struct dlist_node));
	
	if( !new_node )
	{
		return list->tail;
	}
	
	new_node->data = element;
	new_node->prev = iter_before_end;
	new_node->next = list->tail;
	
	list->tail->prev = new_node;
	iter_before_end->next = new_node;
	
	return new_node;	
}

/***** DListRemove ************************************************************/

dlist_iter_ty DListRemove(dlist_iter_ty iter_to_remove)
{
	dlist_iter_ty prev_node = NULL;
	dlist_iter_ty next_node = NULL;
	
	assert(iter_to_remove);
	assert(iter_to_remove->next);
	assert(iter_to_remove->prev);
	
	prev_node = DListPrev(iter_to_remove);
	next_node = DListNext(iter_to_remove);
	
	prev_node->next = next_node;
	next_node->prev = prev_node;
	
	free(iter_to_remove);
	iter_to_remove = NULL;
	
	return next_node;
}

/***** DListPopFront **********************************************************/

void *DListPopFront(dlist_ty *dlist)
{
	dlist_iter_ty begin = NULL;
	void *ret = NULL;
	
	assert(dlist);
	
	begin = DListBegin(dlist);
	
	ret = DListGetData(begin);
	
	DListRemove(begin);
	
	return ret;
}

/***** DListPopBack ***********************************************************/

void *DListPopBack(dlist_ty *dlist)
{
	dlist_iter_ty last_node = NULL;
	void *ret = NULL;
	
	assert(dlist);
	
	last_node = DListPrev(DListEnd(dlist));
	
	ret = DListGetData(last_node);
	
	DListRemove(last_node);
	
	return ret;
}

/***** DListIsEmpty ***********************************************************/

int DListIsEmpty(const dlist_ty *dlist)
{
	dlist_iter_ty begin = NULL;
	dlist_iter_ty end = NULL;
	
	assert(dlist);
	
	begin = DListBegin(dlist);
	end = DListEnd(dlist);
	
	return DListIsEqual(begin, end);
}

/***** DListSize **************************************************************/

size_t DListSize(const dlist_ty *dlist)
{
	dlist_iter_ty runner_iter = NULL;
	dlist_iter_ty end = NULL;
	size_t counter = 0;
	
	assert(dlist);
	
	runner_iter = DListBegin(dlist);
	end = DListEnd(dlist);
	
	while( !DListIsEqual(runner_iter, end) )
	{
		++counter;
		runner_iter = DListNext(runner_iter);
	}
	
	return counter;
}

/***** DListFind **************************************************************/

dlist_iter_ty DListFind(dlist_iter_ty from, dlist_iter_ty to, 
                        is_match_func_ty match, void *param)
{
	void *iter_data = NULL;
	dlist_iter_ty iter = NULL;
	
	assert(from);	
	assert(to);
	assert(match);
	
	iter = from;
	
	while( !DListIsEqual(iter, to) )
	{
		iter_data = DListGetData(iter);
		
		if ( match(iter_data, param) )
		{
			return iter;
		}
		
		iter = DListNext(iter);
	}
	
	return to;
}

/***** DListMultiFind *********************************************************/

int DListMultiFind(dlist_iter_ty from, dlist_iter_ty to, 
	               is_match_func_ty match, void *param, dlist_ty *output_dlist)
{
	void *iter_data = NULL;
	dlist_iter_ty insert_node = NULL;
	dlist_iter_ty output_dlist_end = NULL;
	dlist_iter_ty iter = NULL;
	
	assert(from);
	assert(match);
	assert(output_dlist);
	
	iter = from;
	output_dlist_end = DListEnd(output_dlist);
	
	while( !DListIsEqual(iter, to) )
	{
		iter_data = DListGetData(iter);
		
		if( match(iter_data, param) )
		{
			insert_node = DListPushBack(output_dlist, iter_data);
			
			if( DListIsEqual( insert_node, output_dlist_end ) )
			{
				return ILRD_FAILURE;
			}
		}
		
		iter = DListNext(iter);
	}
	
	return ILRD_SUCCESS;
}

/***** DListForEach ***********************************************************/

int DListForEach(dlist_iter_ty from, dlist_iter_ty to, operation_ty op, 
                 void *param)
{
	dlist_iter_ty iter = NULL;
	void *iter_data = NULL;
	int result = ILRD_SUCCESS;
	
	assert(from);
	assert(op);
	
	iter = from;
	
	while( (!DListIsEqual(iter, to)) && (ILRD_SUCCESS == result) )
	{
		iter_data = DListGetData(iter);
		
		result = op(iter_data, param);
		
		iter = DListNext(iter);
	}
	
	return result;
}

/***** DListSplice ************************************************************/

dlist_iter_ty DListSplice(dlist_iter_ty from, dlist_iter_ty to, 
						  dlist_iter_ty dest)
{
	dlist_iter_ty prev_from = NULL;
	dlist_iter_ty prev_to = NULL;
	dlist_iter_ty dest_next = NULL;
	
	assert(from);
	assert(to);
	assert(dest && dest->next);
	
	prev_from = DListPrev(from);
	prev_to = DListPrev(to);
	dest_next = DListNext(dest);
	
	prev_from->next = to;
	to->prev = prev_from;
	
	dest->next = from;
	from->prev = dest;
	
	dest_next->prev = prev_to;
	prev_to->next = dest_next;
	
	return from;
}
