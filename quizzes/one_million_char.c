/*******************************************************************************
*  one_million_char.c quiz                                                     *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t        */
#include <stdio.h>  /* printf, scanf */

#define ASCII_SIZE 256
#define ESC        27

void OneMillionChar(void);
char FindMaxAscii(int lut[]);
void InitLut(int lut[]);

int main(void)
{
	OneMillionChar();
	return 0;
}


void OneMillionChar(void)
{
	int lut[ASCII_SIZE];
	char chr = 0;
	
	InitLut(lut);
	
	do
	{
		printf("Please insert character: ");
		scanf("%c", &chr);
		
		if( chr == '0' )
		{
			printf("%c\n", (char)FindMaxAscii(lut));
			InitLut(lut);
		}
		
		else
		{
			++lut[chr];
		}
		
	}
	while( chr != ESC );
}

char FindMaxAscii(int lut[])
{
	int max = 0;
	size_t i = 0;
	char max_chr = 0;
	
	for( i = 0; i < ASCII_SIZE; ++i )
	{
		if( lut[i] > max )
		{
			max_chr = (char)i;
		}
	}
	
	return max_chr;
}

void InitLut(int lut[])
{
	size_t i = 0;
	
	for( i = 0; i < ASCII_SIZE; ++i )
	{
		lut[i] = 0;
	}
}
