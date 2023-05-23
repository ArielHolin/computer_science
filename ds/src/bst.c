/*******************************************************************************
*  bst.c                                                                       *
*  Author: Ariel                                                               *
*  Reviewer: Eva                                                               *
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <stddef.h> /* size_t       */

#include "bst.h"

#define UNVALID_ADD 0xDEADBEAF

#define EQUAL 1

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

enum position
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

struct node
{
    void *data;
    node_ty *children[NUM_OF_CHILDREN];
    node_ty *parent; 
};
 
struct bst
{
    node_ty root_dummy;
    cmp_func_ty cmp_func;
};

static bst_iter_ty BSTGetSmallestInSubTree(bst_iter_ty iter, bst_iter_ty parent);
static bst_iter_ty GetSubRightTreeParent(bst_iter_ty iter);
static bst_iter_ty GetLargestInSubTree(bst_iter_ty iter);
static bst_iter_ty GetSubLeftTreeParent(bst_iter_ty iter);
static bst_iter_ty GetSmallestInSubTree(bst_iter_ty iter);
static void BSTDestroyNode(bst_iter_ty bst_iter);
static void BSTSwapNodes(bst_iter_ty iter1, bst_iter_ty iter2);
static int BSTFindParentDirection(bst_iter_ty iter);

/***** BSTCreate **************************************************************/

bst_ty *BSTCreate(cmp_func_ty cmp_func)
{
	bst_ty *new_bst = NULL;
	
	assert(cmp_func);
	
	/* Allocate memory for new_bst */
	new_bst = (bst_ty *)malloc(sizeof(bst_ty));
	
	/* If allocation failed, return NULL */
	if(!new_bst)
	{
		return NULL;
	}
	
	/* Initialize root_dummy with NULLs */
	new_bst->root_dummy.data = (void *)UNVALID_ADD;
	new_bst->root_dummy.children[LEFT] = NULL;
	new_bst->root_dummy.children[RIGHT] = NULL;
	new_bst->root_dummy.parent = NULL;
	
	/* Initialize cmp_func  */
	new_bst->cmp_func = cmp_func;
	
	/* return pointer to bst_ty */
	return new_bst;
}

/***** BSTDestroy *************************************************************/

void BSTDestroy(bst_ty *bst)
{
	if(!bst)
	{
		return;
	}
	
	if(!BSTIsEmpty(bst))
	{
		BSTDestroyNode((&(bst->root_dummy))->children[LEFT]);
	}
	
	free(bst);
	bst = NULL;
}

/* Helper function - Destroy Node */
static void BSTDestroyNode(bst_iter_ty bst_iter)
{	
	bst_iter_ty parent = NULL;
	int direction = LEFT;
	
	if(!bst_iter)
	{
		return;
	}
	
	if(!bst_iter->children[LEFT] && !bst_iter->children[RIGHT])
	{
		parent = bst_iter->parent;
		direction = BSTFindParentDirection(bst_iter);
		
		parent->children[direction] = NULL;
		
		bst_iter->data = NULL;
		bst_iter->children[LEFT] = NULL;
		bst_iter->children[RIGHT] = NULL;
		bst_iter->parent = NULL;
		
		free(bst_iter);
		bst_iter = NULL;
	}
	
	else
	{
		BSTDestroyNode(bst_iter->children[LEFT]);
		BSTDestroyNode(bst_iter->children[RIGHT]);
		BSTDestroyNode(bst_iter);
	}
}

/***** BSTSize ****************************************************************/

size_t BSTSize(const bst_ty *bst)
{
	bst_iter_ty bst_iter = NULL;
	bst_iter_ty root_dummy = NULL;
	size_t counter = 0;

	assert(bst);
	
	bst_iter = BSTBegin(bst);
	root_dummy = &(((bst_ty *)bst)->root_dummy);
	
	while(!BSTIterIsEqual(bst_iter, root_dummy))
	   {
	   	++counter;
	   	bst_iter = BSTNext(bst_iter);
	   }
	   
	return counter;
}

/***** BSTIsEmpty *************************************************************/

int BSTIsEmpty(const bst_ty *bst)
{
	assert(bst);
	
	return (bst->root_dummy.children[LEFT] == NULL) && 
	                                  (bst->root_dummy.children[RIGHT] == NULL);
}

/***** BSTBegin ***************************************************************/

bst_iter_ty BSTBegin(const bst_ty *bst)
{ 
	bst_iter_ty parent = NULL;
	bst_iter_ty bst_iter = NULL;
	
	assert(bst);
	
	parent = &(((bst_ty *)bst)->root_dummy);
	bst_iter = parent->children[LEFT];
	
	parent = BSTGetSmallestInSubTree(bst_iter, parent); 
	       
	return parent; 
}

/* Helper function - Return smallest value in subtree */
static bst_iter_ty BSTGetSmallestInSubTree(bst_iter_ty iter, bst_iter_ty parent)
{
	bst_iter_ty runner_iter = iter;
	bst_iter_ty runner_parent = parent;
	
	while(runner_iter)
	{
		runner_parent = runner_iter;
		runner_iter = runner_parent->children[LEFT];
	}
	
	return runner_parent;
}

/***** BSTEnd *****************************************************************/

bst_iter_ty BSTEnd(const bst_ty *bst)
{
	assert(bst);
	
	return &(((bst_ty *)bst)->root_dummy);
}

/***** BSTPrev ****************************************************************/

bst_iter_ty BSTPrev(bst_iter_ty iter)
{
	bst_iter_ty runner = NULL;
	
	assert(iter);
	
	runner = iter;
	 
	if(runner->children[LEFT] == NULL)
	{
		return GetSubRightTreeParent(runner);
	}
	            
	runner = runner->children[LEFT];
	
	return GetLargestInSubTree(runner);
}

/* Helper function - Return first left parent, if exists */
static bst_iter_ty GetSubRightTreeParent(bst_iter_ty iter)
{
	while(iter->parent)
		{
	    	if(BSTIterIsEqual(iter->parent->children[RIGHT], iter))
	    	{
	        	return iter->parent;
	        }
	           
	    	iter = iter->parent;
	    }
	       
	return iter;
}

/* Helper function - Return Iterator that holds the greatest value in sub tree */
static bst_iter_ty GetLargestInSubTree(bst_iter_ty iter)
{
	while(iter->children[RIGHT])
	{
		iter = iter->children[RIGHT];
	}
	        
	return iter;
}

/***** BSTNext ****************************************************************/

bst_iter_ty BSTNext(bst_iter_ty iter)
{
	bst_iter_ty runner = NULL;
	
	assert(iter);
	
	runner = iter;
	 
	if(runner->children[RIGHT] == NULL)
	{
		return GetSubLeftTreeParent(runner);
	}
	             
	runner = runner->children[RIGHT];
	    
	return GetSmallestInSubTree(runner);	
}

/* Helper function - Return first right parent, if exists */
static bst_iter_ty GetSubLeftTreeParent(bst_iter_ty iter)
{
	while(iter->parent)
		{
	    	if(BSTIterIsEqual(iter->parent->children[LEFT], iter))
	    	{
	        	return iter->parent;
	        }
	           
	    	iter = iter->parent;
	    }
	       
	return iter;
}

/* Helper function - Return Iterator that holds the smallest value in sub tree */
static bst_iter_ty GetSmallestInSubTree(bst_iter_ty iter)
{
	while(iter->children[LEFT])
	{
		iter = iter->children[LEFT];
	}
	        
	return iter;
}

/***** BSTIterIsEqual *********************************************************/

int BSTIterIsEqual(const bst_iter_ty iter1, const bst_iter_ty iter2)
{		
	return iter1 == iter2;
}

/***** BSTGetData *************************************************************/

void *BSTGetData(const bst_iter_ty iter)
{
	assert(iter);
	
	return iter->data;
}

/***** BSTInsert **************************************************************/

bst_iter_ty BSTInsert(bst_ty *bst, void *new_data)
{
	bst_iter_ty parent = NULL;
	bst_iter_ty node_in_direction = NULL;
	bst_iter_ty new_node = NULL;
	int direction = LEFT;
	int cmp_func_res = 0;
	
	assert(bst);
	
	parent = &(bst->root_dummy);
	node_in_direction = parent->children[direction];
	
	while(node_in_direction)
	{
		cmp_func_res = bst->cmp_func(BSTGetData(node_in_direction), new_data);
	    
	    assert(cmp_func_res != 0);
	    
	    if(cmp_func_res < 0)
	    {
	    	direction = LEFT;
	    }
	    
	    else
	    {
	        direction = RIGHT;
	    }
	        
	    parent = node_in_direction;
	    node_in_direction = parent->children[direction];
	}
	
	/* Allocate new node */
	new_node = (bst_iter_ty)malloc(sizeof(node_ty));
	
	if(!new_node)
	{
		return &(bst->root_dummy);
	}
	
	/* Initialize new_node */
	new_node->data = new_data;
	new_node->parent = parent;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	    
	/* Update the parent's child */
	parent->children[direction] = new_node;
	
	return new_node;
}

/***** BSTFind ****************************************************************/

bst_iter_ty BSTFind(const bst_ty *bst, void *data)
{
	bst_iter_ty parent = NULL;
	bst_iter_ty node_in_direction = NULL;
	int direction = LEFT;
	int cmp_func_res = 0;
	
	assert(bst);
	
	parent = &(((bst_ty *)bst)->root_dummy);
	node_in_direction = parent->children[direction];
	
	while(node_in_direction)
	{
		cmp_func_res = bst->cmp_func(BSTGetData(node_in_direction), data);
		
		if(cmp_func_res < 0)
		{
	    	direction = LEFT;
	    }
	   
	   	if(cmp_func_res > 0)
	   	{
	    	direction = RIGHT;
	    }
	       
	   if(cmp_func_res == 0)
	   {
	       return node_in_direction;
	   }
	       
	   parent = node_in_direction;
	   node_in_direction = parent->children[direction];
	}
	    
    return &(((bst_ty *)bst)->root_dummy);
}

/***** BSTForEach *************************************************************/

int BSTForEach(bst_iter_ty from, bst_iter_ty to, operation_ty op, void *param)
{
	bst_iter_ty iter = NULL;
	void *iter_data = NULL;
	int result = ILRD_SUCCESS;
	
	assert(from);
	assert(op);
	
	iter = from;
	
	while( (!BSTIterIsEqual(iter, to)) && (ILRD_SUCCESS == result) )
	{
		iter_data = BSTGetData(iter);
		
		result = op(iter_data, param);
		
		iter = BSTNext(iter);
	}
	
	return result;	
}

/***** BSTRemove **************************************************************/

void BSTRemove(bst_iter_ty iter)
{ 
	bst_iter_ty next_iter = NULL;
	int direction = LEFT;
	
	assert(iter);
	
	direction = BSTFindParentDirection(iter);
	
	/* Case 1: the node is a leaf */
	if(!iter->children[LEFT] && !iter->children[RIGHT])
	{
		iter->parent->children[direction] = NULL;
		
		iter->data = NULL;
		iter->children[LEFT] = NULL;
		iter->children[RIGHT] = NULL;
		iter->parent = NULL;
		
		free(iter);
		iter = NULL;
		
		return;
	}
	
	/* Case2: The node has one left child */
	if(iter->children[LEFT] && !iter->children[RIGHT])
	{
		next_iter = iter->children[LEFT];
		
		iter->parent->children[direction] = next_iter;
		next_iter->parent = iter->parent;
		
		iter->data = NULL;
		iter->children[LEFT] = NULL;
		iter->children[RIGHT] = NULL;
		iter->parent = NULL;
		
		free(iter);
		iter = NULL;
		return;
	}
	
	/* Case 3: The node has one right child */
	if(!iter->children[LEFT] && iter->children[RIGHT])
	{
		next_iter = iter->children[RIGHT];
		
		iter->parent->children[direction] = next_iter;
		next_iter->parent = iter->parent;
		
		iter->data = NULL;
		iter->children[LEFT] = NULL;
		iter->children[RIGHT] = NULL;
		iter->parent = NULL;
		
		free(iter);
		iter = NULL;
		return;
	}
	
	/* Case4: The node has 2 children */
	next_iter = BSTNext(iter);
	BSTSwapNodes(iter, next_iter);
	BSTRemove(iter);                 
}

/* Helper function - Swapping nodes */
static void BSTSwapNodes(bst_iter_ty iter1, bst_iter_ty iter2)
{
	int iter1_direction = LEFT;
	int iter2_direction = LEFT;
	bst_iter_ty iter1_parent = NULL;
	bst_iter_ty iter2_parent = NULL;
	bst_iter_ty iter1_left_child = NULL;
	bst_iter_ty iter2_left_child = NULL;
	bst_iter_ty iter1_right_child = NULL;
	bst_iter_ty iter2_right_child = NULL;
	bst_iter_ty tmp_iter = NULL;
	
	assert(iter1);
	assert(iter2);
	
	iter1_parent = iter1->parent;
	iter1_left_child = iter1->children[LEFT];
	iter1_right_child = iter1->children[RIGHT];
	
	iter2_parent = iter2->parent;
	iter2_left_child = iter2->children[LEFT];
	iter2_right_child = iter2->children[RIGHT];
	
	tmp_iter = iter1;
	
	iter1_direction = BSTFindParentDirection(iter1);
	iter2_direction = BSTFindParentDirection(iter2);
	
	/* placing iter1 instead of iter2 */
	iter1->parent->children[iter1_direction] = iter2;
	iter2->parent = iter1_parent;
	
	iter1->children[LEFT]->parent = iter2;
	iter2->children[LEFT] = iter1_left_child;
	
	iter1->children[RIGHT]->parent = iter2;
	iter2->children[RIGHT] = iter1_right_child;
	
	/* placing iter2 instead of iter1 */
	tmp_iter->parent = iter2_parent;
	iter2_parent->children[iter2_direction] = tmp_iter;
	
	tmp_iter->children[LEFT] = iter2_left_child;
	if(iter2_left_child)
	{
		iter2_left_child->parent = tmp_iter;
	}
	
	tmp_iter->children[RIGHT] = iter2_right_child;
	if(iter2_right_child)
	{
		iter2_right_child->parent = tmp_iter;
	}
}

/* Helper function - finds in which direction of the parent the child is 
                     located */
static int BSTFindParentDirection(bst_iter_ty iter)
{
	assert(iter);
	assert(iter->parent);
	
	if(BSTIterIsEqual(iter->parent->children[LEFT], iter))
	{
		return LEFT;
	}
	
	return RIGHT;
}
