/*******************************************************************************
*  dhcp_test.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "dhcp.h"

typedef struct trie_node trie_node_ty;

struct dhcp
{    
    trie_node_ty *root;
    unsigned char network_address[IPV];
    size_t subnet_mask; 
}; 

void TestDHCPCreate(void);

int main(void)
{
	TestDHCPCreate();
	return 0;
}

/************* TestDHCPCreate *************************************************/

void TestDHCPCreate(void)
{
	unsigned char network_add[IPV] = {127, 56, 76, 86};
	dhcp_ty *dhcp = DHCPCreate(network_add, 24);
	size_t i = 0;
	size_t free_adds = 0;
	DHCP_status_ty status = SUCCESS;
	const unsigned char req_ip[IPV] = {127, 56, 76, 24};
	const unsigned char req_ip2[IPV] = {127, 56, 76, 64};
	const unsigned char ip_to_free[IPV] = {127, 56, 76, 78};
	unsigned char ret_add[IPV] = {0, 0, 0, 0};
	unsigned char ret_add2[IPV] = {0, 0, 0, 0};
	unsigned char ret_add3[IPV] = {0, 0, 0, 0};
	
	for(i = 0; i < IPV; ++i)
	{
		printf("%ld char of network: %d\n", i + 1, dhcp->network_address[i]);
	}
	
	printf("subnet_mask: %ld\n", dhcp->subnet_mask);
	free_adds = DHCPCountFree(dhcp);
	printf("Free addresses before memory allocation: %ld\n", free_adds);
	
	printf("----------\n");
	
	status = DHCPAllocateIp(dhcp, req_ip, &ret_add[0]);
	printf("Status after allocating valid ip: %d\n", status);
	for(i = 0; i < IPV; ++i)
	{
		printf("%ld char of valid ip: %d\n", i + 1, ret_add[i]);
	}
	free_adds = DHCPCountFree(dhcp);
	printf("Free addresses after 1 allocation: %ld\n", free_adds);
	
	printf("----------\n");
	
	status = DHCPAllocateIp(dhcp, req_ip2, &ret_add2[0]);
	printf("Status after allocation of another valid ip: %d\n", status);
	for(i = 0; i < IPV; ++i)
	{
		printf("%ld char of second valid ip: %d\n", i + 1, ret_add2[i]);
	}
	free_adds = DHCPCountFree(dhcp);
	printf("Free addresses after 2 allocations: %ld\n", free_adds);
	
	printf("----------\n");
	
	status = DHCPAllocateIp(dhcp, req_ip, &ret_add3[0]);
	printf("Status after allocation of used ip: %d\n", status);
	for(i = 0; i < IPV; ++i)
	{
		printf("%ld char of second valid ip: %d\n", i + 1, ret_add3[i]);
	}
	free_adds = DHCPCountFree(dhcp);
	printf("Free addresses after 3 allocations: %ld\n", free_adds);
	
	printf("----------\n");
	
	status = DHCPFreeIp(dhcp, req_ip);
	printf("Status of free valid ip: %d\n", status);
	free_adds = DHCPCountFree(dhcp);
	printf("Free addresses after 1 free: %ld\n", free_adds);

	printf("----------\n");
	
	status = DHCPFreeIp(dhcp, ip_to_free);
	printf("Status of free unvalid ip: %d\n", status);
	free_adds = DHCPCountFree(dhcp);
	printf("Free addresses after unsuccessful free: %ld\n", free_adds);

	printf("----------\n");
	
	DHCPDestroy(dhcp);
}
