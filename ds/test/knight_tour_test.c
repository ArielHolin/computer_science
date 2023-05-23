/*******************************************************************************
*  knight_tour_test.c                                                          *
*  Author: Ariel                                                               *
*  Reviewer: Nasrat                                                            *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "knight_tour.h"

void TestKnightsTour(pos_ty start_pos, time_t time_cap);

int main(void)
{	
	TestKnightsTour(56, 50);
	TestKnightsTour(7, 50);
	TestKnightsTour(30, 50);
	TestKnightsTour(43, 50);	
	return 0;
}

void TestKnightsTour(pos_ty start_pos, time_t time_cap)
{
	size_t i = 0;
	size_t j = 0;
	int x = 0;
	int y = 0;
	stat_ty status = NOT_FOUND;
	pos_ty route_dest[DIM * DIM];
	
	for(i = 0; i < (DIM * DIM); ++i)
	{
		route_dest[i] = 0;
	}
	
	status = KnightsTour(start_pos, route_dest, time_cap);
	
	if(NOT_FOUND == status)
	{
		printf("Route was not found for starting position: %d\n\n", start_pos);
		printf("----------\n\n");
		return;
	}
	
	if(TIME_OUT == status)
	{
		printf("TIME OUT! Couldn't find route at given time frame\n\n");
		printf("----------\n\n");
		return;
	}
	
	ParsePos(start_pos, &x, &y);
	
	printf("Route Found!\n\nStarting Position on board: x: %d, y: %d\n\n", y, x);
	printf("Board layout:\n\n");
	
	for(i = 0; i < DIM; ++i)
	{
		for(j = 0; j < DIM; ++j)
		{
			printf("%d ", route_dest[i*DIM +j]);
		}
		printf("\n");
	}
	printf("----------\n\n");	
}
