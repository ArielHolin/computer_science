/*******************************************************************************
 *   ex1.c                                                                     *
 *   Author: Ariel                                                             *
 * ****************************************************************************/
#include <stddef.h>

struct x
{
	int a;
};

/*******************************************************************************
************************************** main ***********************************/
int main(void)
{
	const int val_1_const = 1;
	const int val_1 = 5; 
	/*std::cout<<"val1 is "<<val_1<<std::endl;*/
	int const val_2_const = 2;
	int val_2 = 2;
	
	struct x * const ptr_1 = NULL;
	struct x const x1 = {val_1}; 
	const struct x *ptr_2 = NULL;
	const struct x * * const ptr_3 = NULL;
	/*int const * (* const f)(int *) = foo; */ 

}