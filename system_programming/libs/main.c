/*******************************************************************************
*  Libraries exercise: main.c                                                  *                              
*  Author: Ariel                                                               *
*  Reviewer: Philip                                                            *
*******************************************************************************/
#include <stdio.h> /* printf                 */
#include <dlfcn.h> /* dlopen, dlsym, dlclose */

#include "libar.h"

extern int g_a;

static void MyFunc(void);

int main(void)
{
	void *handle = NULL;
	void (*Bar2)(void);
	
	MyFunc();
	
	Foo();
	printf("%d\n", g_a);
	
	Bar1();
	
	handle = dlopen("libso2.so", RTLD_LAZY);
	
	if(handle)
	{
		*(void **)(&Bar2) = dlsym(handle, "Bar2");
		if(Bar2)
		{
			Bar2();
		}
	}
	
	dlclose(handle);
	
	return 0;
}

static void MyFunc(void)
{
	printf("This is MyFunc() !\n");
}
