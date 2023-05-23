/*******************************************************************************
* Description: Header of DHCP 
* Name: HRD20
* Date: 26/10/21
* Versions: 1.0 ready for review
*******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */

#define IPV 4

typedef struct dhcp dhcp_ty;

typedef enum DHCP 
{
	SUCCESS,
    DIFFERENT_ADDRESS,
    UNAUTHORIZED_ADDRESS,
    INVALID_ADDRESS,
    FAILURE,
    DOUBLE_FREE
}DHCP_status_ty;

/*******************************************************************************
* Function Description: creates a DHCP

* Arguments: subnet_address - the unchnaged part of the ip address
             subnet_mask - the number of unchangeable bits in the ip address 

* Return value: reference to the DHCP

* Notes: the following addresses are reserved:
 for 192.168.20.0/24 -> preserves: 192.168.20.0, 192.168.20.1, 192.168.20.255
 for 192.168.0.0/16  -> preserves: 192.168.0.0,  192.168.0.1, 192.168.255.255
 for 192.0.0.0/8     -> preserves: 192.0.0.0,    192.0.0.1,   192.255.255.255

* Time Complexity: O(1)
*******************************************************************************/
dhcp_ty *DHCPCreate(unsigned char subnet_address[IPV], size_t subnet_mask);

/*******************************************************************************
* Function Description: deallocates the memory that was used for the DHCP
  and all the elements inside it

* Arguments: dhcp: The DHCP that should be destroyed

* Notes: if dhcp is NULL, no operation is performed

* Time Complexity: O(n)
*******************************************************************************/
void DHCPDestroy(dhcp_ty *dhcp);

/*******************************************************************************
* Function Description: allocates the requested ip by the user

* Arguments: dhcp: The DHCP which handels the request
             requested_ip: the requested ip by the user  
             returned_address: the address that the DHCP returns    

* Return value: stauts whether the requested ip address allocation succeeded
                if the address is occupied another address will be given
                status if the requested ip address is out of range
                status if the requested address is a saved address by the DHCP

* Notes: if the user passes a NULL for an IP address, the function will return
         the first free address

* Time Complexity: log(n)
*******************************************************************************/
DHCP_status_ty DHCPAllocateIp(dhcp_ty *dhcp, const unsigned char 
                        requested_ip[IPV], unsigned char returned_address[IPV]);

/*******************************************************************************
* Function Description: frees the ip address given by the user from the DHCP

* Arguments: dhcp: the DHCP which contains the ip_to_free
             ip_to_free: the address that the user wants to free

* Return value: stauts whether the ip_to_free address was successfully freed
                status if the requested ip address is out of range
                status if the requested address is a saved address by the DHCP

* Notes:  undefined behavior if the dhcp is null


* Time Complexity: O(log(n))
*******************************************************************************/
DHCP_status_ty DHCPFreeIp(dhcp_ty *dhcp, const unsigned char ip_to_free[IPV]);

/*******************************************************************************
* Function Description: counts the number of free ip addresses

* Arguments: dhcp: The DHCP which contains the ip addresses

* Return value: the number of the available ip addresses

* Notes: undefined behavior if the dhcp is NULL

* Time Complexity: O(n)
*******************************************************************************/
size_t DHCPCountFree(const dhcp_ty *dhcp);

#endif /* __DHCP_H__ */
