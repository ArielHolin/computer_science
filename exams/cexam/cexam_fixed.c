/*******************************************************************************
*  C Exam                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: liel                                                              *
*******************************************************************************/
#include <stddef.h>  /* size_t */

#define TEN   10
#define EIGHT 8

enum sgn_values
{
	NEGATIVE = -1,
	POSITIVE	
};

int main(void)
{
	return 0;
}

/*************************** Question 1 ***************************************/

int FlipDigitsInNum(int number)
{
	size_t sgn_flag = POSITIVE;
	size_t num_of_digits = 0;
	int i = 0;
	int res = 0;
	size_t curr_digit = 0;
	
	
	if ( number < 0 )
	{
		number = -number;
		sgn_flag = NEGATIVE;
	}
	
	number = RemoveTrailingZeros(number);
	num_of_digits = CountIntDigits(number);
	
	for ( i = num_of_digits - 1; i >= 0; --i )
	{
		curr_digit = number % TEN;
		res += curr_digit * PowOf10(i);
		number /= TEN;
	}
	
	if ( NEGATIVE == sgn_flag )
	{
		res = -res;
	}
	
	return res;
}

/* Return number without trailing zeros from right of number */
size_t RemoveTrailingZeros(size_t number)
{
	while ( 0 == number % TEN )
	{
		number /= TEN;
	}
	
	return number;
}

/* Returns number of digits in number */
size_t CountIntDigits(size_t number)
{
	size_t counter = 0;
	
	while ( number > 0 )
	{
		++counter;
		number /= TEN;
	}
	
	return counter;
}

/* Returns 10^pow. pow should be unsigned */
size_t PowOf10(size_t pow)
{
	size_t res = 1;
	size_t i = 0;
	
	for ( i = 0; i < pow; ++i )
	{
		res *= TEN;
	}
	
	return res;
}

/********************* Question 2 *********************************************/

/* Hexadecimal is base 16, hence each single hexadecimal digits is represented
   by 4 bits (nibble), as follows:
   
   0 - 0000         a - 1010
   1 - 0001         b - 1011
   2 - 0010         c - 1100
   3 - 0011         d - 1101
   4 - 0100         e - 1110
   5 - 0101         f - 1111
   6 - 0110
   7 - 0111
   8 - 1000
   9 - 1001
   
   Now, let's convert the binary number according to this dictionary:
   
   1100 1110 1001 1001 1101 1000 1111 0111
    c    e    9    9    d    8    f    7
    
    Thus, the hexadecimal representation of the binary value is:
    0xce99d8f7
*/

/******************* Question 3 ***********************************************/

/* Uninitialized variable gets the random value located at the address it was
   assigned to.  We can't really know or control what value it might be, hence
   it is called "garbage value".
*/

/********************* Question 4 *********************************************/

/* Mirrors the order of bits in a byte */
unsigned char ByteMirror(unsigned char byte)
{	
	byte = (byte & 0x0f) << 4 | (byte & 0xf0) >> 4;
	
	byte = (byte & 0x33) << 2 | (byte & 0xcc) >> 2;
	
	byte = (byte & 0x55) << 1 | (byte & 0xaa) >> 1;
	       
	return byte;
}

/* I guess that the fastest way to get the mirror value of a byte is by using
   a lookup table. */
   
/******************** Question 5 **********************************************/

/* Flips n bit of val */
int FlipBit(int val, unsigned int n)
{
	unsigned int mask = 1UL;
	
	mask <<= n;
	
	return val ^ mask;
}

/******************** Question 6 **********************************************/

/* Counts set bits in binary representation of number */
size_t CountSetBits(unsigned int number)
{
	size_t counter = 0;
	
	while ( number > 0 )
	{
		++counter;
		number = number & (number - 1);
	}
	
	return counter;
}

/* This method is the most efficient method, since the loop is running exactly 
   the number of times as the number of set bits.
   Thus, it doesn't matter to us whether the input is of type 
   unsigned int (4 bytes), unsigned long (8 bytes), unsigned short (2 bytes),
   or unsigned char (1 byte).
*/   

/******************* Question 7 ***********************************************/

/* size_t is a default type of c language which is garanteed to hold a word.
   in 32-bit machines size of size_t is 4 bytes, and on 64-bit machines size of 
   size_t is 8 bytes.
   
   By default size_t is unsigned, hence it is equivalent to unsigned int 
   (in 32-bit machines) or unsigned long (in 64-bit machines).
*/

/****************** Question 8 ************************************************/

/* Rotating Left 1 byte (8 bits). */
char RotateLeft(unsigned char byte, unsigned int nbits)
{
	unsigned int num_of_moves = nbits % EIGHT;  /* in case nbits >= 8 */
	unsigned char new_right_bits = (byte >> (EIGHT - num_of_moves));
	byte <<= num_of_moves;
	
	return byte | new_right_bits;
}

/******************* Question 9 ***********************************************/

/* If the architecture of one machine is little endiann, and the other machine
   is Big endiann, then it might be the cause for the numbers to appear
   different.
*/

/****************** Question 10 ***********************************************/

void Swap(int *ptr1, int *ptr2)
{
	int tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}
   
/***************** Question 11 ************************************************/

/* Returns length of string */
size_t Strlen(const char *str)
{
	size_t len = 0;
	
	while ('\0' != *str)
	{
		++len;
		++str;
	}
	
	return len;
}   
   
/* Compares between str1 and str2.  if str1 == str2, return 0
                                    if str1 < str2, return < 0,
                                    if str1 > str2, return > 0 */
int Strcmp(const char *str1, const char *str2)
{
	while( ('\0' != *str1) && (*str1 == *str2) )
	{
		++str1;
		++str2;
	}
	
	return *str1 - *str2;
}   
  
/* Concatenates src with dest. Strcat overwrites terminating null byte of dest
   and writes terminating null byte at the end of concatination. */
char *Strcat(char *dest, const char *src)
{
	char *start_dest = dest;
	size_t dest_len = Strlen(dest);
	
	dest += dest_len;
	
	dest = Strcpy(dest, src);
	
	return start_dest;
}

/* Copies src to dest, including terminating null byte. */
char *Strcpy(char *dest, const char *src)
{
	size_t src_len = Strlen(src);
	
	return Strncpy(dest, src, src_len);	
}

/* Copies n bytes from src to dest, including terminating null byte. */
char *Strncpy(char *dest, const char *src, size_t n)
{
	char *start_dst = dest;
	
	while ( ('\0' != *src) && (n > 0) )
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	while ( n > 0 )
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	*dest = '\0';
	
	return start_dst;	
}

/******************* Question 12 **********************************************/

/* Returns n element of Fibonacci series.  n should be greater than 0. */
unsigned long GetNFibonacciElement(unsigned int n)
{
	if ( (1 == n) || (2 == n) )
	{
		return 1;
	}
	
	return GetNFibonacciElement(n - 1) + GetNFibonacciElement(n - 2);
}

/************** Question 13 ***************************************************/

/* Converting number to string and store the value in str. */
char *ItoaBase10(int number, char *str)
{
	char *start_str = str;
	size_t sgn_flag = POSITIVE;
	size_t curr_digit;
	
	if ( number < 0 )
	{
		number = -number;
		sgn_flag = NEGATIVE;
	}
	
	while( number > 0 )
	{
		curr_digit = number % TEN;
		*str = curr_digit + '0';
		++str;
		number /= TEN;
	}
	
	if ( NEGATIVE == sgn_flag )
	{
		*str = '-';
	}
	
	return ReverseStr(start_str);
}

/* Reversing string */
char *ReverseStr(char *str)
{
	size_t str_len = Strlen(str);
	char *start_str = str;
	char *end_str = str + str_len - 1;
	
	while ( start_str < end_str )
	{
		SwapChars(start_str, end_str);
		++start_str;
		--end_str;
	}
	
	return str;
}

void SwapChars(char *str1, char *str2)
{
	char tmp = *str1;
	*str1 = *str2;
	*str2 = tmp; 
}

/************* Question 14 ****************************************************/

/* Multiplying number by 8 using shift operator. */
int ShftMultiBy8(int number)
{
	size_t sgn_flag = POSITIVE;
	
	if ( number < 0 )
	{
		number = -number;
		sgn_flag = NEGATIVE;
	}
	
	number <<= 3UL;
	
	if ( NEGATIVE == sgn_flag )
	{
		number = -number;
	}
	
	return number;
}  
  
/*************** Question 15 **************************************************/

void Swap1(int *ptr1, int *ptr2)
{
	int tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

void Swap2(int *ptr1, int *ptr2)
{
	*ptr1 = *ptr1 ^ *ptr2;
	*ptr2 = *ptr1 ^ *ptr2;
	*ptr1 = *ptr1 ^ *ptr2;
}

void Swap3(int *ptr1, int *ptr2)
{
	*ptr1 = *ptr1 - *ptr2;
	*ptr2 = *ptr1 + *ptr2;
	*ptr1 = *ptr2 - *ptr1;
}

/* I guess that using bitwise operations is always the best way to do arithmetic
   manipulations. */
   
/****************** Question 16 ***********************************************/

/* foo() output:
   
   8 6 5 5
   segmentation fault
   
*/

/****************** Question 17 ***********************************************/

/* foo() output:

   3
   
*/

/**************** Question 18 *************************************************/

/* Static global variable is a variable that is visible only to function at the
   same c file of a program.
   
   Static local variable is a variable that is decalred and initialized within a
   scope of a certain function, and keeps its value betond the scope of the 
   function.
   
   The difference between static global and local is mainly the scope.
   
   Static function is a function that is visible and can be used only inside
   the file it is decalred in a program.
   
   Static library is a set of functions and variables that are grouped together
   for the main program.
   
*/

/************ Question 19 *****************************************************/

/* auto, register, volatile, static and extern are storage class specifiers,
   which suggest the compiler how to treat a variable.
   
   auto is being added to a local variable inside a function scope.
   (auto is default for local variables).
   
   register is the same as auto, except that register tells the compiler that
   the variable is going to be heavily used, hence it might save it in a 
   register. Register is almost never used, since compilers have better 
   optimizations.
   
   volatile tells the compiler not to optimize the current variable, since it 
   might be changed by outer resources (such as hardware or thread).
   
   static variables and functions explained in question 18.
   static variables refers to static storage, whereas static functions refers
   to static linkage.
   
   extern variable turns the variable to be visible to whole the files compiled
   within a program. Initialization of extern variable can't be added within
   declaration.
*/

/*************** Question 20 **************************************************/

/* I guess sizeof(int) should be the same for both 32-bit machines and 64-bit
   machines.
*/

/************** Question 21 ***************************************************/

/* 32-bit machine
   
   struct S
   {
      int *i;  4 bytes
      char c;  1 byte
      padding  1 byte
      short s; 2 bytes
      int *j;  4 bytes
   }
   
   overall: 12 bytes
   
   64-bit machine
   
   struct S
   {
     int *i;  8 bytes
     char c;  1 byte
     padding  1 byte
     short s; 2 bytes
     padding  4 bytes
     int *j;  8 bytes
   }
   
   overall: 24 bytes
*/

/************* Question 22 ****************************************************/

/* 32-bit machine

   struct S
   {
     unsigned int i : 2;    2 bits
     unsigned char c : 1;   1 bit
     unsigned short s : 3;  3 bits
     padding                2 bits ( 1 byte )
     padding                3 bytes
     int *j;                4 bytes ( 8 bytes )
     unsigned char x : 2;   2 bits
     padding                6 bits ( 9 bytes )
     padding                3 bytes
   }
    overall: 12 bytes
 
   64-bit machine
   
   struct S
   {
     unsigned int i : 2;    2 bits
     unsigned char c : 1;   1 bit
     unsigned short s : 3;  3 bits
     padding                2 bits ( 1 byte )
     padding                7 bytes
     int *j;                8 bytes ( 16 bytes )
     unsigned char x : 2;   2 bits
     padding                6 bits ( 17 bytes )
     padding                7 bytes
   }
   
   overall: 24 bytes
*/

/********************** Question 23 *******************************************/

/* jack is a type of the union, whose sizeof is 8 bytes.

   Prototype of a function that receives jack as parameter:
   
   void func_examp(union jack var_jack);
*/

 /*ll: i think the union is anonymous and jack is a var*/ 
 /*ah: I'm not sure I agree with this. Will wait for class clarification. */
   
