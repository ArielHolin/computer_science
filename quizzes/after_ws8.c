/*******************************************************************************
*  After ws8 Quiz                                                              *
*  Author: Ariel                                                               * 
*******************************************************************************/
#include <stddef.h> /* size_t */

/* Question 1 */
#define MAX2(a, b) ( a > b ? a : b)
#define MAX3(a, b, c) (MAX2(a, MAX2(b, c)))

/*Question 2 */
#define TO_LOWER(a) ( a >= 'A' && a <= 'Z' ? (a - 'A') + 'a' : a) 

/* Question 3 */
#define OFFSET(s, f) ((size_t)&(((s *)0)->f) - (s *)0)

int main(void)
{
	return 0;
}

/* Question 4.1 
   
   struct s
   {
       int num;  4 bytes
       char ch1; 1 byte
       padding 3 bytes
       int *ptr; 4 bytes
       char ch2; 1 byte
       padding 3 bytes
   }
   
   overall: sizeof struct is 16 bytes on 32-bit machine
            on 64-bit machine overall size will be 24 bytes  


   Question 4.2
   
   when declaring a variable of type s, its address will be divisible by 16
   since it has to be aligned to the structure type (which is 16 on 32-bit 
   machine).


   Question 5

   s1 is the name of the new typedef struct.
   

   Question 6
   
   s1 is a variable of the new struct
   
   Question 7
   
   The sizeof u1 is 8 bytes, because it has to be aligned to int and must 
   include array of 5 chars (1 byte each)
   
   Question 8
   
   Answer: readability, performance (the most used field comes first)
   
*/

