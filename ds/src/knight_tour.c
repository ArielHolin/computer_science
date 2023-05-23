/*******************************************************************************
*  knight_tour.c - phase 1                                                     *
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
                              int knight_moves[DIM][2], size_t *board, 
                              size_t move_ind, time_t start_time, 
                              time_t time_cap);
static int IsValidMove(char x, char y, size_t *board);

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
	time_t start_time = time(NULL);
	
	int knight_moves[DIM][2] = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, 
	                            {-1, -2}, {-2, 1}, {-2, -1}};
	
	return RecKnightsTour(start_pos, route_dest, knight_moves, &board, move_ind, 
	                      start_time, time_cap);
}

/* Helper function - Recursive implementation of KnightsTour */
static stat_ty RecKnightsTour(pos_ty position, pos_ty route_dest[DIM * DIM], 
                              int knight_moves[DIM][2], size_t *board, 
                              size_t move_ind, time_t start_time, 
                              time_t time_cap)
{
	pos_ty next_pos = 0;
	int curr_x = 0;
	int curr_y = 0;
	size_t i = 0;
	stat_ty status = NOT_FOUND;
	
	assert(board);
	
	if(time_cap < time(NULL) - start_time)
	{
		return TIME_OUT;
	}
	
	route_dest[position] = move_ind;
	
	if((DIM * DIM - 1) == move_ind)
	{
		return FOUND;
	}
	
	ParsePos(position, &curr_x, &curr_y);
	
	for(i = 0; i < DIM; ++i)
	{
		if(IsValidMove(curr_x + knight_moves[i][X], curr_y + knight_moves[i][Y], 
		                                                                 board))
		{
			next_pos = InitPos(curr_x + knight_moves[i][X], curr_y + 
			                                                knight_moves[i][Y]);
			*board = BitsArrSetOn(*board, (size_t)next_pos);
			
			status = RecKnightsTour(next_pos, route_dest, knight_moves, board, 
			                        move_ind + 1, start_time, time_cap);
			
			if(NOT_FOUND != status)
			{
				return status;
			}
			
			*board = BitsArrSetOff(*board, (size_t)next_pos);
		}
	}
	
	return status;
}

/************* Helper Functions ***********************************************/

static int IsValidMove(char x, char y, size_t *board)
{
	pos_ty pos = InitPos(x, y);
	
	assert(board);
	
	return (((x >= 0) && (x < DIM)) && ((y >= 0) && (y < DIM)) && 
	                                         (0 == BitsArrGetVal(*board, pos)));
}
