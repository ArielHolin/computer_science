/*******************************************************************************
*  ws3.c
*  Author: Ariel
*  Reviewer: Liel
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

size_t EnvpCounter(char **envp);
size_t FindEnvpName(char *str);
char *WriteLowName(char *dest, char *src, size_t len);
void EnvpImp(char **env);
int JosephusMath(int soldiers, int step);
void JosephusMathImp(void);
int *Josephus(int *array, int array_len);
int JosephusImp(void);
void DataTypeImp(void);

int main(int argc, char **argv, char **envp)
{
	if (argc != 2)
	{
		printf("Usage: ./ws3 JosephusMath/Josephus/DataType/Env\n");
		return 1;
	}
	
	if (strcmp(argv[1], "JosephusMath") == 0)
	{
		JosephusMathImp();
		return 0;
	}
	
	if (strcmp(argv[1], "Josephus") == 0)
	{
		JosephusImp();
		return 0;
	}
	
	if (strcmp(argv[1], "DataType") == 0)
	{
		DataTypeImp();
		return 0;
	}
	
	EnvpImp(envp);
	return 0;
}

/********************Environment Helper Functions******************************/

/* Counts the number of environment variables */
size_t EnvpCounter(char **envp)
{
	size_t counter = 0;
	
	while (envp[counter])
	{
		++counter;
	}
	
	return counter;
}

/* Finds the length of str name.  Str name finished at char = '=' */
size_t FindEnvpName(char *str)
{
	size_t j = 0;
	
	while (str[j] != '=')
	{
		++j;
	}
	
	return j;
}

/* Writes src into dest in lower case letters. */
char *WriteLowName(char *dest, char *src, size_t len)
{
	size_t k = 0;
	
	for (k = 0; k < len; ++k)
	{
		dest[k] = tolower(src[k]);
	}
	
	dest[k] = '\0';
	
	return dest;
}

/* Implemantation of Env inside main */
void EnvpImp(char **envp)
{
	/* Calculate number of environment variables */
	size_t envp_ctr = EnvpCounter(envp);
	
	/* Allocate memory for envp list */
	char **envp_lst = (char **)malloc(envp_ctr * sizeof(char **));
	size_t i = 0;
	size_t j;
	
	/* For each environment variable */
	for (i = 0; i < envp_ctr; ++i)
	{
		j = 0; 
		
		/* Find the length of the environment variable name */
		j = FindEnvpName(envp[i]);
		
		/* Allocate the size of its name memory */
		envp_lst[i] = (char *)malloc(j * sizeof(char) + 1);
		
		/* Write its name letter by letter converting to lower case */
		envp_lst[i] = WriteLowName(envp_lst[i], envp[i], j);
		
		/* print the name, and free memory */
		printf("%s\n", envp_lst[i]);
		free(envp_lst[i]);
	}
	
	/* Free allocated memory */
	free(envp_lst);
}

/***************************Josephus Problem***********************************/

/***********************Recursive Implemantation*******************************/

int JosephusMath(int soldiers, int step)
{
	if (soldiers == 1)
	{
		return 1;
	}
	
	return ((JosephusMath(soldiers-1, step) + step - 1) % soldiers + 1);
}

/* Implemantaion inside main */
void JosephusMathImp(void)
{
	int soldiers = 100;
	int step = 2;
	printf("%d\n", JosephusMath(soldiers, step) - 1);
}

/***********************Arrays and Pointers Implemantation*********************/

int *Josephus(int *array, int array_len)
{
	int i = 0;
	int new_array_len = array_len / 2;
	int *new_arr = (int *)malloc(new_array_len * sizeof(int));
	
	if (array_len == 1)
	{
		free(new_arr);
		return array;
	}
	
	if (array_len % 2 == 0)
	{
		for (i = 0; i < array_len; i += 2)
		{
			new_arr[i/2] = array[i];
		}
	}
	
	else
	{
		for (i = 2; i < array_len; i += 2)
		{
			new_arr[(i/2) - 1] = array[i];
		}
	}
	
	free(array);
	
	return Josephus(new_arr, new_array_len);
}

/* Implemantation inside main including testing */
int JosephusImp(void)
{
	const int SOLDIERS = 100;
	int i = 0;
	int *array = (int *)malloc(SOLDIERS * sizeof(int));
	int *res = NULL;
	
	for (i = 0; i < SOLDIERS; ++i)
	{
		array[i] = i;
	}
	
	res = Josephus(array, SOLDIERS);
	
	if (JosephusMath(SOLDIERS, 2) - 1 != *res)
	{
		printf("Josephus Failed! :(\n");
		free(res);
		return 1;
	}
	
	else
	{
		printf("Josephus Success! :)\n");
		free(res);
		return 0;
	}
}

/**************************Data Types******************************************/

void DataTypeImp(void)
{
	printf("    short int is %2ld bytes \n", sizeof(short int));
	printf("          int is %2ld bytes \n", sizeof(int));
	printf("        int * is %2ld bytes \n", sizeof(int *));
	printf("     long int is %2ld bytes \n", sizeof(long int));
	printf("   long int * is %2ld bytes \n", sizeof(long int *));
	printf("   signed int is %2ld bytes \n", sizeof(signed int));
	printf(" unsigned int is %2ld bytes \n", sizeof(unsigned int));
	printf("\n");
	printf("        float is %2ld bytes \n", sizeof(float));
	printf("      float * is %2ld bytes \n", sizeof(float *));
	printf("       double is %2ld bytes \n", sizeof(double));
	printf("     double * is %2ld bytes \n", sizeof(double *));
	printf("  long double is %2ld bytes \n", sizeof(long double));
	printf("\n");
	printf("  signed char is %2ld bytes \n", sizeof(signed char));
	printf("         char is %2ld bytes \n", sizeof(char));
	printf("       char * is %2ld bytes \n", sizeof(char *));
	printf("unsigned char is %2ld bytes \n", sizeof(unsigned char));
}
