/*******************************************************************************
*  slle.c                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Maayan                                                            *
*******************************************************************************/
#include <assert.h>  /* assert */
#include <stddef.h>  /* size_t */

#include "../include/slle.h"

#define ILRD_TRUE  1
#define ILRD_FALSE 0

struct node
{
	void *data;
	struct node *next;
};

static node_t *FindInter(node_t *big_head, node_t *small_head, size_t diff);
static size_t CountNodes(node_t *head);

/******* Flip *****************************************************************/

node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *curr = head;
	node_t *next_node = head->next;
	
	assert(head);
	
	while( next_node )
	{
		curr->next = prev;
		prev = curr;
		curr = next_node;
		next_node = next_node->next;
	}
	
	curr->next = prev;
	
	return curr;
}

/******** HasLoop *************************************************************/

int HasLoop(const node_t *head)
{
	const node_t *hare = head;
	const node_t *tortoise = head;
	
	assert(head);
	
	while( hare->next && hare->next->next )
	{
		hare = hare->next->next;
		tortoise = tortoise->next;
		
		if( hare == tortoise )
		{
			return ILRD_TRUE;
		}
	}
	
	return ILRD_FALSE;
}

/****** FindIntersection ******************************************************/

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t head_1_count = 0;
	size_t head_2_count = 0;
	int diff = 0;
	
	assert(head_1);
	assert(head_2);
	
	head_1_count = CountNodes(head_1);
	head_2_count = CountNodes(head_2);
	
	diff = head_1_count - head_2_count;
	
	if( diff >= 0 )
	{
		return FindInter(head_1, head_2, diff);
	}
	
	diff = -diff;
		
	return FindInter(head_2, head_1, diff);
}

/* Equalizing Number of nodes of big_head and small_head linked lists,
   and then finds first node of intersection, if any. */
static node_t *FindInter(node_t *big_head, node_t *small_head, size_t diff)
{
	while( diff )
		{
			big_head = big_head->next;
			--diff;
		}
		
	while( big_head )
	{
		if( big_head == small_head )
		{
			return big_head;
		}
			
		big_head = big_head->next;
		small_head = small_head->next;
	}
		
	return big_head;
}

/* Counting number of nodes in linked list */
static size_t CountNodes(node_t *head)
{
	size_t counter = 0;
	
	assert(head);
	
	while( head )
	{
		++counter;
		
		head = head->next;
	}
	
	return counter;
}
