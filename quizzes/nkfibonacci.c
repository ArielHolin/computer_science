/*******************************************************************************
 *  Fibonnaci N K                                                              *
 *  Author: Ariel                                                              *
 * ****************************************************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

int nkFibonacci(int n, int k);
int sum(int *arr, int k);

int main(void)
{
    int res = nkFibonacci(2, 4);
    printf("Nth element in the series: %d\n", res);
    return 0;
}

int nkFibonacci(int n, int k)
{
    int *arr = (int *)malloc(sizeof(int) * n + 1);
    int res = 0;

    if(!arr)
    {
        return NULL;
    }

    if(n <= k)
    {
        free(arr);
        return 1;
    }

    for(int i = 0; i < k; ++i)
    {
        arr[i] = 1;
    }

    for(int i = n-1; i >= n-k; --i)
    {
        arr[k - i + n - 1] = sum(&arr[n-i-1], k);
    }

    res = arr[n-1];
    free(arr);

    return res;
}

int sum(int *arr, int k)
{
    int res = 0;

    for(int i = 0; i < k; ++i)
    {
        res += arr[i];
    }

    return res;
}