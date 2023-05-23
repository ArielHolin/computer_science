/*********************************************************************
* Description: Implementation of a vector data structure.
* Name: HRD20
* Date: 08/08/21
* Versions: 
* 1.0 - ready for review
* 1.1 - after Naama's notes
* 1.2 - final header
*********************************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef int status_ty;
typedef struct vector vector_ty; 

/*******************************************************************************
* Function Description: create a vector with a capacity that was stated by 
                        the user 

* Arguments: capacity of the vector 

* Return value: pointer to the vector

* Notes: if memory allocation for the vector fails, returns NULL. 

* Time Complexity: O(1)
*******************************************************************************/

vector_ty *VectorCreate(size_t capacity);

/*******************************************************************************
* Function Description: frees the memory that was used for the vector

* Arguments: pointer to the vector

* Return value: - 

* Notes: undefined behaviour if vector is NULL 

* Time Complexity: O(1)
*******************************************************************************/

void VectorDestroy(vector_ty *vector);

/*******************************************************************************
* Function Description: returns the number of elements in the vector

* Arguments: pointer to the vector

* Return value: number of elements

* Notes:  undefined behaviour if vector is NULL 

* Time Complexity: O(1)
*******************************************************************************/

size_t VectorSize(const vector_ty *vector);

/*******************************************************************************
* Function Description: returns the current capacity of the vector

* Arguments: pointer to the vector

* Return value: vector's capacity

* Notes:  undefined behaviour if vector is NULL 

* Time Complexity: O(1)
*******************************************************************************/

size_t VectorCapacity(const vector_ty *vector);

/*******************************************************************************
* Function Description: reduces memory usage by freeing unused memory, so that
capacity will be equal to size

* Arguments: pointer to the vector

* Return value: status of success/failure

* Notes: - 

* Time Complexity: worst - O(n) Amortized O(1)
*******************************************************************************/

status_ty VectorShrinkToFit(vector_ty *vector);

/*******************************************************************************
* Function Description: returns the element from an index that was stated by 
                        the user 

* Arguments: pointer to the vector and index of an element

* Return value: the value of the element in the specified index

* Notes: if index is greater than the number of element in the vector 
   the behaviour is undefined 

* Time Complexity: O(1)
*******************************************************************************/

void *VectorGetVal (const vector_ty *vector, size_t index);

/*******************************************************************************
* Function Description: changes the element at index that was stated by the user
to the value of the new element

* Arguments: pointer to the vector, index of an element and value 
of the new element

* Return value: the value of the element in the specified index

* Notes: if index is greater than the number of element in the vector 
   the behaviour is undefined  

* Time Complexity: O(1)
*******************************************************************************/

void *VectorSetVal (vector_ty *vector, size_t index, void *element );

/*******************************************************************************
* Function Description: adds an element to the end of the vector 

* Arguments: pointer to the vector

* Return value: status of success/failure

* Notes: if the size of the vector is equal to the capacity, the capacity will
grow by growth factor

* Amortized time Complexity: O(1) worst O(n)
*******************************************************************************/

status_ty VectorPushBack(vector_ty *vector, void *element);

/*******************************************************************************
* Function Description: removes the last element at the end of the vector

* Arguments: pointer to the vector

* Return value: status of success/failure

* Notes: if the size of the vector is much smaller than the capacity,  
         the capacity will shrink by shrink factor

* Amortized time Complexity: O(1)
*******************************************************************************/

status_ty VectorPopBack(vector_ty *vector);

/*******************************************************************************
* Function Description: user sets new_capacity to the vector's current capacity, 
so that the current capacity size will be at least the size of the new_capacity  

* Arguments: pointer to the vector and space to add

* Return value: status of success/failure

* Notes: - 

* Time Complexity: O(n)
*******************************************************************************/

status_ty VectorReserve(vector_ty *vector, size_t new_capacity);


#endif /* __VECTOR_H__ */
