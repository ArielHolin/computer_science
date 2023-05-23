/*******************************************************************************
*  recursion.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Bnaya                                                             *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* malloc, free */

#include "stack.h"

typedef struct node
{
	void *data;
	struct node *next;
}node_ty;

static int FIBO_BASE_CASE = 1;

int FibonacciRecursive(int element_index);
int FibonacciIterative(int element_index);
node_ty *FlipList(node_ty *node);
void SortStackRecursive(stack_ty *stack);
void InsertTopRecursive(stack_ty *stack, int top);
size_t StrLen(const char *str);
size_t StrLenRecursive(char *str, size_t res);
int StrCmp(const char *str1, const char *str2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrCatRecursive(char *dest, const char *src, size_t dest_len);
char *StrStr(const char *haystack, const char *needle);
char *StrStrRecursive(char *haystack, const char *needle, size_t needle_len);
int StrnCmp(const char *str1, const char *str2, size_t n);

int main(void)
{		
	size_t i = 0;
	int arr[7] = {4, 1, 6, 2, 7, 3, 5};
	
	stack_ty *new_stack = StackCreate(7);
	
	for(i = 0; i < 7; ++i)
	{
		StackPush(new_stack, &arr[i]);
	}
	
	SortStackRecursive(new_stack);
	
	for(i = 0; i < 7; ++i)
	{
		printf("%d\n", *(int *)StackPeek(new_stack));
		StackPop(new_stack);
	}
	
	StackDestroy(new_stack);
	
	return 0;
}

/****************** Exercise 1 ************************************************/

int FibonacciRecursive(int element_index)
{
	if(element_index <= 0)
	{
		return FIBO_BASE_CASE;
	}
	
	return FibonacciRecursive(element_index - 1) + 
	                                      FibonacciRecursive(element_index - 2);
}


int FibonacciIterative(int element_index)
{
	int first_element = FIBO_BASE_CASE;
	int second_element = FIBO_BASE_CASE;
	int res = 0;
	int i = 0;
	
	for(i = 0; i < element_index - 1; ++i)
	{
		res = first_element + second_element;
		
		first_element = second_element;
		second_element = res;
	}
	
	return res;
}

/****************** Exercise 2 ************************************************/

node_ty *FlipList(node_ty *node)
{
	node_ty *new_head = NULL;
	
	if(!node)
	{
		return NULL;
	}
	
	if(!node->next)
	{
		return node;
	}
	
	new_head = FlipList(node->next);
	
	node->next->next = node;
	node->next = NULL;
	
	return new_head;
}

/****************** Exercise 3 ************************************************/

void SortStackRecursive(stack_ty *stack)
{
	int top = 0;
	
	if(StackIsEmpty(stack))
	{
		return;
	}
	
	top = *(int *)StackPeek(stack);
	StackPop(stack);
	
	SortStackRecursive(stack);
	
	InsertTopRecursive(stack, top);	
}

void InsertTopRecursive(stack_ty *stack, int top)
{
	int curr_top = 0;
	
	if((StackIsEmpty(stack)) || (top > *(int *)StackPeek(stack)))
	{
		StackPush(stack, &top);
		return;
	}
	
	curr_top = *(int *)StackPeek(stack);
	
	StackPop(stack);
	
	InsertTopRecursive(stack, top);
	
	StackPush(stack, &curr_top);
}

/****************** Exercise 4 ************************************************/

/* StrLen */
size_t StrLen(const char *str)
{
	size_t res = 0;
	
	return StrLenRecursive((char *)str, res);
}

size_t StrLenRecursive(char *str, size_t res)
{	
	if(*str == '\0')
	{
		return res;
	}
	
	++str;
	++res;
	
	return StrLenRecursive(str, res);
}

/* StrCmp */
int StrCmp(const char *str1, const char *str2)
{	
	if((*str1 == '\0') || (*str2 == '\0') || (*str1 != *str2))
	{
		return *str1 - *str2;
	}
	
	++str1;
	++str2;
	
	return StrCmp(str1, str2);
}

/* StrCpy */
char *StrCpy(char *dest, const char *src)
{
	if(*src == '\0')
	{
		*dest = *src;
		return dest;
	}
	
	*dest = *src;
	++src;
	++dest;
	
	return StrCpy(dest, src);
}

/* StrCat */
char *StrCat(char *dest, const char *src)
{
	size_t dest_len = StrLen(dest);
	
	return StrCatRecursive(dest, src, dest_len);
}

char *StrCatRecursive(char *dest, const char *src, size_t dest_len)
{	
	if(*src == '\0')
	{
		dest[dest_len] = *src;
		return dest;
	}
	
	dest[dest_len] = *src;
	++dest;
	++src;
	
	return StrCatRecursive(dest, src, dest_len);
}

/* StrStr */
char *StrStr(const char *haystack, const char *needle)
{
	size_t needle_len = StrLen(needle);
	
	return StrStrRecursive((char *)haystack, needle, needle_len);
}

char *StrStrRecursive(char *haystack, const char *needle, size_t needle_len)
{	
	if(!haystack)
	{
		return NULL;
	}
	
	if(0 == StrnCmp(haystack, needle, needle_len))
	{
		return haystack;
	}
	
	++haystack;
	
	return StrStrRecursive(haystack, needle, needle_len);
}

int StrnCmp(const char *str1, const char *str2, size_t n)
{	
	if(0 == n)
	{
		return 0;
	}
	
	if((*str1 == '\0') || (*str2 == '\0') || (*str1 != *str2))
	{
		return *str1 - *str2;
	}
	
	++str1;
	++str2;
	--n;
	
	return StrnCmp(str1, str2, n);
}


