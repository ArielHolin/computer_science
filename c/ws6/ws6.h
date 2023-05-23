/************************************************
*  ws6.h
*  Author: Ariel 
*  Reviewer: Bnaya
*************************************************/

#ifndef __WS6_H__
#define __WS6_H__

#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

/* Receives two unsigned integers, and return x*(2^y) */
long Pow2(unsigned int x, unsigned int y);

/* Receives unsigned int, return 1 if n is power of 2, 0 otherwise.
   Implemantation using while loop. */
int IsPowOf2Loop(unsigned int number);

/* Same as function above, without using loop. */
int IsPowOf2NoLoop(unsigned int number);

/* Adding one to number */
int AddOneNoArithmetic(int number);

/* Receives array of unsigned ints and the array length, and prints only
   unsigned ints which has 3 set bits */
void Print3SetBitsUnsignedInts(unsigned int array[], size_t array_len);

/* Reversing bits of an unsigned integer */
unsigned int ByteMirrorLoop(unsigned int number);

/* Reversing string of an unsigned integer, using lookup table */
unsigned int ByteMirrorLUT(unsigned int number);

/* checks if bits 2 and 6 are on, return 1 if yes, 0 otherwise */
int TwoAndSix(unsigned char chr);

/* checks if bits 2 or 6 are on, return 1 if yes, 0 otherwise */
int TwoOrSix(unsigned char chr);

/* Switch bits number 3 and 5 */
int SwapBit3AndBit5(unsigned char chr);

/* Finds closest number (from bottom) that is divisible by 16 */
unsigned int FindClosestDivBy16(unsigned int number);

void Swap(int *number1, int *number2);

/* Receives a number and return the number of turned on bits. */
int CountSetBits(unsigned int number);

/* Same as CountSetBits, but implementation doesn't include using loop */
int CountSetBitsNoLoop(unsigned int number);

/* Receives float from user, and print its bits */
void PrintFloatBits(void);

#endif  /* __WS6_H__ */
