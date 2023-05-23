/*******************************************************************************
*  ht.c                                                                        *
*  Author: Ariel                                                               *
*  Reviewer: Phillip                                                           *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "ht.h"
#include "dlist.h"

#define EMPTY     1
#define NON_EMPTY 0

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

struct hash_table
{
    size_t capacity;
    get_key_ty get_key_func;
    hash_func_ty hash_func;
    is_match_func_ty match_func;
    dlist_ty *ht_arr[1];
};

/*********** Helper Functions *************************************************/

static int HTCreateMultiDlists(ht_ty *ht, size_t arr_size);
static void HTDestroyMultiDlists(ht_ty *ht, size_t arr_size);
static dlist_iter_ty HTFindIter(const ht_ty *hash_table, void *key);

/*********** HTCreate *********************************************************/

ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, 
                            get_key_ty get_key_func, ht_match_ty match_func)
{
	ht_ty *new_ht = NULL;
	size_t status = ILRD_SUCCESS;
	
	assert(hash_func);
	assert(get_key_func);
	assert(match_func);
	
	new_ht = (ht_ty *)malloc(OFFSETOF(ht_ty, ht_arr) + 
	                                           (capacity * sizeof(dlist_ty *)));
	                                          
	if(!new_ht)
	{
		return NULL;
	}
	
	status = HTCreateMultiDlists(new_ht, capacity);
	
	if(ILRD_SUCCESS != status)
	{
		return NULL;
	}
	
	new_ht->capacity = capacity;
	new_ht->get_key_func = get_key_func;
	new_ht->hash_func = hash_func;
	new_ht->match_func = (is_match_func_ty)match_func;
	
	return new_ht;
}

static int HTCreateMultiDlists(ht_ty *ht, size_t arr_size)
{
	size_t i = 0;
	
	assert(ht);
	
	for(i = 0; i < arr_size; ++i)
	{
		ht->ht_arr[i] = DListCreate();
		
		if(!ht->ht_arr[i])
		{
			HTDestroyMultiDlists(ht, i);
			
			return ILRD_FAILURE;
		}
	}
	
	return ILRD_SUCCESS;
}

static void HTDestroyMultiDlists(ht_ty *ht, size_t arr_size)
{
	size_t i = 0;
	
	assert(ht);
	
	for(i = 0; i < arr_size; ++i)
	{
		DListDestroy(ht->ht_arr[i]);
		ht->ht_arr[i] = NULL;
	}
}

/*********** HTDestroy ********************************************************/

void HTDestroy(ht_ty *hash_table)
{
	if(!hash_table)
	{
		return;
	}
	
	hash_table->get_key_func = NULL;
	hash_table->hash_func = NULL;
	hash_table->match_func = NULL;
	
	HTDestroyMultiDlists(hash_table, hash_table->capacity);
	
	free(hash_table);
	hash_table = NULL;
}

/*********** HTIsEmpty ********************************************************/

int HTIsEmpty(const ht_ty *hash_table)
{
	size_t i = 0;
	
	assert(hash_table);
	
	for(i = 0; i < hash_table->capacity; ++i)
	{
		if(!DListIsEmpty(hash_table->ht_arr[i]))
		{
			return NON_EMPTY;
		}
	}
	
	return EMPTY;
}

/*********** HTSize ***********************************************************/

size_t HTSize(const ht_ty *hash_table)
{
	size_t counter = 0;
	size_t i = 0;
	
	assert(hash_table);
	
	for(i = 0; i < hash_table->capacity; ++i)
	{
		counter += DListSize(hash_table->ht_arr[i]);
	}
	
	return counter;
}

/*********** HTInsert *********************************************************/

int HTInsert(ht_ty *hash_table, void *data)
{
	void *key = NULL;
	size_t ht_index = 0;
	
	dlist_iter_ty dlist_push_res = NULL;
	dlist_iter_ty dlist_end_iter = NULL;
	
	assert(hash_table);
	assert(data);
	
	key = hash_table->get_key_func(data);
	ht_index = hash_table->hash_func(key);
	ht_index %= hash_table->capacity;
	
	dlist_end_iter = DListEnd(hash_table->ht_arr[ht_index]);
	
	dlist_push_res = DListPushFront(hash_table->ht_arr[ht_index], data);
	
	return DListIsEqual(dlist_end_iter, dlist_push_res);
}

/*********** HTRemove *********************************************************/

void HTRemove(ht_ty *hash_table ,void *key)
{
	dlist_iter_ty find_res = NULL;
	
	assert(hash_table);
	assert(key);
	
	find_res = HTFindIter(hash_table, key);
	
	if(!find_res)
	{
		return;
	}
	
	DListRemove(find_res);	
}

static dlist_iter_ty HTFindIter(const ht_ty *hash_table, void *key)
{
	size_t ht_index = 0;
	dlist_iter_ty dlist_find_res = NULL;
	dlist_iter_ty dlist_begin = NULL;
	dlist_iter_ty dlist_end = NULL;
	
	assert(hash_table);
	assert(key);
	
	ht_index = hash_table->hash_func(key);
	ht_index %= hash_table->capacity;
	
	dlist_begin = DListBegin(hash_table->ht_arr[ht_index]);
	dlist_end = DListEnd(hash_table->ht_arr[ht_index]);
	
	dlist_find_res = DListFind(dlist_begin, dlist_end, hash_table->match_func, 
	                                                                       key);
	                                                                       
	if(DListIsEqual(dlist_find_res, dlist_end))
	{
		return NULL;
	}
	
	return dlist_find_res;
}

/*********** HTFind ***********************************************************/

void *HTFind(const ht_ty *hash_table ,void *key)
{
	size_t ht_index = 0;
	dlist_iter_ty dlist_find_res = NULL;
	dlist_iter_ty dlist_begin = NULL;
	dlist_iter_ty dlist_end = NULL;
	
	assert(hash_table);
	assert(key);
	
	ht_index = hash_table->hash_func(key);
	ht_index %= hash_table->capacity;
	
	dlist_begin = DListBegin(hash_table->ht_arr[ht_index]);
	dlist_end = DListEnd(hash_table->ht_arr[ht_index]);
	
	dlist_find_res = DListFind(dlist_begin, dlist_end, hash_table->match_func, 
	                                                                       key);
	                                                                       
	if(DListIsEqual(dlist_find_res, dlist_end))
	{
		return NULL;
	}
	
	return DListGetData(dlist_find_res);
}

/*********** HTForEach ********************************************************/

int HTForEach(ht_ty *hash_table, ht_operation_ty op, void *param)
{
	size_t i = 0;
	int for_each_res = ILRD_SUCCESS;
	dlist_iter_ty dlist_begin = NULL;
	dlist_iter_ty dlist_end = NULL;
	
	assert(hash_table);
	assert(op);
	
	for(i = 0; i < hash_table->capacity; ++i)
	{
		dlist_begin = DListBegin(hash_table->ht_arr[i]);
		dlist_end = DListEnd(hash_table->ht_arr[i]);
		
		for_each_res = DListForEach(dlist_begin, dlist_end, op, param);
		
		if(ILRD_SUCCESS != for_each_res)
		{
			return for_each_res;
		}
	}
	
	return for_each_res;
}








