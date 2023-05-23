/*******************************************************************************
*  sorted_list.c                                                               *
*  Author: Ariel                                                               *
*  Reviewer: Nasrat                                                            *
*******************************************************************************/
#include <assert.h> /* assert       */
#include <stdlib.h> /* malloc, free */

#include "dlist.h"
#include "sorted_list.h"

struct sorted_list
{
	dlist_ty *dlist;
	cmp_func_ty cmp_func;
};

/* Function Declaration */
static sorted_list_iter_ty HelperFind(sorted_list_ty *list, sorted_list_iter_ty from,
                                      sorted_list_iter_ty to, const void *to_find);

/***** SortedListCreate *******************************************************/

sorted_list_ty *SortedListCreate(cmp_func_ty cmp_func)
{
	sorted_list_ty *new_sl = NULL;
	
	assert(cmp_func);
	
	new_sl = (sorted_list_ty *)malloc(sizeof(sorted_list_ty));
	
	if( !new_sl )
	{
		return NULL;
	}
	
	new_sl->dlist = DListCreate();
	
	if( !new_sl->dlist )
	{
		free(new_sl);
		new_sl = NULL;
		
		return NULL;
	}
	
	new_sl->cmp_func = cmp_func;
	
	return new_sl;
}

/***** SortedListDestroy ******************************************************/

void SortedListDestroy(sorted_list_ty *list)
{
	assert(list);
	
	DListDestroy(list->dlist);
	list->dlist = NULL;
	
	list->cmp_func = NULL;
	
	free(list);
	list = NULL;
}

/***** SortedListBegin ********************************************************/

sorted_list_iter_ty SortedListBegin(const sorted_list_ty *list)
{
	sorted_list_iter_ty ret = {0};
	
	assert(list);
	assert(list->dlist);
	
	ret.dlist_iter = DListBegin(list->dlist);
	DEBUG_ONLY(ret.list = (sorted_list_ty *)list;)
	
	return ret;
}

/***** SortedListEnd **********************************************************/

sorted_list_iter_ty SortedListEnd(const sorted_list_ty *list)
{
	sorted_list_iter_ty ret = {0};
	
	assert(list);
	assert(list->dlist);
	
	ret.dlist_iter = DListEnd(list->dlist);
	DEBUG_ONLY(ret.list = (sorted_list_ty *)list;)
	
	return ret;
}

/***** SortedListNext *********************************************************/

sorted_list_iter_ty SortedListNext(const sorted_list_iter_ty iter)
{
	sorted_list_iter_ty ret = {0};
	
	assert(iter.dlist_iter);
	assert(DListNext(iter.dlist_iter));
	
	ret.dlist_iter = DListNext(iter.dlist_iter);
	DEBUG_ONLY(ret.list = iter.list;)
	
	return ret;
}

/***** SortedListPrev *********************************************************/

sorted_list_iter_ty SortedListPrev(const sorted_list_iter_ty iter)
{
	sorted_list_iter_ty ret = {0};
	
	assert(iter.dlist_iter);
	assert(DListPrev(iter.dlist_iter));
	
	ret.dlist_iter = DListPrev(iter.dlist_iter);
	DEBUG_ONLY(ret.list = iter.list;)
	
	return ret;
}

/***** SortedListGetData ******************************************************/

void *SortedListGetData(sorted_list_iter_ty iter)
{
	assert(iter.dlist_iter);
	assert(DListNext(iter.dlist_iter));
	assert(DListPrev(iter.dlist_iter));
	
	return DListGetData(iter.dlist_iter);
}

/***** SortedListIsEqual ******************************************************/

int SortedListIsEqual(const sorted_list_iter_ty iter1, 
                      const sorted_list_iter_ty iter2)
{
	assert(iter1.dlist_iter);
	assert(iter2.dlist_iter);
	
	return DListIsEqual(iter1.dlist_iter, iter2.dlist_iter);
}

/***** SortedListInsert *******************************************************/

sorted_list_iter_ty SortedListInsert(sorted_list_ty *list, void *new_data)
{
	sorted_list_iter_ty iter_begin = {0};
	sorted_list_iter_ty iter_end = {0};
	sorted_list_iter_ty ret = {0};
	
	assert(list);
	assert(list->dlist);
	
	iter_begin.dlist_iter = DListBegin(list->dlist);
	DEBUG_ONLY(iter_begin.list = list;)
	
	iter_end.dlist_iter = DListEnd(list->dlist);
	DEBUG_ONLY(iter_end.list = list;)
	
	ret = HelperFind(list, iter_begin, iter_end, new_data);
	
	ret.dlist_iter = DListInsert(ret.dlist_iter, new_data);
	DEBUG_ONLY(ret.list = list;)
	
	return ret;
}

/***** SortedListRemove *******************************************************/

sorted_list_iter_ty SortedListRemove(sorted_list_iter_ty iter_to_remove)
{
	sorted_list_iter_ty ret = {0};
	
	assert(iter_to_remove.dlist_iter);
	
	ret.dlist_iter = DListRemove(iter_to_remove.dlist_iter);
	DEBUG_ONLY(ret.list = iter_to_remove.list;)
	DEBUG_ONLY(iter_to_remove.list = NULL;)
	
	return ret;
}

/***** SortedListPopFront *****************************************************/

void *SortedListPopFront(sorted_list_ty *list)
{
	assert(list);
	assert(list->dlist);
	
	return DListPopFront(list->dlist);
}

/***** SortedListPopBack ******************************************************/

void *SortedListPopBack(sorted_list_ty *list)
{
	assert(list);
	assert(list->dlist);
	
	return DListPopBack(list->dlist);
}

/***** SortedListIsEmpty ******************************************************/

int SortedListIsEmpty(const sorted_list_ty *list)
{
	assert(list);
	assert(list->dlist);
	
	return DListIsEmpty(list->dlist);
}

/***** SortedListSize *********************************************************/

size_t SortedListSize(const sorted_list_ty *list)
{
	assert(list);
	assert(list->dlist);
	
	return DListSize(list->dlist);
}

/***** SortedListFind *********************************************************/

sorted_list_iter_ty SortedListFind(sorted_list_ty *list, sorted_list_iter_ty from,
                                   sorted_list_iter_ty to, const void *to_find)
{
	sorted_list_iter_ty ret = {0};
	
	assert(list);
	assert(from.dlist_iter);
	assert(to.dlist_iter);
	assert( from.list == to.list );
	
	ret = SortedListFindIf(list->cmp_func, from, to, to_find);
	DEBUG_ONLY(ret.list = list;)
	
	return ret;
}

/***** SortedListFindIf *******************************************************/

sorted_list_iter_ty SortedListFindIf(cmp_func_ty cmp_func, sorted_list_iter_ty from, 
                     sorted_list_iter_ty to, const void *to_find)
{
	sorted_list_iter_ty iter = {0};
	void *iter_data = NULL;
	
	assert(cmp_func);
	assert(from.dlist_iter);
	assert(to.dlist_iter);
	assert( from.list == to.list );
	
	iter = from;
	
	while( !SortedListIsEqual(iter, to) )
	{
		iter_data = DListGetData(iter.dlist_iter);
		
		if( cmp_func(iter_data, (void *)to_find) == 0 )
		{
			return iter;
		}
		
		iter = SortedListNext(iter);
	}
	
	return to;
}

/***** SortedListForEach ******************************************************/

int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to, 
                      operations_ty op, void *param)
{
	assert(from.dlist_iter);
	assert(to.dlist_iter);
	assert(from.list == to.list);
	assert(op);
	
	return DListForEach(from.dlist_iter, to.dlist_iter, op, param);
}

/***** SortedListMerge ********************************************************/

void SortedListMerge(sorted_list_ty *dest_list, sorted_list_ty *src_list)
{
	sorted_list_iter_ty dest_from = {0};
	sorted_list_iter_ty dest_to = {0};
	sorted_list_iter_ty src_from = {0};
	sorted_list_iter_ty src_to = {0};
	sorted_list_iter_ty dest_find_iter = {0};
	void *src_iter_data = NULL;
	
	assert(dest_list);
	assert(src_list);
	
	dest_from.dlist_iter = DListBegin(dest_list->dlist);
	DEBUG_ONLY(dest_from.list = dest_list;)
	
	dest_to.dlist_iter = DListEnd(dest_list->dlist);
	DEBUG_ONLY(dest_to.list = dest_list;)
	
	/* Initializing all src_list.list = dest, since at the end all of them will
	   belong to dest_list */
	DEBUG_ONLY(src_from.list = dest_list;)
	DEBUG_ONLY(src_to.list = dest_list;)
	DEBUG_ONLY(dest_find_iter.list = dest_list;)
	
	while( !DListIsEmpty(src_list->dlist) )
	{
		src_from.dlist_iter = DListBegin(src_list->dlist);
		src_to.dlist_iter = DListNext(src_from.dlist_iter);
		src_iter_data = DListGetData(src_from.dlist_iter);
		
		dest_find_iter = HelperFind(dest_list, dest_from, dest_to, 
		                                 src_iter_data);
		                                 
		/* If find iterator is the last iterator of dest_list */
		if( SortedListIsEqual(dest_find_iter, dest_to) ) break;
		
		dest_from.dlist_iter = DListSplice(src_from.dlist_iter, src_to.dlist_iter, 
		                                   DListPrev(dest_find_iter.dlist_iter));
		                                   
		DEBUG_ONLY(dest_from.list = dest_list;)            
	}
	
	/* If while loop finished because of break command */
	if( !DListIsEmpty(src_list->dlist) )
	{
		/* Splice the rest of src_list into the last valid iterator in dest_list */
		DListSplice(src_from.dlist_iter, DListEnd(src_list->dlist), 
	                DListPrev(dest_find_iter.dlist_iter));		
	
		DEBUG_ONLY(dest_from.list = dest_list;)
	}
}

/***** HelperFind *************************************************************/

/* Iterated through iterators in the interval [from, to) and compares between
   iterator's data and to_find, in order to find iterator to insert before.
   if data > to_find return iterator
   if data == to_find return next iterator */

static sorted_list_iter_ty HelperFind(sorted_list_ty *list, sorted_list_iter_ty from,
                                      sorted_list_iter_ty to, const void *to_find)
{
	sorted_list_iter_ty iter = {0};
	void *iter_data = NULL;
	
	assert(list);
	assert(from.dlist_iter);
	assert(to.dlist_iter);
	assert( from.list == to.list );
	
	iter = from;
	
	while( !SortedListIsEqual(iter, to) )
	{
		iter_data = DListGetData(iter.dlist_iter);
		
		if( list->cmp_func(iter_data, (void *)to_find) >= 0 )
		{
			return iter;
		}
		
		iter = SortedListNext(iter);
	}
	
	return to;
}
