/*******************************************************************************
*  ws10.h                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Bnaya                                                             *
*******************************************************************************/

#ifndef __WS10_H__
#define __WS10_H__

/* Converts number into char * and store the value in str */
char *ItoaBase10 (int number, char *str);

/* Receives char * representation of number and a base, and return integer
   decimal representation of the number according to base. If a certain char
   doesn't belong to base representation, return 0.
   Base is up to 36. */
int AtoiGenBase(const char *str, size_t base);

/* Receives 3 array of chars and prints the chars that are both in arr1 and arr2
   but not in arr3. */ 
void PrintIntersection(char *arr1, char *arr2, char *arr3);

/* Checks Endiann architecture. If big endiann, return 1. If little endiann, 
   return 0. If middle endiann, return -1 */
size_t EndiannCheck(void);

#endif  /* __WS10_H__ */
