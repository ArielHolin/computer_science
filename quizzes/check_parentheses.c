/*******************************************************************************
*  Quiz - Balance_parentheses.c
*  Author: Ariel
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* puts   */
#include <string.h> /* strlen */

#include "../ds/include/stack.h"

enum left_parentheses
{
	LEFT_CIRC = 1,
	LEFT_SQUARE = 2,
	LEFT_CURL = 3
};

enum right_parentheses
{
	RIGHT_CURL = -3,
	RIGHT_SQUARE = -2,
	RIGHT_CIRC = -1
};

#define default_par -4

int CheckBalancedPar(char *par_str);
int ParValue(char chr);

int main(void)
{
	char str1[] = "[()](){[()]()}";
	char str2[] = "[{}(])";
	char *str3 = "kusdg$345t4tkj(()){{}}(}";
	
	CheckBalancedPar(str1);
	CheckBalancedPar(str2);
	CheckBalancedPar(str3);
	return 0;
}


int CheckBalancedPar(char *par_str)
{
	size_t par_str_len = strlen(par_str);
	stack_ty *par_stack = StackCreate(par_str_len + 1);
	
	if ( ParValue(*par_str) < 0 )
	{
		puts("Not Balanced");
		StackDestroy(par_stack);
		return -1;
	}
	
	StackPush(par_stack, (char *)par_str);
	
	while (*(par_str + 1))
	{
		++par_str;
		
		if ( ParValue(*par_str) > 0 )
		{
			StackPush(par_stack, (char *)par_str);
			continue;
		}
		
		if ( !StackIsEmpty(par_stack) &&
		     0 == ParValue(*par_str) + ParValue(*((char *)StackPeek(par_stack))) )
		{
			StackPop(par_stack);
			continue;
		}
		
		puts("Not Balanced");
		StackDestroy(par_stack);
		return -1;
	}
	
	if ( !StackIsEmpty(par_stack) )
	{
		puts("Not Balanced");
		StackDestroy(par_stack);
		return -1;
	}
	
	puts("Balanced");
	StackDestroy(par_stack);
	return 0;
}

int ParValue(char chr)
{
	switch (chr)
	{
		case '(':
			return LEFT_CIRC;
		case ')':
			return RIGHT_CIRC;
		case '[':
			return LEFT_SQUARE;
		case ']':
			return RIGHT_SQUARE;
		case '{':
			return LEFT_CURL;
		case '}':
			return RIGHT_CURL;
		default:
			return default_par;
	}
}

