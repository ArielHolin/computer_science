/*******************************************************************************
*  ws8.c                                                                       *
*  Author: Ariel                                                               *
*  Reviewer: Doron                                                             *
*******************************************************************************/
#include <string.h>  /* strcpy, strlen         */
#include <stdio.h>   /* printf, sprintf, puts  */
#include <stdlib.h>  /* free                   */
#include <assert.h>  /* assert                 */

#define ARRAY_SIZE  5
#define MAX_INT_LEN 10

#define MAX2(a, b) ( a > b ? a : b )
#define MAX3(a, b, c) ( a > MAX2(b, c) ? a : MAX2(b, c) )
#define SIZEOF_VAR(var) ( (size_t) (&(var) + 1) - (size_t) &var )
#define SIZEOF_TYPE(type) ( (size_t) ((type *)0 + 1) )

/* Exercise 1 */

struct element;

typedef void (*add_func_ty)(struct element *, int);
typedef void (*print_func_ty)(struct element *);
typedef void (*clean_func_ty)(struct element *);

typedef struct element
{
	void *data;
	add_func_ty add_to_data;
	print_func_ty print_func;
	clean_func_ty clean_func;
} element_ty;

enum array_locations
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

void InitElementArr(element_ty element_arr[]);
void PrintArrayElements(element_ty arr[], size_t arr_size);
void AddToElements(element_ty arr[], size_t arr_size, int number);
void PrintAndFree(element_ty arr[], size_t arr_size);

static void PrintFloat(element_ty *elem);
static void PrintInt(element_ty *elem);
static void PrintString(element_ty *elem);
static void AddToFloat(element_ty *elem, int number);
static void AddToInt(element_ty *elem, int number);
static void AddToString(element_ty *elem, int number);
static void CleanString(element_ty *elem);
static void CleanDummy(element_ty *elem);

static char *StrDup(const char *str);

/* Exercise 2 */

static void TestMax2(void);
static void TestMax3(void);

/* Exercise 3 & 4 */

static void TestMacro(void);

int main(void)
{
	/* Exercise 1 */
	element_ty elements_arr[ARRAY_SIZE];
	int number_to_add = 10;
	
	InitElementArr(elements_arr);
	
	puts("element_ty data before adding: ");
	PrintArrayElements(elements_arr, ARRAY_SIZE);
	
	AddToElements(elements_arr, ARRAY_SIZE, number_to_add);
	
	puts("element_ty data after adding: ");
	PrintAndFree(elements_arr, ARRAY_SIZE);
	
	printf("----------\n");
	
	/* Exercise 2 */
	TestMax2();
	TestMax3();
	
	/* Exercise 3 & 4 */
	TestMacro();
	
	return 0;
}

/*************** Function to be called inside main ****************************/

/*********************** Exercise 1 *******************************************/

/* Initializing array of element_ty */
void InitElementArr(element_ty element_arr[])
{
	*((float *)&element_arr[FIRST].data) = 4.2;
	element_arr[FIRST].add_to_data = AddToFloat;
	element_arr[FIRST].print_func = PrintFloat;
	element_arr[FIRST].clean_func = CleanDummy;
	
	*((float *)&element_arr[SECOND].data) = 6.7;
	element_arr[SECOND].add_to_data = AddToFloat;
	element_arr[SECOND].print_func = PrintFloat;
	element_arr[SECOND].clean_func = CleanDummy;
	
	element_arr[THIRD].data = StrDup("chapter");
	element_arr[THIRD].add_to_data = AddToString;
	element_arr[THIRD].print_func = PrintString;
	element_arr[THIRD].clean_func = CleanString;
	
	*((int *)&element_arr[FOURTH].data) = 12;
	element_arr[FOURTH].add_to_data = AddToInt;
	element_arr[FOURTH].print_func = PrintInt;
	element_arr[FOURTH].clean_func = CleanDummy;
	
	*((float *)&element_arr[FIFTH].data) = 56.32;
	element_arr[FIFTH].add_to_data = AddToFloat;
	element_arr[FIFTH].print_func = PrintFloat;
	element_arr[FIFTH].clean_func = CleanDummy;
}

/* Printing data in element_ty array. Used before adding. */
void PrintArrayElements(element_ty arr[], size_t arr_size)
{
	size_t i = 0;
	
	for ( i = 0; i < arr_size; ++i)
	{
		arr[i].print_func(&arr[i]);	
	}
}

/* Adding number to element_ty data. */
void AddToElements(element_ty arr[], size_t arr_size, int number)
{
	size_t i = 0;
	
	for ( i = 0; i < arr_size; ++i)
	{
		arr[i].add_to_data(&arr[i], number);
	}
	
}

/* Printing element_ty data and free. Used after adding. */
void PrintAndFree(element_ty arr[], size_t arr_size)
{
	size_t i = 0;
	
	for ( i = 0; i < arr_size; ++i)
	{
		arr[i].print_func(&arr[i]);	
		
		arr[i].clean_func(&arr[i]);
	}
}

/******* Implementation of print/add/clean functions of element_ty ************/

/************************* Print Functions ************************************/

static void PrintFloat(element_ty *elem)
{
	assert ( NULL != elem );
	
	printf("%.2f\n", *((float *)&elem->data));
}

static void PrintInt(element_ty *elem)
{
	assert ( NULL != elem );
	
	printf("%d\n", elem->data);
}

static void PrintString(element_ty *elem)
{
	assert ( NULL != elem );
	
	printf("%s\n", elem->data);
}

/************************* Add Functions **************************************/

static void AddToFloat(element_ty *elem, int number)
{
	assert ( NULL != elem );
	
	*((float *)&elem->data) += number;
}

static void AddToInt(element_ty *elem, int number)
{
	assert ( NULL != elem );
	
	*((int *)&elem->data) += number;
}


static void AddToString(element_ty *elem, int number)
{
	char int_buffer[MAX_INT_LEN];
	
	assert ( NULL != elem );

	sprintf(int_buffer, "%d", number);
	strcat(elem->data, int_buffer);
}

/********************** Clean Functions ***************************************/

static void CleanString(element_ty *elem)
{
	assert ( NULL != elem );
	
	free(elem->data);
}

static void CleanDummy(element_ty *elem)
{}

/************************** Helper Functions **********************************/

/* Returns a pointer to a new string which is a duplicate of s */
static char *StrDup(const char *str)
{
	char *res = (char *)malloc(strlen(str) + MAX_INT_LEN);
	
	assert ( NULL != str );

	res = strcpy(res, str);
	return res;
}

/*********************** Exercise 2 *******************************************/

static void TestMax2(void)
{
	assert (4 == MAX2(4, 1));
	assert (-1 == MAX2(-1, -2));
	assert (17.45 == MAX2(10.12, 17.45));
	
	printf("TestMax2 Success!\n-----------\n");
}

static void TestMax3(void)
{
	assert (0 == MAX3(-1, 0, -2));
	assert (50.54 == MAX3(40.6, -14.2, 50.54));
	
	printf("TestMax3 Success!\n----------\n");
}

/******************** Exercise 3 & 4 ******************************************/

static void TestMacro(void)
{
	assert (4 == SIZEOF_TYPE(int));
	assert (8 == SIZEOF_TYPE(char *));
	assert (4 == SIZEOF_TYPE(float));
	assert (32 == SIZEOF_TYPE(element_ty));
	
	printf("TestMacro Success!\n----------\n");
}
