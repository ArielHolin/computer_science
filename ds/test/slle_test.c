/*******************************************************************************
*  slle_test.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Maayan                                                            *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* malloc, free */

#include "../include/slle.h"

struct node
{
	void *data;
	struct node *next;
};

static void TestFlip(void);
static void TestHasLoop1(void);
static void TestHasLoop2(void);
static void TestFindIntersection(void);

int main(void)
{
	TestFlip();
	TestHasLoop1();
	TestHasLoop2();
	TestFindIntersection();
	return 0;
}

static void TestFlip(void)
{	
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *result = NULL;
	
	node1 = (node_t *)malloc(sizeof(node_t));
	
	if( !node1 )
	{
		return;
	}
	
	node2 = (node_t *)malloc(sizeof(node_t));
	
	if( !node2 )
	{
		free(node1);
		
		return;
	} 
	
	node3 = (node_t *)malloc(sizeof(node_t));
	
	if( !node3 )
	{
		free(node1);
		free(node2);
		
		return;
	} 
	
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	
	result = Flip(node1);
	
	if( node1 != result->next->next ||
	    node2 != result->next ||
	    node3 != result) 
	{
		printf("TestFlip() fail!\n----------\n");
		
		free(node1);
		free(node2);
		free(node3);
		
		return;
	}
	
	printf("TestFLip() Success!\n----------\n");
	
	free(node1);
	free(node2);
	free(node3);
}

static void TestHasLoop1(void)
{
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	
	node1 = (node_t *)malloc(sizeof(node_t));
	
	if( !node1 )
	{
		return;
	}
	
	node2 = (node_t *)malloc(sizeof(node_t));
	
	if( !node2 )
	{
		free(node1);
		
		return;
	} 
	
	node3 = (node_t *)malloc(sizeof(node_t));
	
	if( !node3 )
	{
		free(node1);
		free(node2);
		
		return;
	} 
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node1;
	
	if( HasLoop(node1) )
	{
		printf("TestHasLoop() Success!\n----------\n");
	}
	
	else
	{
		printf("TestHasLoop() fail!\n----------\n");
	}
	
	free(node1);
	free(node2);
	free(node3);
}

static void TestHasLoop2(void)
{
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	
	node1 = (node_t *)malloc(sizeof(node_t));
	
	if( !node1 )
	{
		return;
	}
	
	node2 = (node_t *)malloc(sizeof(node_t));
	
	if( !node2 )
	{
		free(node1);
		
		return;
	} 
	
	node3 = (node_t *)malloc(sizeof(node_t));
	
	if( !node3 )
	{
		free(node1);
		free(node2);
		
		return;
	} 
	
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	
	if( HasLoop(node1) )
	{
		printf("TestHasLoop() fail!\n----------\n");
	}
	
	else
	{
		printf("TestHasLoop() Success!\n----------\n");
	}
	
	free(node1);
	free(node2);
	free(node3);
}

static void TestFindIntersection(void)
{
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *node4 = NULL;
	node_t *node5 = NULL;
	
	node1 = (node_t *)malloc(sizeof(node_t));
	
	if( !node1 )
	{
		return;
	}
	
	node2 = (node_t *)malloc(sizeof(node_t));
	
	if( !node2 )
	{
		free(node1);
		
		return;
	} 
	
	node3 = (node_t *)malloc(sizeof(node_t));
	
	if( !node3 )
	{
		free(node1);
		free(node2);
		
		return;
	}
	
	node4 = (node_t *)malloc(sizeof(node_t));
	
	if( !node4 )
	{
		free(node1);
		free(node2);
		free(node3);
		
		return;
	} 
	
	node5 = (node_t *)malloc(sizeof(node_t));
	
	if( !node5 )
	{
		free(node1);
		free(node2);
		free(node3);
		free(node4);
		
		return;
	}
	
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	
	node4->next = node5;
	node5->next = NULL;
	
	if( node1 != FindIntersection(node1, node1) ||
	    node2 != FindIntersection(node1, node2) ||
	    node3 != FindIntersection(node3, node1) ||
	    NULL != FindIntersection(node1, node4))
	{
		printf("FindIntersection() fail!\n----------\n");
		return;
	}
	
	printf("FindIntersection() success!\n----------\n");
	
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
}


