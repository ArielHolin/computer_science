/*******************************************************************************
*  ws9.h                                                                       *
*  Author: Ariel                                                               *
*  Reviewer: Maayan                                                            *
*******************************************************************************/

#ifndef __WS9_H__
#define __WS9_H__

/* Fills the first n bytes of the memory area pointed to by s with
   the constant byte c. */
void *Memset(void *s, int c, size_t n);

/* Copies n bytes from memory area src to memory area dest.
   Memcpy doesn't consider overlapping. */
void *Memcpy(void *dest, const void *src, size_t n);

/* Copies n bytes from memory area src to memory area dest. 
   Memove consider overlap. */
void *Memmove(void *dest, const void *src, size_t n);

#endif  /* __WS9_H__ */
