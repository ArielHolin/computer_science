/*******************************************************************************
*  slist.c                                                                     *
*  Author: Ariel                                                               *
*  Reviewer: Nisan                                                             *
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "../include/slist.h"

#define SUCCESS 0

struct slist
{
	slist_node_ty *tail;
	slist_node_ty *head;
};

struct slist_node
{
	void *data;
	struct slist_node *next;
};

/******** SlistBegin **********************************************************/

slist_iter_ty SlistBegin(const slist_ty *slist)
{
	assert(slist);
	
	return slist->head->next;
}

/******* SlistEnd *************************************************************/

slist_iter_ty SlistEnd(const slist_ty *slist)
{
	assert(slist);
	
	return slist->tail;
}

/******* SlistNext ************************************************************/

slist_iter_ty SlistNext(slist_iter_ty iterator)
{
	assert(iterator);
	
	return iterator->next;
}

/****** SlistGetData **********************************************************/

void *SlistGetData(slist_iter_ty iterator)
{
	assert(iterator);
	
	return iterator->data;
}

/******* SlistSetData *********************************************************/

void SlistSetData(slist_iter_ty iterator, void *data)
{
	assert(iterator);
	
	iterator->data = data;
}

/******* SlistIsEqual *********************************************************/

bool_ty SlistIsEqual(slist_iter_ty iterator1, slist_iter_ty iterator2)
{
	assert(iterator1);
	assert(iterator2);
	
	return iterator1 == iterator2;
}

/********* SlistCreate ********************************************************/

slist_ty *SlistCreate(void)
{
	/* Allocate memory to a new linked list */
	slist_ty *new_slist = (slist_ty *)malloc(sizeof(slist_ty));
	
	/* Validate memory */
	if ( !new_slist )
	{
		return NULL;
	}
	
	/* Allocate memory to head member of linked list */ 
	new_slist->head = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	/* Validate memory */
	if ( !new_slist->head )
	{
		/* If not created, free linked list and set to NULL */
		free(new_slist);
		new_slist = NULL;
		
		return NULL;
	}
	
	/* Allocate memory to tail member of linked list */
	new_slist->tail = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	/* Validate memory */
	if ( !new_slist->tail )
	{
		/* If not created, free head and set to NULL */
		free(new_slist->head);
		new_slist->head = NULL;
		
		/* Free linked list and set to NULL */
		free(new_slist);
		new_slist = NULL;
		
		return NULL;
	}
	
	/* Head next points to tail */
	new_slist->head->next = new_slist->tail;
	
	/* Tail data holds linked list */
	new_slist->tail->data = new_slist;
	
	/* Tail next points to NULL */
	new_slist->tail->next = NULL;
	
	return new_slist;
}

/********** SlistDestroy ******************************************************/

void SlistDestroy(slist_ty *slist)
{
	/* Initialize begin iterator */ 
	slist_iter_ty begin = SlistBegin(slist);
	
	/* Initialize end iterator */
	slist_iter_ty end = SlistEnd(slist);
	
	/* Validate slist */
	assert(slist);
	
	/* As long as begin != end */
	while( !SlistIsEqual(begin, end) )
	{
		/* Remove begin */
		SlistRemove(begin);
		
		/* Update begin iterator */
		begin = SlistBegin(slist);
		
		/* Update end iterator */
		end = SlistEnd(slist);
	}
	
	/* Destroy begin */
	begin = NULL;
	
	/* free linked list */
	free(slist->head);
	slist->head = NULL;
	
	free(slist->tail);
	slist->tail = NULL;
	
	free(slist);
	slist = NULL;
}

/********* SlistInsert ********************************************************/

slist_iter_ty SlistInsert(void *element, slist_iter_ty iter)
{
	/* Create new node */
	slist_node_ty *new_node = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	/* Validate iter */
	assert(iter);
	
	/* If node wasn't created */
	if ( !new_node )
	{
		/* Find dummy iterator */
		while ( iter->next )
		{
			iter = SlistNext(iter);
		}
		
		/* Return dummy */
		return iter;
	}
	
	/* Assign data of iterator into new_node */
	new_node->data = iter->data;
	/* Assign new element into iterator */
	iter->data = element;
	
	/* Switch between new node and iterator */
	new_node->next = iter->next;
	iter->next = new_node;
	
	/* If new node is the new dummy */
	if ( !new_node->next )  
	{
		/* Update slist tails */
		((slist_ty *)(new_node->data))->tail = new_node;
	}
	
	/* Return inserted iterator */
	return iter;
}

/******** SlistRemove *********************************************************/

slist_iter_ty SlistRemove(slist_iter_ty iter)
{
	/* Hold next iterator */
	slist_iter_ty next_iter = SlistNext(iter);
	
	/* Validate iterator */
	assert(iter);
	
	/* Assign next iterator to iter */
	iter->data = next_iter->data;
	iter->next = next_iter->next;
	
	/* Remove next iterator */
	free(next_iter);
	next_iter = NULL;
	
	/* If iterator is the new dummy */
	if ( !iter->next )  
	{
		/* Update slist tail */
		((slist_ty *)(iter->data))->tail = iter;
	}
	
	/* Return next iterator */
	return iter;
}

/******** SlistFind ***********************************************************/

slist_iter_ty SlistFind(slist_iter_ty from, slist_iter_ty to, 
                        is_match_func_ty match_func, void *param)
{
	/* Validate from and match_func */
	assert(from);
	assert(match_func);
	
	/* As long as from != to */
	while( !SlistIsEqual(from, to) )
	{
		/* Check if match_func return TRUE on current iterator */
		if ( match_func(SlistGetData(from), param) )
		{
			/* If TRUE, return current iterator */
			return from;
		}
		
		/* Else, update current iterator */
		from = SlistNext(from);
	}
	
	/* If no iterator was found, return to iterator */
	return to;
}

/******* SlistForEach *********************************************************/

int SlistForEach(slist_iter_ty from, slist_iter_ty to, 
                 action_func_ty action_func, void *param)
{
	/* Initialize result variable with SUCCESS */
	int result = SUCCESS;
	
	/* Validate from and action_func */
	assert(from);
	assert(action_func);
	
	/* As long as from != to and action_func applied successfully */
	while( (!SlistIsEqual(from, to)) && (SUCCESS == result) )
	{
		/* Apply action_func on current iterator */
		result = action_func(SlistGetData(from), param);
		
		/* Update current iterator */
		from = SlistNext(from);
	}
	
	/* Return result */
	return result;
}

/******** SlistCount **********************************************************/

size_t SlistCount(const slist_ty *slist)
{
	/* Initialize counter variable to 0 */
	size_t counter = 0;
	/* Initialize first iterator in linked list */
	slist_iter_ty iter = SlistBegin(slist);
	
	/* Validate slist */
	assert(slist);
	
	/* As long as iterator hasn't reached dummt iterator */
	while ( !SlistIsEqual(iter, SlistEnd(slist)) )
	{
		/* Increment counter */
		++counter;
		/* Update iterator to next iterator */
		iter = SlistNext(iter);
	}
	
	/*  Return counter */
	return counter;
}

/******* SlistIsEmpty *********************************************************/

bool_ty SlistIsEmpty(const slist_ty *slist)
{
	/* Validate slist */
	assert(slist);
	
	/* If first iterator == last iterator return TRUE */
	return SlistIsEqual(SlistBegin(slist), SlistEnd(slist));
}

/******* SlistMerge ***********************************************************/

slist_ty *SlistMerge(slist_ty *dst,slist_ty *src)
{
	slist_iter_ty dst_end = NULL;
	slist_iter_ty src_begin = NULL;
	slist_iter_ty src_end = NULL;
	
	slist_node_ty *new_node = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	if( !new_node )
	{
		return NULL;
	}
	
	assert(dst);
	assert(src);
	
	dst_end = SlistEnd(dst);
	src_begin = SlistBegin(src);
	src_end = SlistEnd(src);
	new_node->data = src;
	
	/* Update Next of dst dummy iterator */
	dst_end->next = src_begin;
	/* Remove dummy iterator of dst */
	SlistRemove(dst_end);	
	/* Update data of src dummy */
	src_end->data = dst;
	/* Update tail of dst */
	dst->tail = src_end;
	
	/* Update tail of src */
	src->tail = new_node;
	/* Update src slist */
	src->head->next = src->tail;
	src->head->next->next = NULL;
	
	return dst;
}
