/*******************************************************************************
*  Quiz 4 - Bursa
*  Author: Ariel
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

typedef struct profit
{
	size_t buy_index;
	size_t sell_index;
	size_t profit;
} profit_ty;

profit_ty Bursa(int *arr, size_t size);

int main(void)
{
	int array[8] = {6, 12, 3, 5, 1, 4, 9, 2};
	size_t size = 8;
	
	profit_ty result = Bursa(array, size);
	
	printf("Buy index: %lu, Sell index: %lu, Profit: %lu\n", \
	        result.buy_index, result.sell_index, result.profit);
	
	return 0;
}

profit_ty Bursa(int *arr, size_t size)
{
	size_t buy = 0;
	size_t sell = 1;
	size_t profit = arr[sell] - arr[buy];
	
	profit_ty result;
	result.buy_index = 0;
	result.sell_index = 1;
	result.profit = arr[result.sell_index] - arr[result.buy_index];
	
	for ( sell = 1; sell < size; ++sell)
	{
		if ( arr[sell] < arr[buy])
		{
			buy = sell;
		}
		
		else
		{
			profit = arr[sell] - arr[buy];
			
			if (profit > result.profit)
			{
				result.profit = profit;
				result.buy_index = buy;
				result.sell_index = sell;
			}
		}
	}
	
	return result;
}
