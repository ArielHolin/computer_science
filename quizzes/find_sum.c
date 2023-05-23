/*******************************************************************************
*  Quiz ws3
*  Author: Ariel
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int IsSumFound(int *sort_arr, int sum, int arr_size, int *ind1, int *ind2);

int main(void)
{
	int array[5] = {2, 4, 7, 12, 14};
	int *ind1 = (int *)malloc(sizeof(int));
	int *ind2 = (int *)malloc(sizeof(int));
	
	IsSumFound(array, 21, 5, ind1, ind2);
	
	free(ind1);
	free(ind2);
	
	return 0;
}

int IsSumFound(int *sort_arr, int sum, int arr_size, int *ind1, int *ind2)
{
	int first_ind = 0;
	int last_ind = arr_size - 1;
	
	while (first_ind < last_ind)
	{
		if (sort_arr[first_ind] == sum)
		{
			printf("Index is: %d\n", first_ind);
			*ind1 = first_ind;
			return 1;
		}
		
		if (sort_arr[last_ind] == sum)
		{
			printf("Index is: %d\n", last_ind);
			*ind2 = last_ind;
			return 1;
		}
		
		if (sort_arr[first_ind] + sort_arr[last_ind] < sum)
		{
			++first_ind;
			continue;
		}
		
		if (sort_arr[first_ind] + sort_arr[last_ind] > sum)
		{
			--last_ind;
			continue;
		}
		
		printf("Indices Are: %d, %d\n", first_ind, last_ind);
		*ind1 = first_ind;
		*ind2 = last_ind;
		return 1;
	}
	
	printf("No indices found :( \n");
	return 0;
}
