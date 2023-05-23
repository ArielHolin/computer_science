/*********************************************************************
* Description: API for Hash Table Data Structure
* Name: HRD20
* Date: 17/10/2021
* Versions: 1.0 - 
*********************************************************************/
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stddef.h> /* size_t */

typedef struct hash_table ht_ty;

/* operation_ty return 0 for succes, else return int that indicates the type of failure
   for user convenience. */
typedef int (*ht_operation_ty)(void *data, void *param);

/* hash_func_ty return size_t type after manipulation on the key*/
typedef size_t (*hash_func_ty)(const void *key);

/* return the key of data item we get, so we know where to insert data */
typedef void *(*get_key_ty)(const void *data);

/* this hasht table match function */
typedef int (*ht_match_ty)(const void *data, void *param);
/*******************************************************************************
* Function Description: Creates a hash table with given size
			       
* Arguments: capacity: the capacity of the created hash table
             hash function: for hasing the key of item
             get_key_func: for getting key of item
             match_func: to match items in case of collision

* Return value: Pointer to the created hash table
   
* Notes: if HTCreate fails, return NULL. in case of unvalid functions 
        
* Time Complexity: O(1)
*******************************************************************************/
ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, 
                            get_key_ty get_key_func, ht_match_ty match_func);

/*******************************************************************************
* Function Description: destroy a hash table
			       
* Arguments: hast_table

* Return value: 
   
* Notes: If hash_table is null, no operation is done
        
* Time Complexity: O(1)
*******************************************************************************/
void HTDestroy(ht_ty *hash_table);

/*******************************************************************************
* Function Description: insert new item to the hast table

* Arguments: hast_table: tha table to insert the item to
             data: the key to where to insert the item in the table

* Return value: return status of the function. 0 for seccuess not 0 otherwise
   
* Notes: if one of the arguments is not valid, undefined behavior
        
* Time Complexity: O(1), O(n) worst case
*******************************************************************************/
int HTInsert(ht_ty *hash_table, void *data);

/*******************************************************************************
* Function Description: remove item from the hast table
			       
* Arguments: hast_table: tha table to remove the item from
             key: the key to where to remove the item in the table

* Return value: 
   
* Notes: if one of the arguments is not valid, undefined behavior
        
* Time Complexity: O(1), O(n) worst case
*******************************************************************************/
void HTRemove(ht_ty *hash_table, void *key);

/*******************************************************************************
* Function Description: find item in the hast table
			       
* Arguments: hast_table: tha table to find the item from
             key: the key to how to find the item

* Return value: return the value of the the item we searched for
   
* Notes: if we didnt find we return null
         if one of the arguments is not valid, undefined behavior
        
* Time Complexity: O(1), O(n) worst case
*******************************************************************************/
void *HTFind(const ht_ty *hash_table, void *key);

/*******************************************************************************

* Function Description: Perfroms op on each item in the hash table.
			       
* Arguments: hash_table - hash table to perform operation on .
             op - operation function.
             param - param of the operation function, for user convenience.

* Return value: 0 for SUCCESS, otherwise returns int that was returned from op function 
   
* Notes: - If op fails before the entire hash table, function stops.

* Time Complexity: O(n) n - number of elements.	
*******************************************************************************/
int HTForEach(ht_ty *hash_table, ht_operation_ty op, void *param);

/*******************************************************************************
* Function Description: Determines if hash table is empty.
			       
* Arguments: Pointer to hash_table.

* Return value: If empty return 1, else return 0 
   
* Notes: If hash_table is not valid, undefined behavior
        
* Time Complexity: O(1)
*******************************************************************************/
int HTIsEmpty(const ht_ty *hash_table);

/*******************************************************************************
* Function Description: Returns the size of the hash table
			       
* Arguments: Pointer to hash_table.

* Return value: The number of items in the hash table.  
   
* Notes: If hash table is not valid, undefined behavior
        
* Time Complexity: O(n) n - number of elements.
*******************************************************************************/
size_t HTSize(const ht_ty *hash_table);

/*******************************************************************************
* Function Description: Returns the load factor of the hash table
			       
* Arguments: Pointer to hash_table.

* Return value: The load factor of the hash table.  
   
* Notes: If hash table is not valid, undefined behavior
        
* Time Complexity: O(n) n - number of elements.
*******************************************************************************/
double HTGetLoadFactor(const ht_ty *hash_table);

/*******************************************************************************
* Function Description: Returns the standard deviation of the hash table
			       
* Arguments: Pointer to hash_table.

* Return value: The standard deviation of the hash table.  
   
* Notes: If hash table is not valid, undefined behavior
        
* Time Complexity: O(n) n - number of elements.
*******************************************************************************/
double HTGetSD(const ht_ty *hash_table);

#endif /* __HASHTABLE_H__*/
