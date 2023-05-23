/*******************************************************************************
*  Libraries exercise: so2.c                                                   *
*  Author: Ariel                                                               *
*  Reviewer: Philip                                                            *
*******************************************************************************/
#include <stdio.h> /* printf */

#include "libar.h"

void Bar2(void)
{
	printf("This is Bar2() !\n");
	Foo2();
	printf("%d\n", g_m);
}
