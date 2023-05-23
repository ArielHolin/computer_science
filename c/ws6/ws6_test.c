/**************************************************
*  ws6_test.c
*  Author: Ariel
*  Reviewer: Bnaya
**************************************************/
#include <stdio.h>   /* printf */
#include <assert.h>  /* assert */
#include "ws6.h"

void TestPow2(void);
void TestIsPowOf2Loop(void);
void TestIsPowOf2NoLoop(void);
void TestAddOneNoArithmetic(void);
void TestByteMirrorLoop(void);
void TestPrint3BitsUnsignedInts(void);
void TestTwoAndSix(void);
void TestTwoOrSix(void);
void TestSwapBit3AndBit(void);
void TestFindClosestDivBy16(void);
void TestSwap(void);
void TestCountSetBits(void);
void TestCountSetBitsNoLoop(void);

int main(void)
{
	/*TestPow2();
	TestIsPowOf2Loop();
	TestIsPowOf2NoLoop();
	TestAddOneNoArithmetic();
	TestPrint3BitsUnsignedInts();
	TestTwoAndSix();
	TestTwoOrSix();
	TestSwapBit3AndBit();
	TestFindClosestDivBy16();
	TestSwap();
	TestCountSetBits();
	TestCountSetBitsNoLoop();
	TestByteMirrorLoop();*/
	PrintFloatBits();
	return 0;
}

void TestPow2(void)
{
	assert( 5 == Pow2(5, 0) );
	assert( 0 == Pow2(0, 7) );
	assert( 88 == Pow2(22, 2) );
	
	printf("TestPow2() Success!\n----------\n");
}

void TestIsPowOf2Loop(void)
{
	assert ( 0 == IsPowOf2Loop(0) );
	assert ( 1 == IsPowOf2Loop(2) );
	assert ( 0 == IsPowOf2Loop(3) );
	assert ( 1 == IsPowOf2Loop(16) );
	assert ( 0 == IsPowOf2Loop(22) );
	
	printf("TestIsPowOf2Loop() Success!\n----------\n");
}

void TestIsPowOf2NoLoop(void)
{
	assert ( 0 == IsPowOf2NoLoop(0) );
	assert ( 1 == IsPowOf2NoLoop(2) );
	assert ( 0 == IsPowOf2NoLoop(3) );
	assert ( 1 == IsPowOf2NoLoop(16) );
	assert ( 0 == IsPowOf2NoLoop(22) );
	
	printf("TestIsPowOf2NoLoop() Success!\n----------\n");
}

void TestAddOneNoArithmetic(void)
{
	assert ( 1 == AddOneNoArithmetic(0) );
	assert ( 54 == AddOneNoArithmetic(53) );
	assert ( -9 == AddOneNoArithmetic(-10) );
	assert ( -198 == AddOneNoArithmetic(-199) );
	
	printf("TestAddOneNoArithmetic() Success!\n----------\n");
}

void TestPrint3SetBitsUnsignedInts(void)
{
	unsigned int array[10] = {15, 19, 24, 44, 47, 76, 79, 98, 99, 100};
	
	Print3SetBitsUnsignedInts(array, 10);
}

void TestByteMirrorLoop(void)
{
	assert ( 1 == ByteMirrorLoop(4) );
	assert ( 5 == ByteMirrorLoop(5) );
	assert ( 3 == ByteMirrorLoop(6) );
	assert ( 23 == ByteMirrorLoop(29) );
	
	printf("TestByteMirrorLoop() Success!\n----------\n");
}

void TestTwoAndSix(void)
{
	assert ( 1 == TwoAndSix('f') );
	assert ( 1 == TwoAndSix('u') );
	assert ( 0 == TwoAndSix('A') );
	assert ( 1 == TwoAndSix('D') );
	
	printf("TestTwoAndSix() Success!\n----------\n");
}

void TestTwoOrSix(void)
{
	assert ( 1 == TwoOrSix('f') );
	assert ( 1 == TwoOrSix('u') );
	assert ( 1 == TwoOrSix('A') );
	assert ( 1 == TwoOrSix('D') );
	assert ( 0 == TwoOrSix('!') );
	
	printf("TestTwoOrSix() Success!\n----------\n");
}

void TestSwapBit3AndBit(void)
{
	assert ( 'I' == SwapBit3AndBit5('a'));
	assert ( 'h' == SwapBit3AndBit5('h'));
	assert ( 'W' == SwapBit3AndBit5('W'));
	assert ( 'r' == SwapBit3AndBit5('Z'));
	
	printf("TestSwapBit3AndBit5() Success!\n----------\n");
}

void TestFindClosestDivBy16(void)
{
	assert ( 32 == FindClosestDivBy16(33));
	assert ( 16 == FindClosestDivBy16(22));
	assert ( 16 == FindClosestDivBy16(17));
	assert ( 48 == FindClosestDivBy16(48));
	assert ( 64 == FindClosestDivBy16(65));
	
	printf("TestClosestDivBy16() Success!\n----------\n");
}

void TestSwap(void)
{
	int x = 42;
	int y = 17;
	
	printf("x before: %d, y before: %d\n", x, y);
	
	Swap(&x, &y);
	
	printf("x after: %d, y after: %d\n", x, y);
	
	printf("TestSwap() Success!\n----------\n");
}

void TestCountSetBits(void)
{
	assert ( 3 == CountSetBits(41) );
	assert ( 4 == CountSetBits(58) );
	assert ( 5 == CountSetBits(117) );
	assert ( 6 == CountSetBits(125) );
	
	printf("TestCountSetBits() Success!\n----------\n");
}

void TestCountSetBitsNoLoop(void)
{
	assert ( 3 == CountSetBitsNoLoop(41) );
	assert ( 4 == CountSetBitsNoLoop(58) );
	assert ( 5 == CountSetBitsNoLoop(117) );
	assert ( 6 == CountSetBitsNoLoop(125) );
	
	printf("TestCountSetBitsNoLoop() Success!\n----------\n");
}
