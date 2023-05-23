#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "dictionary.h"
#include "mt_merge_sort.h"

#define ILRD_SUCCESS 0
#define ILRD_FAILURE 1
#define NUM_OF_THREAD 7

int max_level;

typedef struct array_data
{
    char ** og_array;
    size_t s_index;
    size_t e_index;
    size_t thread_level;

}array_data_ty;

void *ThreadFunc(void *args);
int CmpFunc(const void *data1, const void *data2);
void InitStruct(array_data_ty* data_struct, size_t s_in, size_t e_in,
                size_t level, char ** arr);

int MyStrcmp(const void *str1, const void *str2);

static int MergeLeftAndRight(char **left_array, char **right_array, 
                                 int left_num_elements, int right_num_elements);


int main()
{
    size_t array_size = sizeof(dict_arr)/(sizeof(char*));
    max_level = log(NUM_OF_THREAD) + 1;
    qsort(dict_arr, array_size, sizeof(char *), CmpFunc);
    MTMergeSort(dict_arr, array_size);
   

    return 0;
}

int MTMergeSort(char **arr_to_sort, size_t arr_size)
{
    pthread_t threads_array[2];
    array_data_ty data_array[2];
    size_t index = 0;
    size_t s_index = 0;
    size_t left_arr_size = (arr_size / 2) + (arr_size % 2);
    int my_level = 0;

    InitStruct(&data_array[0], s_index, left_arr_size - 1, my_level + 1, arr_to_sort);
    InitStruct(&data_array[1], left_arr_size, arr_size, my_level + 1, arr_to_sort);

    for (index = 0; index < 2; index++)
    {
        if(0 != pthread_create(&threads_array[index], NULL, ThreadFunc, &data_array[index]))
        {
            perror("pthread_create Failed");
            return -1;
        }
    }

    for (index = 0; index < 2; index++)
    {
        if(0 != pthread_join(threads_array[index], NULL))
        {
            perror("pthread_join Failed");
            return -1;
        }
    }
    printf("before merge\n");
    /* merge */
    MergeLeftAndRight(data_array[0].og_array + data_array[0].s_index, data_array[1].og_array + data_array[1].s_index,
                      data_array[0].e_index - data_array[0].s_index, data_array[1].e_index - data_array[1].s_index);

    return 0;
}

void *ThreadFunc(void *args)
{
    array_data_ty *my_data = (array_data_ty*)args;
    
    if(my_data->thread_level == max_level)
    {
        /* sort */
        qsort(my_data->og_array + my_data->s_index, my_data->e_index - my_data->s_index, sizeof(char *), MyStrcmp);
    }
    else
    {
        pthread_t threads_array[2];
        array_data_ty data_array[2];
        size_t index = 0;
        size_t s_index = my_data->s_index;
        size_t arr_size = my_data->e_index - my_data->s_index;
        size_t left_arr_size = (arr_size / 2) + (arr_size % 2);
        int my_level = my_data->thread_level;

        InitStruct(&data_array[0], s_index, s_index + left_arr_size - 1, my_level + 1, my_data->og_array);
        InitStruct(&data_array[1], s_index + left_arr_size, s_index + arr_size, my_level + 1, my_data->og_array);

        for (index = 0; index < 2; index++)
        {
            if(0 != pthread_create(&threads_array[index], NULL, ThreadFunc, &data_array[index]))
            {
                perror("pthread_create Failed");
                return NULL;
            }
        }

        for (index = 0; index < 2; index++)
        {
            if(0 != pthread_join(threads_array[index], NULL))
            {
                perror("pthread_join Failed");
                return NULL;
            }
        }

    /* merge */
    MergeLeftAndRight(data_array[0].og_array + data_array[0].s_index, data_array[1].og_array + data_array[1].s_index,
                      data_array[0].e_index - data_array[0].s_index, data_array[1].e_index - data_array[1].s_index);
    }

    return NULL;
}

int CmpFunc(const void *data1, const void *data2)
{
    int num = 0;
    srand(time(NULL));
	num = rand()%(3);
    if(0 == num)
    {
        return 0;
    }
    else if(1 == num)
    {
        return 1;
    }
    return -1;
}

void InitStruct(array_data_ty* data_struct, size_t s_in, size_t e_in,
                size_t level, char ** arr)
{
    data_struct->e_index = e_in;
    data_struct->s_index = s_in;
    data_struct->thread_level = level;
    data_struct->og_array = arr;

}

int MyStrcmp(const void *str1, const void *str2)
{
    const char *data1 = (char*)str1;
    const char *data2 = (char*)str2;

    return strcmp(data1, data2);
}


static int MergeLeftAndRight(char **left_array, char **right_array, 
                                  int left_num_elements, int right_num_elements)
{
    char **sorted_array = NULL;
    int total_num_elements = 0;
    int left_ind = 0;
    int right_ind = 0;
    int sorted_ind = 0;
    

    assert(left_array);
    assert(right_array);

    total_num_elements = left_num_elements + right_num_elements;

    sorted_array = (char **)malloc(sizeof(char *) * total_num_elements);

    if(!sorted_array)
    {
        return ILRD_FAILURE;
    }
    
    while((left_ind < left_num_elements) && (right_ind < right_num_elements))
    {
        
        if(strcmp(left_array[left_ind], right_array[right_ind]) <= 0)
        {
            sorted_array[sorted_ind] = left_array[left_ind];
            ++left_ind;
        }

        else
        {
            sorted_array[sorted_ind] = right_array[right_ind];
            ++right_ind;
        }

        ++sorted_ind;
        
    }

    while(right_ind < right_num_elements)
    {
        sorted_array[sorted_ind] = right_array[right_ind];
        ++sorted_ind;
        ++right_ind;
    }

    while(left_ind < left_num_elements)
    {
        sorted_array[sorted_ind] = left_array[left_ind];
        ++sorted_ind;
        ++left_ind;
    }
   
    memcpy(left_array, sorted_array, sizeof(char *) * total_num_elements);
    puts("af mem cpy");
    free(sorted_array);
    sorted_array = NULL;

    return ILRD_SUCCESS;
}