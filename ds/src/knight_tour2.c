/*******************************************************************************
*  knight_tour.c - phase 2 (Warnsdorff Algorithm)                              *
*  Author: Ariel                                                               *
*  Reviewer: Nasrat                                                            *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <time.h>   /* time_t, time */
#include <assert.h> /* assert       */

#include "knight_tour.h"
#include "bit_array.h"

#define X 0
#define Y 1

static stat_ty RecKnightsTour(pos_ty position, pos_ty route_dest[DIM * DIM], 
                              size_t valid_positions[DIM * DIM], size_t *board, 
                              size_t move_ind, time_t start_time, 
                              time_t time_cap);
static void InitLut(size_t valid_positions[DIM * DIM], int knight_moves[DIM][2]);
static pos_ty FindBestAccessible(size_t valid_positions[DIM * DIM],  
                                                              size_t bit_array);
static pos_ty FindAccessibleInd(size_t bit_array);
static int IsInBounds(char x, char y);

/************* InitPos ********************************************************/

pos_ty InitPos(int x, int y)
{		
	return ((x * DIM) + y);
}

/************* ParsePos *******************************************************/

void ParsePos(pos_ty pos, int *x, int *y)
{
	*y = pos % DIM;
	*x = pos / DIM;
}

/************* KnightsTour ****************************************************/

stat_ty KnightsTour(pos_ty start_pos, pos_ty route_dest[DIM * DIM], time_t time_cap)
{
	size_t board = BitsArrSetOn(0, start_pos);
	size_t move_ind = 0;
	size_t valid_positions[DIM * DIM];
	size_t i = 0;
	int knight_moves[DIM][2] = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, 
	                            {-1, -2}, {-2, 1}, {-2, -1}};

	time_t start_time = 0;
	
	for(i = 0; i < (DIM * DIM); ++i)
	{
		valid_positions[i] = 0;
	}
	
	InitLut(valid_positions, knight_moves);
	
	start_time = time(NULL);
	
	return RecKnightsTour(start_pos, route_dest, valid_positions, &board, 
	                      move_ind, start_time, time_cap);
}

/* Helper function - Recursive implementation of KnightsTour */
static stat_ty RecKnightsTour(pos_ty position, pos_ty route_dest[DIM * DIM], 
                              size_t valid_positions[DIM * DIM], size_t *board, 
                              size_t move_ind, time_t start_time, 
                              time_t time_cap)
{
	pos_ty next_pos = 0;
	pos_ty i = 0;
	size_t num_of_accessibles = BitsArrCountOn(valid_positions[position]);
	size_t bit_array = valid_positions[position];
	stat_ty status = NOT_FOUND;
	
	assert(board);
	
	if(time_cap < time(NULL) - start_time)
	{
		return TIME_OUT;
	}
	
	route_dest[position] = move_ind;
	
	if((DIM*DIM - 1) == move_ind)
	{
		return FOUND;
	}
	
	for(i = 0; i < num_of_accessibles; ++i)
	{
		next_pos = FindBestAccessible(valid_positions, bit_array);
		
		if(0 == BitsArrGetVal(*board, next_pos))
		{
			*board = BitsArrSetOn(*board, (size_t)next_pos);
			
			status = RecKnightsTour(next_pos, route_dest, valid_positions, board, 
			                        move_ind + 1, start_time, time_cap);
			
			if(NOT_FOUND != status)
			{
				return status;
			}
			
			*board = BitsArrSetOff(*board, (size_t)next_pos);
		}
		
		bit_array = BitsArrSetOff(bit_array, (size_t)next_pos);
	}
	
	return status;
}

/************* InitLut ********************************************************/

static void InitLut(size_t valid_positions[DIM * DIM], int knight_moves[DIM][2])
{
	int curr_x = 0;
	int curr_y = 0;
	pos_ty i = 0;
	pos_ty j = 0;
	pos_ty pos = 0;
	
	for(i = 0; i < (DIM * DIM); ++i)
	{
		ParsePos(i, &curr_x, &curr_y);
		
		for(j = 0; j < DIM; ++j)
		{
			if(IsInBounds(curr_x + knight_moves[j][X], curr_y + 
			                                                knight_moves[j][Y]))
			{
				pos = InitPos(curr_x + knight_moves[j][X], curr_y + 
				                                            knight_moves[j][Y]);
				valid_positions[i] = BitsArrSetOn(valid_positions[i], 
				                                                   (size_t)pos);
			}
		}
	}
}

/************* FindBestAccessible *********************************************/

static pos_ty FindBestAccessible(size_t valid_positions[DIM * DIM],
                                                               size_t bit_array)
{
	pos_ty best_accessible_pos = 0;
	pos_ty curr_accessible_pos = 0 ;
	size_t num_of_accessibles = BitsArrCountOn(bit_array);
	size_t max_accessibles = DIM + 1;
	size_t i = 0;
	
	for(i = 0; i < num_of_accessibles; ++i)
	{
		curr_accessible_pos = FindAccessibleInd(bit_array);
	
		if(BitsArrCountOn(valid_positions[curr_accessible_pos]) < max_accessibles)
		{
			best_accessible_pos = curr_accessible_pos;
			max_accessibles = BitsArrCountOn(valid_positions[best_accessible_pos]);
		}
		
		bit_array &= (bit_array - 1);
	}
	
	return best_accessible_pos;
}

static pos_ty FindAccessibleInd(size_t bit_array)
{
	return (pos_ty)(BitsArrCountOn(bit_array - 1) + 1 - BitsArrCountOn(bit_array));
}

/************* Helper Functions ***********************************************/

static int IsInBounds(char x, char y)
{	
	return (((x >= 0) && (x < DIM)) && ((y >= 0) && (y < DIM)));
}
