/*******************************************************************************
 *  maxSubArray.c                                                              *
 *  Author: Ariel                                                              *
 * ****************************************************************************/
#include <stddef.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>

typedef struct maxSubArr
{
    size_t minIndex;
    size_t maxIndex;
    int maxSum;
}maxSubArr_ty;

maxSubArr_ty FindMaxSubArr(int *array, size_t arrSize);

int main(void)
{
    int array[9] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	
	maxSubArr_ty res = FindMaxSubArr(array, 9);
	
	printf("sum: %d, first ind: %li, last ind: %li\n", 
	        res.maxSum, res.minIndex, res.maxIndex);
	
    return 0;
}

maxSubArr_ty FindMaxSubArr(int *array, size_t arrSize)
{
    maxSubArr_ty ret = {0};
    size_t i = 0;

    int currSum = 0;
    ret.maxSum = 0;

    assert(array);
    assert(arrSize > 0);

    for(i = 0; i < arrSize; ++i)
    {
        currSum += array[i];

        if(currSum < 0)
        {
            ret.minIndex = i + 1;
            currSum = 0;
            continue;
        }

        if(currSum >= ret.maxSum)
        {
            ret.maxIndex = i;
            ret.maxSum = currSum;
        }
    }

    return ret;
}