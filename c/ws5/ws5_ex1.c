/*******************************************************************************
*  ws5_ex1.c
*  Author: Ariel
*  Reviewr: Doron
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

/******************Exercise 1 structs and functions****************************/
typedef void (*print_funct_ty)(int);

typedef struct
{
	int number;
	print_funct_ty Print;
}print_me_ty;

static void PrintNum(int number);

int main(void)
{
	size_t i = 0;
	size_t j = 0;
	
	print_me_ty example[10];
	
	for ( i = 0; i < 10; ++i)
	{
		example[i].number = i;
		example[i].Print = PrintNum;
	}
	
	for ( j = 0; j < 10; ++j)
	{
		example[j].Print(example[j].number);
	}
	
	return 0;
}

static void PrintNum(int number)
{
	printf("%d\n", number);
}
