/************************************************
*   ws1.c
*   author : Ariel Holin
*   reviewer: Maayan
*************************************************/

#include <stdio.h>    /* printf */

void HelloWorld(void);
void TestHelloWorld(void);

double PowersOfTen(int n);
void TestPowersOfTen(void);

int FlipDigits(int n);
void TestFlipDigits(void);

void Swap(int *ptr1, int *ptr2);
void TestSwap(void);

const int TEN = 10;

int main(void)
{
	TestHelloWorld();
	TestPowersOfTen();
	TestFlipDigits();
	TestSwap();
	return 0;	
}


/*********************Hello World**********************************************/

/* converting hexa decimal array into a string and print "Hello World!" */
void HelloWorld(void)
{	
	/* int i = 0; */
	char hex_array[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 
	                    0x72, 0x6c, 0x64, 0x21, 0x22};

    
    /*	while (hex_array[i] != 0x00)
    	{
        	printf("%c", hex_array[i]);
        	i++;
    	}
    */	
    	printf("%s\n", hex_array); 
}

void TestHelloWorld(void)
{
	HelloWorld();
	printf("--------------\n");
}

/********************Powers of Ten*********************************************/

/* receives power and return 10^power */
double PowersOfTen(int power)
{
	int i = 0;
	float base = TEN;
	float res = 1;
	
	if (0 > power)
	{
		base = 1. / base;
		power = -power;
	}
	
	for (i = 0; i < power; i++)
	{
		res *= base;
	}
	
	return res;	
}


void TestPowersOfTen(void)
{
	printf("PowerByN(0) should return 1.00\n");
	printf("Validity check: %0.2f\n\n", PowersOfTen(0));
	
	printf("PowerByN(-1) should return 0.1\n");
	printf("Validity check: %0.1f\n\n", PowersOfTen(-1));
	
	printf("PowerByN(-4) should return 0.0001\n");
	printf("Validity check: %0.4f\n\n", PowersOfTen(-4));
	
	printf("PowerByN(5) should return 10000.00\n");
	printf("Validity check: %0.2f\n", PowersOfTen(5));
	
	printf("--------------\n");
}

/*******************Flip Digits************************************************/

/* Helper function for FlipDigits().
   receives integer and return the value of decimal digit's place:
   single digit number = 0, 
   2 digits number = 1,
   3 digits number = 2, 
   ...
*/  
int FindTenPlace(int n)     
{
	int counter = 0;
	
	if (0 > n)
	{
		n = -n;
	}
	
	while (n >= TEN)
	{
		counter++;
		n /= TEN;
	}
	
	return counter;
}


/* receives an int number, flip its digits and return a new number.
   Works for base 10 only */
int FlipDigits(int n)           
{
	int res = 0;
	int pow = FindTenPlace(n);
	int tmp;
	
	if (0 == n % TEN)
	{
		n /= TEN;
		pow--;
	} 
	
	while (0 != n)
	{
		tmp = (n % TEN);
		res += tmp * PowersOfTen(pow);
		
		pow--;
		n /= TEN;
	}
	
	return res;
}


void TestFlipDigits(void)
{
	printf("Flip(0) should return 0.\n");
	printf("Validity check: %d\n\n", FlipDigits(0));
	
	printf("Flip(1000) should return 1.\n");
	printf("Validity check: %d\n\n", FlipDigits(1000));
	
	printf("Flip(1230) should return -321.\n");
	printf("Validity check: %d\n\n", FlipDigits(-1230));
	
	printf("Flip(5047803) should return 3087405.\n");
	printf("Validity check: %d\n", FlipDigits(5047803));
	
	printf("--------------\n");
}

/*************************Swap*************************************************/

/* Swapping the values of the integers. */
void Swap(int *ptr1, int *ptr2)
{
	int tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

void TestSwap(void)
{
	int val1 = 1;
	int val2 = 2;
	
	printf("Before swap: val1 = %d, val2 = %d\n", val1, val2);
	
	Swap(&val1, &val2);
	
	printf("After swap: val1 = %d, val2 = %d\n", val1, val2);
}
