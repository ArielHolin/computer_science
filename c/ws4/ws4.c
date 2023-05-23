/*******************************************************************************
*  ws4.c
*  Author: Ariel
*  Reviewer: Eva
*******************************************************************************/
#include <stdio.h>  /* printf, getchar */
#include <stddef.h> /* size_t          */
#include <string.h> /* strcmp          */
#include <stdlib.h> /* system          */

#define LUT_SIZE 256
#define A_ASCII 65
#define T_ASCII 84
#define ESC_ASCII 27

int PrintCharWithIf(void);
static int PrintCharWithIfImp(char letter);
int PrintCharWithSwitch(void);
static int PrintCharWithSwitchImp(char letter);
int PrintCharWithLut(void);
static int PrintCharWithLutImp(char letter);
static void InitLut( void (*func[])(void));
static void PrintA(void);
static void PrintT(void);
static void PrintEsc(void);
static void Empty(void);

static void (*lut[LUT_SIZE])(void);

/*******************************main*******************************************/

int main(int argc, char **argv)
{	
	if (2 != argc)
	{
		printf("Usage: ./ws4 If/Switch/Lut\n");
		return 1;
	}
	
	if (0 == strcmp(argv[1], "If"))
	{
		PrintCharWithIf();
		return 0;
	}
	
	if (0 == strcmp(argv[1], "Switch"))
	{
		PrintCharWithSwitch();
		return 0;
	}				
			
	if (0 == strcmp(argv[1], "Lut"))
	{
		PrintCharWithLut();
		return 0;
	}
	
	printf("Usage: ./ws4 If/Switch/Lut\n");
	
	return 0;
}

/*************************If/Else**********************************************/

/* Receives letter from user and call PrintCharWithIfImp() as long as 
   letter != Esc */ 
int PrintCharWithIf(void)
{	
	int letter = 0;
	
	system("stty -icanon -echo");
	
	do
	{
		printf("Insert letter: \n");
		letter = getchar();
		PrintCharWithIfImp(letter);
	}
	while( letter != ESC_ASCII );
	
	system("stty icanon echo");
	
	return 0;
}

static int PrintCharWithIfImp(char letter)
{
	if ( A_ASCII == letter )
	{
		PrintA();
		return 0;
	}
		
	if ( T_ASCII == letter )
	{
		PrintT();
		return 0;
	}
	
	if ( ESC_ASCII == letter )
	{
		PrintEsc();
		return 0;
	}
	
	return 0;
}

/****************************Switch********************************************/

/* Receives letter from user and call PrintCharWithSwitchImp() as long as 
   letter != Esc */
int PrintCharWithSwitch(void)
{	
	int letter = 0;
	
	system("stty -icanon -echo");
	
	do
	{
		printf("Insert letter: \n");
		letter = getchar();
		PrintCharWithSwitchImp(letter);
	}
	while( letter != ESC_ASCII);
	
	system("stty icanon echo");
	
	return 0;
}

static int PrintCharWithSwitchImp(char letter)
{
	switch (letter)
	{
		case A_ASCII:
			PrintA();
			break;
		case T_ASCII:
			PrintT();
			break;
		case ESC_ASCII:
			PrintEsc();
			break;
		default:
			break;
	}
	
	return 0;
}

/*******************************LUT********************************************/

/* Receives letter from user and call PrintCharWithLutImp() as long as 
   letter != Esc */ 
int PrintCharWithLut(void)
{	
	int letter = 0;
	
	static int is_first_entrance = 0;
	
	system("stty -icanon -echo");
	
	if ( 0 == is_first_entrance )
	{
		InitLut(lut);
		is_first_entrance = 1;
	}
	
	do
	{
		printf("Insert letter: \n");
		letter = getchar();
		PrintCharWithLutImp(letter);
	}
	while( letter != ESC_ASCII );
	
	system("stty icanon echo");
	
	return 0;
}

static int PrintCharWithLutImp(char letter)
{
	lut[(int) letter]();
	return 0;
}

/* Initialize Lookup Table */
static void InitLut( void (*func[])(void))
{
	size_t i = 0;
	
	while ( i < LUT_SIZE )
	{
		switch (i)
		{
			case A_ASCII:
				func[i] = PrintA;
				break;
			case T_ASCII:
				func[i] = PrintT;
				break;
			default:
				func[i] = Empty;
		}
		++i;
	}	
}

static void PrintA(void)
{
	printf("A pressed\n");
}

static void PrintT(void)
{
	printf("T pressed\n");
}

static void PrintEsc(void)
{
	printf("Bye Bye\n");
}

static void Empty(void)
{}







