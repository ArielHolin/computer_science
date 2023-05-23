/*******************************************************************************
*  dhcp.c                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Doron                                                             *
*******************************************************************************/
#include <stddef.h> /* size_t       */ 
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <string.h> /* memcpy       */

#include "dhcp.h"

typedef struct trie_node trie_node_ty;

enum occupied_status
{
	UNOCCUPIED = 0,
	OCCUPIED = 1
};

enum position
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

struct trie_node
{
      trie_node_ty *children[NUM_OF_CHILDREN];
      int is_occupied;
};

struct dhcp
{    
    trie_node_ty *root;
    unsigned char network_address[IPV];
    size_t subnet_mask; 
}; 

/************* Helper Functions Declarations **********************************/

static trie_node_ty *CreateFixedBits(dhcp_ty *dhcp, unsigned char network[IPV], 
                                                            size_t subnet_mask);
static trie_node_ty *CreateReservedAdds(dhcp_ty *dhcp, size_t subnet_mask);
static trie_node_ty *FindFirstUnreservedNode(dhcp_ty *dhcp, size_t subnet_mask);
static void DestroyTrieNode(trie_node_ty *node);
static size_t DHCPCountOccupied(trie_node_ty *node, size_t level);
static void UpdateOccupiedParents(trie_node_ty *node);
static DHCP_status_ty FindFirstAvailableAddress(dhcp_ty *dhcp, 
                                           unsigned char returned_address[IPV]);
static size_t NumOfBits(size_t ipv);
static size_t PowOfTwo(size_t pow);

/************* DHCPCreate *****************************************************/

dhcp_ty *DHCPCreate(unsigned char network_address[IPV], size_t subnet_mask)
{	
	dhcp_ty *new_dhcp = (dhcp_ty *)malloc(sizeof(dhcp_ty));
	
	if(!new_dhcp) return NULL;
			
	new_dhcp->root = (trie_node_ty *)malloc(sizeof(trie_node_ty));
	
	if(!new_dhcp->root)
	{
		free(new_dhcp);
		new_dhcp = NULL;
		
		return NULL;
	}
	
	new_dhcp->root->children[LEFT] = NULL;
	new_dhcp->root->children[RIGHT] = NULL;
	
	new_dhcp->root = CreateFixedBits(new_dhcp, &network_address[0], subnet_mask);
	
	if(!new_dhcp->root)
	{
		free(new_dhcp);
		new_dhcp = NULL;
		
		return NULL;
	}
	
	new_dhcp->root = CreateReservedAdds(new_dhcp, subnet_mask);
	
	if(!new_dhcp->root)
	{
		free(new_dhcp);
		new_dhcp = NULL;
		
		return NULL;
	}
	
	memcpy(new_dhcp->network_address, network_address, IPV);
	
	new_dhcp->subnet_mask = subnet_mask;
	
	return new_dhcp;
}  

/************* DHCPDestroy ****************************************************/

void DHCPDestroy(dhcp_ty *dhcp)
{
	if(!dhcp) return;
	
	DestroyTrieNode(dhcp->root);
	
	free(dhcp);
	dhcp = NULL;
}

/* Helper Function - recursively destroy trie nodes */
static void DestroyTrieNode(trie_node_ty *node)
{
	if(!node) return;
	
	DestroyTrieNode(node->children[LEFT]);
	DestroyTrieNode(node->children[RIGHT]);
	
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	
	free(node);
	node = NULL;
}

/************* DHCPCountFree **************************************************/

size_t DHCPCountFree(const dhcp_ty *dhcp)
{
	trie_node_ty *node = NULL;
	size_t level = 0;
	size_t ipv = IPV;
	size_t occupied_adds = 0;
	
	assert(dhcp);
	
	node = FindFirstUnreservedNode((dhcp_ty *)dhcp, dhcp->subnet_mask);
	
	level = NumOfBits(ipv) - dhcp->subnet_mask;
	
	occupied_adds = DHCPCountOccupied(node, level);
	
	return PowOfTwo(level) - occupied_adds;
}

static size_t DHCPCountOccupied(trie_node_ty *node, size_t level)
{	
	if(!node) return 0;
	
	if(node->is_occupied)
	{
		return PowOfTwo(level);
	}
	
	--level;
	return (DHCPCountOccupied(node->children[LEFT], level) + 
	                           DHCPCountOccupied(node->children[RIGHT], level));
	
}

/************* DHCPAllocateIp *************************************************/

DHCP_status_ty DHCPAllocateIp(dhcp_ty *dhcp, const unsigned char 
                        requested_ip[IPV], unsigned char returned_address[IPV])
{
	unsigned char status = SUCCESS;
	unsigned char *req_ip = NULL;
	unsigned char *ret_add = NULL;
	size_t level = 0;
	size_t ipv = IPV;
	size_t subnet_mask = 0;
	size_t mask = 1UL;
	trie_node_ty *node = NULL;
	size_t counter = 0;
	size_t i = 0;
	
	assert(dhcp);
	
	ret_add = &returned_address[i];
	req_ip = (unsigned char *)&requested_ip[i];
	subnet_mask = dhcp->subnet_mask;
	node = dhcp->root;
	level = NumOfBits(ipv) - subnet_mask;
	
	if(!requested_ip)
	{
		return FindFirstAvailableAddress(dhcp, ret_add);
	}
	
	/* working on fixed bits range: validate req_ip by comparing to fixed bits */
	while(subnet_mask > 0)
	{	
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			req_ip = (unsigned char *)&requested_ip[i];
			ret_add = &returned_address[i];
			mask = 1UL;
		}
		
		if((mask & *req_ip) && (!node->children[RIGHT]))
		{
			if(subnet_mask == 1)
			{
				--subnet_mask;
				continue;
			}
			
			return INVALID_ADDRESS;
		}
		
		else if(mask & *req_ip)
		{
			*ret_add |= mask;
			mask <<= 1;
			--subnet_mask;
			node = node->children[RIGHT];
		}
		
		else if((!(mask & *req_ip)) && (!node->children[LEFT]))
		{
			if(subnet_mask == 1)
			{
				--subnet_mask;
				continue;
			}
			
			return INVALID_ADDRESS;
		}
		
		else
		{
			mask <<= 1;
			--subnet_mask;
			node = node->children[LEFT];
		}	
	}
	
	/* working on dynamic bits range: 
       assigning requested ip if unoccupied,  otherwise - assigning new ip.*/
	while(level > 0)
	{	
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			req_ip = (unsigned char *)&requested_ip[i];
			ret_add = &returned_address[i];
			mask = 1UL;
		}
		
		if((mask & *req_ip) && (!node->children[RIGHT]))
		{	
			node->children[RIGHT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
			
			if(!node->children[RIGHT])
			{
				DestroyTrieNode(dhcp->root);
				return FAILURE;
			}
			
			node = node->children[RIGHT];
			node->children[LEFT] = NULL;
			node->children[RIGHT] = NULL;
			node->is_occupied = UNOCCUPIED;
			
			if(level > 1)
			{
				*ret_add |= mask;
			}
			
			mask <<= 1;
			--level;
		}
		
		else if((mask & *req_ip) && (UNOCCUPIED == 
		                                    node->children[RIGHT]->is_occupied))
		{
			node = node->children[RIGHT];
			
			if(level > 1)
			{
				*ret_add |= mask;
			}
			
			mask <<= 1;
			--level;
		}
		
		else if((mask & *req_ip) && (OCCUPIED == 
		                                    node->children[RIGHT]->is_occupied))
		{	
			status = FindFirstAvailableAddress(dhcp, &returned_address[0]);
			
			if(SUCCESS == status)
			{
				status = DIFFERENT_ADDRESS;
				return status;
			}
		}
		
		else if((!(mask & *req_ip)) && (!node->children[LEFT]))
		{			
			node->children[LEFT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
			
			if(!node->children[LEFT])
			{
				DestroyTrieNode(dhcp->root);
				return FAILURE;
			}
			
			node = node->children[LEFT];
			node->children[LEFT] = NULL;
			node->children[RIGHT] = NULL;
			node->is_occupied = UNOCCUPIED;
			
			mask <<= 1;
			--level;
		}
		
		else if((!(mask & *req_ip)) && (UNOCCUPIED == 
		                                     node->children[LEFT]->is_occupied))
		{
			node = node->children[LEFT];
			mask <<= 1;
			--level;
		}
		
		else if((!(mask & *req_ip)) && (OCCUPIED == 
		                                     node->children[LEFT]->is_occupied))
		{	
			status = FindFirstAvailableAddress(dhcp, &returned_address[0]);
			
			if(SUCCESS == status)
			{
				status = DIFFERENT_ADDRESS;
				return status;
			}
		}
	}
	
	node->is_occupied = OCCUPIED;
	UpdateOccupiedParents(dhcp->root);
	
	return status;
}

static DHCP_status_ty FindFirstAvailableAddress(dhcp_ty *dhcp, 
                                            unsigned char returned_address[IPV])
{
	unsigned char *ret_add = NULL;
	size_t level = 0;
	size_t ipv = IPV;
	size_t subnet_mask = 0;
	size_t mask = 1UL;
	trie_node_ty *node = NULL;
	size_t i = 0;
	size_t counter = 0;
	
	assert(dhcp);
	
	ret_add = &returned_address[i];
	subnet_mask = dhcp->subnet_mask;
	node = dhcp->root;
	level = NumOfBits(ipv) - subnet_mask;
	
	/* Traversing through fixed bits range */
	while(subnet_mask > 0)
	{
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			ret_add = &returned_address[i];
			mask = 1UL;
		}
		
		if(!node->children[LEFT])
		{
			*ret_add |= mask;
			mask <<= 1;
			--subnet_mask;
			node = node->children[RIGHT];
		}
		
		else
		{
			mask <<= 1;
			--subnet_mask;
			node = node->children[LEFT];
		}	
	}
	
	while(level > 0)
	{
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			ret_add = &returned_address[i];
			mask = 1UL;
		}
		
		if(!node->children[LEFT])
		{
			node->children[LEFT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
			
			if(!node->children[LEFT])
			{
				DestroyTrieNode(dhcp->root);
				return FAILURE;
			}
			
			node = node->children[LEFT];
			node->children[LEFT] = NULL;
			node->children[RIGHT] = NULL;
			node->is_occupied = UNOCCUPIED;
			
			mask <<= 1;
			--level;
		}
		
		else if(UNOCCUPIED == node->children[LEFT]->is_occupied)
		{
			node = node->children[LEFT];
			
			mask <<= 1;
			--level;
		}
		
		else if(!node->children[RIGHT])
		{
			node->children[RIGHT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
			
			if(!node->children[RIGHT])
			{
				DestroyTrieNode(dhcp->root);
				return FAILURE;
			}
			
			node = node->children[RIGHT];
			node->children[LEFT] = NULL;
			node->children[RIGHT] = NULL;
			node->is_occupied = UNOCCUPIED;
			
			if(level > 1)
			{
				*ret_add |= mask;
			}
			
			mask <<= 1;
			--level;
		}
		
		else if(UNOCCUPIED == node->children[RIGHT]->is_occupied)
		{
			node = node->children[RIGHT];
			
			if(level > 1)
			{
				*ret_add |= mask;
			}
			
			mask <<= 1;
			--level;
		}
		
		/* Return failure in case there are no addresses to allocate */
		else return FAILURE;
	}
	
	node->is_occupied = OCCUPIED;
	UpdateOccupiedParents(dhcp->root);
	
	return SUCCESS;
}

static void UpdateOccupiedParents(trie_node_ty *node)
{
	if(NULL == node) return;
	if((NULL == node->children[LEFT]) && (NULL != node->children[RIGHT])) return;
	if((NULL != node->children[LEFT]) && (NULL == node->children[RIGHT])) return;
	
	UpdateOccupiedParents(node->children[LEFT]);
	UpdateOccupiedParents(node->children[RIGHT]);
	
	if((OCCUPIED == node->children[LEFT]->is_occupied) && 
	                           (OCCUPIED == node->children[RIGHT]->is_occupied))
	{
		node->is_occupied = OCCUPIED;
	}
}

/************* DHCPFreeIp *****************************************************/

DHCP_status_ty DHCPFreeIp(dhcp_ty *dhcp, const unsigned char ip_to_free[IPV])
{
	unsigned char *ip_to_free_runner = NULL;
	size_t level = 0;
	size_t ipv = IPV;
	size_t subnet_mask = 0;
	size_t mask = 1UL;
	trie_node_ty *node = NULL;
	size_t i = 0;
	size_t counter = 0;
	
	assert(dhcp);
	
	ip_to_free_runner = (unsigned char *)&ip_to_free[i];
	subnet_mask = dhcp->subnet_mask;
	node = dhcp->root;
	level = NumOfBits(ipv) - subnet_mask;
	
	while(subnet_mask > 0)
	{	
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			ip_to_free_runner = (unsigned char *)&ip_to_free[i];
			mask = 1UL;
		}
		
		if((mask & *ip_to_free_runner) && (!node->children[RIGHT]))
		{
			if(subnet_mask == 1)
			{
				--subnet_mask;
				continue;
			}
			
			return INVALID_ADDRESS;
		}
		
		else if(mask & *ip_to_free_runner)
		{
			mask <<= 1;
			--subnet_mask;
			node = node->children[RIGHT];
		}
		
		else if((!(mask & *ip_to_free_runner)) && (!node->children[LEFT]))
		{
			if(subnet_mask == 1)
			{
				--subnet_mask;
				continue;
			}
			
			return INVALID_ADDRESS;
		}
		
		else
		{
			mask <<= 1;
			--subnet_mask;
			node = node->children[LEFT];
		}	
	}
	
	while(level > 0)
	{	
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			ip_to_free_runner = (unsigned char *)&ip_to_free[i];
			mask = 1UL;
		}
		
		if((mask & *ip_to_free_runner) && (!node->children[RIGHT]))
		{
			return INVALID_ADDRESS;
		}
		
		else if(mask & *ip_to_free_runner)
		{
			node = node->children[RIGHT];
			node->is_occupied = UNOCCUPIED;
			mask <<= 1;
			--level;
		}
		
		else if((!(mask & *ip_to_free_runner)) && (!node->children[LEFT]))
		{
			return INVALID_ADDRESS;
		}
		
		else if(!(mask & *ip_to_free_runner))
		{
			node = node->children[LEFT];
			node->is_occupied = UNOCCUPIED;
			mask <<= 1;
			--level;
		}
	}
	
	node->is_occupied = UNOCCUPIED;
	return SUCCESS;
}

/************* Generic Helper Functions ***************************************/

/* Helper Function - Creating the fixed bits int the trie according to 
                     subnet_mask */
static trie_node_ty *CreateFixedBits(dhcp_ty *dhcp, unsigned char network[IPV], 
                                                             size_t subnet_mask)
{
	unsigned char mask = 1UL;
	unsigned char *net = NULL;
	trie_node_ty *node = NULL;
	size_t counter = 0;
	size_t i = 0;
	
	assert(dhcp);
	assert(network);
	
	net = &network[i];
	node = dhcp->root;
	
	while(subnet_mask > 0)
	{	
		++counter;
		
		if(0 == (counter % 8))
		{
			++i;
			net = &network[i];
			mask = 1UL;
		}
		
		if(mask & *net)
		{
			node->children[RIGHT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
			
			if(!node->children[RIGHT])
			{
				DestroyTrieNode(dhcp->root);
				return NULL;
			}
			
			node = node->children[RIGHT];
			
			node->children[RIGHT] = NULL;
			node->children[LEFT] = NULL;
			node->is_occupied = UNOCCUPIED;
			
			mask <<= 1;
			--subnet_mask;
		}
		
		else
		{
			node->children[LEFT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
			
			if(!node->children[LEFT])
			{
				DestroyTrieNode(dhcp->root);
				return NULL;
			}
			
			node = node->children[LEFT];
			
			node->children[RIGHT] = NULL;
			node->children[LEFT] = NULL;
			node->is_occupied = UNOCCUPIED;
			
			mask <<= 1;
			--subnet_mask;
		}
	}
	
	return dhcp->root;
}

/* Creating reserved adds in the trie */
static trie_node_ty *CreateReservedAdds(dhcp_ty *dhcp, size_t subnet_mask)
{
	size_t remainder_bits = 0;
	size_t ipv = IPV;
	trie_node_ty *left_dir_node = NULL;
	trie_node_ty *right_dir_node = NULL;
	
	assert(dhcp);
	
	left_dir_node = FindFirstUnreservedNode(dhcp, subnet_mask);
	right_dir_node = FindFirstUnreservedNode(dhcp, subnet_mask);
	
	remainder_bits = NumOfBits(ipv) - subnet_mask;
	
	while(remainder_bits > 1)
	{
		left_dir_node->children[LEFT] = 
		                           (trie_node_ty *)malloc(sizeof(trie_node_ty));
		
		if(!left_dir_node->children[LEFT])
		{
			DestroyTrieNode(dhcp->root);
			return NULL;
		}
		
		right_dir_node->children[RIGHT] = 
		                           (trie_node_ty *)malloc(sizeof(trie_node_ty));
		
		if(!right_dir_node->children[RIGHT])
		{
			DestroyTrieNode(dhcp->root);
			return NULL;
		}
		
		left_dir_node = left_dir_node->children[LEFT];
		
		left_dir_node->children[RIGHT] = NULL;
		left_dir_node->children[LEFT] = NULL;
		left_dir_node->is_occupied = UNOCCUPIED;
		
		right_dir_node = right_dir_node->children[RIGHT];
		
		right_dir_node->children[RIGHT] = NULL;
		right_dir_node->children[LEFT] = NULL;
		right_dir_node->is_occupied = UNOCCUPIED;
		
		--remainder_bits;
	}
	
	right_dir_node->children[RIGHT] = 
	                               (trie_node_ty *)malloc(sizeof(trie_node_ty));
	
	if(!right_dir_node->children[RIGHT])
	{
		DestroyTrieNode(dhcp->root);
		return NULL;
	}
	
	right_dir_node = right_dir_node->children[RIGHT];
	
	right_dir_node->children[RIGHT] = NULL;
	right_dir_node->children[LEFT] = NULL;
	right_dir_node->is_occupied = OCCUPIED;
	
	left_dir_node->children[LEFT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
	
	if(!left_dir_node->children[LEFT])
	{
		DestroyTrieNode(dhcp->root);
		return NULL;
	}
	
	left_dir_node->children[LEFT]->children[LEFT] = NULL;
	left_dir_node->children[LEFT]->children[RIGHT] = NULL;
	left_dir_node->children[LEFT]->is_occupied = OCCUPIED;
	
	left_dir_node->children[RIGHT] = (trie_node_ty *)malloc(sizeof(trie_node_ty));
	
	if(!left_dir_node->children[RIGHT])
	{
		DestroyTrieNode(dhcp->root);
		return NULL;
	}
	
	left_dir_node->children[RIGHT]->children[LEFT] = NULL;
	left_dir_node->children[RIGHT]->children[RIGHT] = NULL;
	left_dir_node->children[RIGHT]->is_occupied = OCCUPIED;
	
	left_dir_node->is_occupied = OCCUPIED;
	
	return dhcp->root;
}

/* Finding first node in the trie that wasn't reserved according to
   subnet_mask */
static trie_node_ty *FindFirstUnreservedNode(dhcp_ty *dhcp, size_t subnet_mask)
{
	trie_node_ty *node = NULL;
	
	assert(dhcp);
	
	node = dhcp->root;
	
	while(subnet_mask > 0)
	{
		if(!node->children[LEFT])
		{
			node = node->children[RIGHT];
		}
		
		else
		{
			node = node->children[LEFT];
		}
		
		--subnet_mask;
	}
	
	return node;
}

/* Number of bits according to ipv (32-bit for ipv=4, 128-bit for ipv=6) */
static size_t NumOfBits(size_t ipv)
{
	return ipv * 8;
}

/* Calculating Powers of 2 */
static size_t PowOfTwo(size_t pow)
{
	size_t i = 0;
	size_t res = 1;
	
	for(i = 0; i < pow; ++i)
	{
		res *= 2;
	}
	
	return res;
}






