/*******************************************************************************
*  rbst.c                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Nisan                                                             *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <assert.h> /* assert       */
#include <stdlib.h> /* malloc, free */

#include "rbst.h"

#define MAX(a,b) ((a > b) ? a : b)

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
    size_t height;
    node_ty *children[NUM_OF_CHILDREN];
};
 
struct rbst
{
    node_ty *root;
    cmp_func_ty cmp_func;
};

static void RBSTDestroyNode(node_ty *node);
static size_t RBSTSizeNode(const node_ty *node);
static void *RBSTFindNode(const node_ty *node, void *data, cmp_func_ty cmp_func);
static void ForEachPostOrder(node_ty *node, operation_ty op, void *param, 
                                                                   int *status);
static void ForEachPreOrder(node_ty *node, operation_ty op, void *param, 
                                                                   int *status);
static void ForEachInOrder(node_ty *node, operation_ty op, void *param, 
                                                                   int *status);
static node_ty *RBSTInsertNode(node_ty *node, void *new_data, cmp_func_ty cmp_func, 
                                                             node_ty *new_node);
static void RBSTUpdateHeight(node_ty *node);
static node_ty *RBSTRemoveNode(node_ty *node, void *data, cmp_func_ty cmp_func);
static void *RBSTNextData(node_ty *node);
static void RBSTUpdateData(node_ty *node, void *data);

/************* Functions for balancing ****************************************/

static node_ty *RBSTBalanceNode(node_ty *node);
static int RBSTHeightNode(const node_ty *node);
static int RBSTGetBalanceFactor(const node_ty *node);
static node_ty *RBSTLeftRotate(node_ty *node, node_ty *pivot);
static node_ty *RBSTRightRotate(node_ty *node, node_ty *pivot);

/************* RBSTCreate *****************************************************/

rbst_ty *RBSTCreate(cmp_func_ty cmp_func)
{
	rbst_ty *new_rbst = NULL;
	
	assert(cmp_func);
	
	new_rbst = (rbst_ty *)malloc(sizeof(rbst_ty));
	
	if(!new_rbst)
	{
		return NULL;
	}
	
	new_rbst->root = NULL;
	new_rbst->cmp_func = cmp_func;
	
	return new_rbst;
}

/************* RBSTDestroy ****************************************************/

void RBSTDestroy(rbst_ty *rbst)
{	
	if(!RBSTIsEmpty(rbst))
	{
		RBSTDestroyNode(rbst->root);
	}
	
	free(rbst);
	rbst = NULL;
}

/* Helper function - Destroy node */
static void RBSTDestroyNode(node_ty *node)
{
	if(!node)
	{
		return;
	}
	
	RBSTDestroyNode(node->children[LEFT]);
	RBSTDestroyNode(node->children[RIGHT]);
	
	node->data = NULL;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	
	free(node);
	node = NULL;
}

/************* RBSTIsEmpty ****************************************************/

int RBSTIsEmpty(const rbst_ty *rbst)
{
	assert(rbst);
	
	return (NULL == rbst->root);
}

/************* RBSTHeight *****************************************************/

size_t RBSTHeight(const rbst_ty *rbst)
{
	assert(rbst);
	assert(rbst->root);
	
	return rbst->root->height;
}

/************* RBSTSize *******************************************************/

size_t RBSTSize(const rbst_ty *rbst)
{
	assert(rbst);
	
	return RBSTSizeNode(rbst->root);
}

/* Helper function - Find size of node */
static size_t RBSTSizeNode(const node_ty *node)
{
	if(!node)
	{
		return 0;
	}
	
	return (1 + (RBSTSizeNode(node->children[LEFT]) + 
	                                      RBSTSizeNode(node->children[RIGHT])));
}

/************* RBSTFind *******************************************************/

void *RBSTFind(const rbst_ty *rbst, void *data)
{	
	assert(rbst);
	assert(data);
	
	return RBSTFindNode(rbst->root, data, rbst->cmp_func);
}

static void *RBSTFindNode(const node_ty *node, void *data, cmp_func_ty cmp_func)
{
	if(!node)
	{
		return NULL;
	}
	
	if(cmp_func(node->data, data) > 0)
	{
		return RBSTFindNode(node->children[RIGHT], data, cmp_func);
	}
	
	if(cmp_func(node->data, data) < 0)
	{
		return RBSTFindNode(node->children[LEFT], data, cmp_func);
	}
	
	return data;
}

/************* RBSTForEach ****************************************************/

int RBSTForEach(rbst_ty *rbst, operation_ty op, void *param, trav_ty trav_order)
{
	int status = ILRD_SUCCESS;
	
	assert(rbst);
	assert(op);
	
	switch(trav_order)
	{
		case PRE_ORDER:
			ForEachPreOrder(rbst->root, op, param, &status);
			return status;
		case IN_ORDER:
			ForEachInOrder(rbst->root, op, param, &status);
			return status;
		case POST_ORDER:
			ForEachPostOrder(rbst->root, op, param, &status);
			return status;
		default:
			return ILRD_FAILURE;
	}
}

/* Helper function - ForEach in post order traversal */
static void ForEachPostOrder(node_ty *node, operation_ty op, void *param, 
                                                                    int *status)
{	
	int local_status = 0;
	
	if(!node)
	{
		return;
	}
	
	ForEachPostOrder(node->children[LEFT], op, param, status);
	if(ILRD_SUCCESS != *status)
	{
		return;
	}
	
	ForEachPostOrder(node->children[RIGHT], op, param, status);
	if(ILRD_SUCCESS != *status)
	{
		return;
	}
	
	local_status =  op(node->data, param);
	
	if(ILRD_SUCCESS != local_status)
	{
		*status = ILRD_FAILURE;
		return;
	}
}

/* Helper function - ForEach in PreOrder traversal */
static void ForEachPreOrder(node_ty *node, operation_ty op, void *param, 
                                                                    int *status)
{
	int local_status = 0;
	
	if(!node)
	{
		return;
	}
	
	local_status = op(node->data, param);
	
	if(ILRD_SUCCESS != local_status)
	{
		*status = ILRD_FAILURE;
		return;
	}
	
	ForEachPreOrder(node->children[LEFT], op, param, status);
	if(ILRD_SUCCESS != *status)
	{
		return;
	}
	
	ForEachPreOrder(node->children[RIGHT], op, param, status);
	if(ILRD_SUCCESS != *status)
	{
		return;
	}
}

/* Helper function - ForEach in InOrder traversal */
static void ForEachInOrder(node_ty *node, operation_ty op, void *param, 
                                                                    int *status)
{
	int local_status = 0;
	
	if(!node)
	{
		return;
	}
	
	ForEachInOrder(node->children[LEFT], op, param, status);
	if(ILRD_SUCCESS != *status)
	{
		return;
	}
	
	local_status = op(node->data, param);
	
	if(ILRD_SUCCESS != local_status)
	{
		*status = ILRD_FAILURE;
		return;
	}
	
	ForEachInOrder(node->children[RIGHT], op, param, status);
	if(ILRD_SUCCESS != *status)
	{
		return;
	}
}

/************* RBSTInsert *****************************************************/

int RBSTInsert(rbst_ty *rbst, void *new_data)
{
	node_ty *new_node = NULL;
	
	assert(rbst);
	assert(new_data);
	
	new_node = (node_ty *)malloc(sizeof(node_ty));
	
	if(!new_node)
	{
		return ILRD_FAILURE;
	}
	
	new_node->data = new_data;
	new_node->height = 0;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	if(!rbst->root)
	{
		rbst->root = new_node;
		return ILRD_SUCCESS;
	}
	
	rbst->root = RBSTInsertNode(rbst->root, new_data, rbst->cmp_func, new_node);
	RBSTUpdateHeight(rbst->root);
	
	return ILRD_SUCCESS;
}

/* Helper function - inserting while traversing nodes */
static node_ty *RBSTInsertNode(node_ty *node, void *new_data, cmp_func_ty cmp_func, 
                                                              node_ty *new_node)
{
	int direction = LEFT;
	int cmp_func_res = 0;
	
	cmp_func_res = cmp_func(node->data, new_data);
	
	assert(0 != cmp_func_res);
	
	if(cmp_func_res > 0)
	{
		direction = RIGHT;
	}
	
	if(!node->children[direction])
	{
		node->children[direction] = new_node;
		RBSTUpdateHeight(node);
		return node;	
	}

	node->children[direction] = RBSTInsertNode(node->children[direction], 
	                                              new_data, cmp_func, new_node);
	RBSTUpdateHeight(node);
	
	node = RBSTBalanceNode(node);
	
	RBSTUpdateHeight(node);
	
	return node;
}

/* Helper function - updating height of node */
static void RBSTUpdateHeight(node_ty *node)
{
	int left_child_height = 0;
	int right_child_height = 0;
	
	if(!node->children[LEFT] && !node->children[RIGHT])
	{
		node->height = 0;
		return;
	}
	
	if(NULL != node->children[LEFT])
	{
		left_child_height = node->children[LEFT]->height;
	}
	
	if(NULL != node->children[RIGHT])
	{
		right_child_height = node->children[RIGHT]->height;
	}
	
	node->height = (1 + MAX(left_child_height, right_child_height));
}

/************* RBSTRemove *****************************************************/

void RBSTRemove(rbst_ty *rbst, void *data)
{	
	assert(rbst);
	assert(data);
	
	rbst->root = RBSTRemoveNode(rbst->root, data, rbst->cmp_func);
	rbst->root = RBSTBalanceNode(rbst->root);
	RBSTUpdateHeight(rbst->root);
}

/* Helper function - Removing while traversing nodes */
static node_ty *RBSTRemoveNode(node_ty *node, void *data, cmp_func_ty cmp_func)
{
	void *next_data = NULL;
	
	/* if node was not found return NULL */
	if(!node)
	{
		return NULL;
	}
	
	/* If data > node->data */
	if(cmp_func(node->data, data) > 0)
	{
		/* Recursively Call the function on the right child */
		node->children[RIGHT] = RBSTRemoveNode(node->children[RIGHT], data, 
		                                                              cmp_func);
		/* Update the node's height */
		RBSTUpdateHeight(node);
		/* Balance the tree */
		node = RBSTBalanceNode(node);	
		RBSTUpdateHeight(node);
	}
	
	/* If data < node->data */
	else if(cmp_func(node->data, data) < 0)
	{
		/* Recursively call the function on the left child */
		node->children[LEFT] = RBSTRemoveNode(node->children[LEFT], data, 
		                                                              cmp_func);
		/* Update the node's height */
		RBSTUpdateHeight(node);
		/* Balance the tree */
		node = RBSTBalanceNode(node);
		RBSTUpdateHeight(node);
	}
	
	/* If node found */
	else
	{
		/* If the node is a leaf */
		if(!node->children[LEFT] && !node->children[RIGHT])
		{
			/* Free the node */
			free(node);
			node = NULL;
		}
		
		/* If the node has only left child */
		else if(node->children[LEFT] && !node->children[RIGHT])
		{
			node->data = node->children[LEFT]->data;
			node->height = node->children[LEFT]->height;
			
			/* Free left child of node */
			free(node->children[LEFT]);
			node->children[LEFT] = NULL;
		}
		
		/* If the node has only right child */
		else if(!node->children[LEFT] && node->children[RIGHT])
		{	
			/* Copy the data of the right child into the found node */
			node->data = node->children[RIGHT]->data;
			node->height = node->children[RIGHT]->height;
			
			/* Free right child of node */
			free(node->children[RIGHT]);
			node->children[RIGHT] = NULL;
		}
		
		/* If the node has two children */
		else
		{	
			/* Find the next data */
			next_data = RBSTNextData(node->children[RIGHT]);
			/* Copy next data into the found node */
			node->data = next_data;
			
			/* Copy the given data into the next node */
			RBSTUpdateData(node->children[RIGHT], data);
			
			/* Call the function recursively on the right child */
			node->children[RIGHT] = RBSTRemoveNode(node->children[RIGHT], data, 
			                                                          cmp_func);
			/* Update node height */
			RBSTUpdateHeight(node);
			
			/* Balance the tree */
			node = RBSTBalanceNode(node);
			
			RBSTUpdateHeight(node);
		}
	}
	
	return node;
}

/* Helper function - Updating data at bottom nodes */
static void RBSTUpdateData(node_ty *node, void *data)
{
	if(!node->children[LEFT])
	{
		node->data = data;
		return;
	}
	
	RBSTUpdateData(node->children[LEFT], data);
}

/* Helper function - Find the next appropriate data at the tree
   The function will be implied on a node with two children, so next data
   will always be down the node */
static void *RBSTNextData(node_ty *node)
{
	if(!node->children[LEFT])
	{
		return node->data;
	}
	
	return RBSTNextData(node->children[LEFT]);
}

/************* Functions for Balancing *****************************************/

/* Balancing nodes */
static node_ty *RBSTBalanceNode(node_ty *node)
{
	int balance_factor = 0;
	
	assert(node);
	
	balance_factor = RBSTGetBalanceFactor(node);
	
	if((balance_factor > 1) && (RBSTGetBalanceFactor(node->children[LEFT]) >= 0))
	{
		node = RBSTRightRotate(node, node->children[LEFT]);
	}
	
	else if((balance_factor > 1) && (RBSTGetBalanceFactor(node->children[LEFT]) 
	                                                                       < 0))
	{
		node->children[LEFT] = RBSTLeftRotate(node->children[LEFT], 
		                                 node->children[LEFT]->children[RIGHT]);
		node = RBSTRightRotate(node, node->children[LEFT]);
	}
	
	else if((balance_factor < -1) && (RBSTGetBalanceFactor(node->children[RIGHT]) 
	                                                                       > 0))
	{
		node->children[RIGHT] = RBSTRightRotate(node->children[RIGHT], 
		                                 node->children[RIGHT]->children[LEFT]);
		node = RBSTLeftRotate(node, node->children[RIGHT]);
	}
	
	else if((balance_factor < -1) && (RBSTGetBalanceFactor(node->children[RIGHT])
	                                                                      <= 0))
	{
		node = RBSTLeftRotate(node, node->children[RIGHT]);
	}
	
	return node;	
}

/* Find node's height */
static int RBSTHeightNode(const node_ty *node)
{
	if(!node)
	{
		return -1;
	}
	
	return node->height;
}

/* Finding the balance factor of a node */
static int RBSTGetBalanceFactor(const node_ty *node)
{
	assert(node);
	
	return (RBSTHeightNode(node->children[LEFT]) - 
	                                     RBSTHeightNode(node->children[RIGHT]));
}

/* Performing left rotation */
static node_ty *RBSTLeftRotate(node_ty *node, node_ty *pivot)
{	
	assert(node);
	assert(pivot);
	
	node->children[RIGHT] = pivot->children[LEFT];
	pivot->children[LEFT] = node;
	
	RBSTUpdateHeight(node);
	RBSTUpdateHeight(pivot);
	
	return pivot;
}

/* Performing right rotation */
static node_ty *RBSTRightRotate(node_ty *node, node_ty *pivot)
{
	assert(node);
	assert(pivot);
	
	node->children[LEFT] = pivot->children[RIGHT];
	pivot->children[RIGHT] = node;
	
	RBSTUpdateHeight(node);
	RBSTUpdateHeight(pivot);
	
	return pivot;
}






