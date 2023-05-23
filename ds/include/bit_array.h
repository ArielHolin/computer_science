#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

/*
Description: The bit array data structure is an array of 64 bits

Name: Ariel
Reviewer: Bnaya
Date: 3.8.2021

Versions:          
0.1 - 
*/

#include <stddef.h> /* size_t */

typedef size_t bit_arr_ty;

/*******************************************************************************
* Function Description: SetAll function is turn_on all the bits in the bit array
						 and return the new bit_array. 
			       
* Arguments: bit_array - array of bits.

* Return value: The function return the bit array after the change. 
   
* Notes: 
        
* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrSetAll(bit_arr_ty bit_array);

/*******************************************************************************
* Function Description: SetOn function turn-on the bit placed in the bit array in 
						the position determined.return the new bit_array.
						
* Arguments: bit_array - array of bits
			 position - the index of the bit in the bit array. 
			       
* Return value: The function return the bit array after the change. 
  
* Notes: the position need to be between 0 and 63, due to array size constraint.
		 (bit array is size of 64 bits), all other position input will result 
		 undefined behavior.
		       
* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrSetOn(bit_arr_ty bit_array, size_t position);

/*******************************************************************************
* Function Description: GetVal function return the bit value placed in the bit array at 
						the requested position.
						      
* Arguments: bit_array - array of bits
             position - the index of the bit in the bit array.   
			      
* Return value: The function return the value of the bit in the position 
				determined  - 0 or 1.
				
* Notes: the position need to be between 0 and 63, due to array size constraint.
		 (bit array is size of 64 bits), all other position input will result 
		 undefined behavior.
		 
* Time Complexity:	
*******************************************************************************/
size_t BitsArrGetVal(bit_arr_ty bit_array, size_t position);
/*******************************************************************************
* Function Description: Rotr function rotate the bit array number of times determined
						in the num_of_rot parameter determined.  
						     
* Arguments: bit_array - array of bits, 
             num_of_rot -  number of rotations to make.

* Return value: The function return the bit array after the change.   
   
* Notes: When num_of_rot is greater then 64 the rotations will repeat itself.
		 64 rotations is the same as 1 rotation.
		         
* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrRotR(bit_arr_ty bit_array, size_t num_of_rot);
/*******************************************************************************
* Function Description: CountOn function returns the number of set bits in the 
						bit array.        
						
* Arguments: bit_array - array of bits.
     
* Return value: The value returned is the number of set bits in the bit array. 

* Notes: 
	        
* Time Complexity:	
*******************************************************************************/
size_t BitsArrCountOn(bit_arr_ty bit_array);
/*******************************************************************************
* Function Description: ResetAll function turn_off all the bits in the bit array and 
						return the new bit_array. 
						   
* Arguments: bit_array - array of bits.       

* Return value: The function return the bit array after the change.  
    
* Notes: 	
        
* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrResetAll(bit_arr_ty bit_array);
/*******************************************************************************
* Function Description: SetOff function turn-off the bit placed in the bit array 
						in the position determined.return the new bit_array.
						        
* Arguments: bit_array - array of bits
			 position - the index of the bit in the bit array.
			        
* Return value: The function return the bit array after the change. 
     
* Notes: the position need to be between 0 and 63, due to array size constraint.
		 (bit array is size of 64 bits), all other position input will result 
		 undefined behavior.
	        
* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrSetOff(bit_arr_ty bit_array, size_t position);
/*******************************************************************************
* Function Description: Flip function flips the bit placed in the bit array at 
						the requested position.  
						     
* Arguments: bit_array - array of bits, 
             position - the index of the bit in the bit array.
       
* Return value: The function return the bit array after the change.  
    
* Notes: the position need to be between 0 and 63, due to array size constraint.
		 (bit array is size of 64 bits), all other position input will result 
		 undefined behavior.	        

* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrFlip(bit_arr_ty bit_array, size_t position);
/*******************************************************************************
* Function Description: RotL function rotate the bit array number of times determined
						in the position parameter determined.
						    
* Arguments: bit_array - array of bits, num_of_rot -  number of rotations to make.

* Return value: The function return the bit array after the change.   
   
* Notes: When num_of_rot is greater then 64 the rotations will repeat itself.
		 64 rotations is the same as 1 rotation. 
		 	        
* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrRotL(bit_arr_ty bit_array, size_t num_of_rot);
/*******************************************************************************
* Function Description: CountOff function returns the number of off bits in
						the bit array. 
						    
* Arguments: bit_array - array of bits.
       
* Return value: The function return the number of off bits in the bit array.

* Notes: 

* Time Complexity:	
*******************************************************************************/
size_t BitsArrCountOff(bit_arr_ty bit_array);
/*******************************************************************************
* Function Description: ToString function returns string representation of the bit 
						array.     
* Arguments: bit_array - array of bits. 
             dest - a pointer to a buffer that will contain the string.

* Return value: The return value is the pointer to the bit array string .
				
* Notes: the size of the buffer must be large enough to be contain all the bits
		 of the bit array. if the space is smaller, the behavior is undefined.
		 
* Time Complexity:	
*******************************************************************************/
char *BitsArrToString(bit_arr_ty bit_array, char *dest);
/*******************************************************************************
* Function Description: SetBit function changes the bit state 
						in the requested position according to given state.
						   
* Arguments: bit_array - array of bits, 
             position - the index of the bit in the bit array.
             bit_state - the state you want the bit to be.
			 
* Return value: The function return the bit array after the change. 
     
* Notes: The bit state is must be 1 or 0 , else the behavior is undefined.
		 also, the position need to be between 0 and 63, due to array size constraint.
		 (bit array is size of 64 bits), all other position input will result 
		 undefined behavior.

* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrSetBit(bit_arr_ty bit_array, size_t position, size_t bit_state);
/*******************************************************************************
* Function Description: Mirror function mirrors the bit array.
						the MSB become the LSB and vice versa. 
						return the bit arry after the change. 
						      
* Arguments: bit_array - array of bits.
      
* Return value: The function return the bit array after the change.       

* Notes: 	        

* Time Complexity:	
*******************************************************************************/
bit_arr_ty BitsArrMirror(bit_arr_ty bit_array);

#endif /* __BIT_ARRAY_H__ */
