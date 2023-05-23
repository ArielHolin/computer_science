/*********************************************************************
* Description: Cover a chess board by travelling with a knight.
                The knight must visit each square only once.
* Name: HRD20
* Date: 01.11.21
* Versions:
    1.0 - Initial version
    1.1 - Added typdef for pos_ty and explanation for KnightsTour 
        time complexity.
    1.2 - Added time_cap argument in KnightsTour function.
        Also added TIME_OUT enum in stat_ty for more informative return
        value.
*********************************************************************/
#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__
 
#include <time.h>   /* time_t */

#define DIM 8

typedef enum stat
{
    NOT_FOUND = 0,
    FOUND = 1,
    TIME_OUT = 2
} stat_ty;

typedef unsigned char pos_ty;
/*******************************************************************************
* Function Description: Check if there is a path for a knight that covers all
                        the board by visiting each square exactly once.
			       
* Arguments:
            start_pos - starting position of the knight. Should be used with 
                        the function InitPos.
                        E.G if start_pos coordination is x,y then 
                        start_pos = InitPos(x, y) 
            route_dest - an array containing the correct route (if FOUND)
            time_cap - time limit for the function to run (in seconds)

* Return value:  status of function 
   
* Notes:
        
* Time Complexity:	O(8^(DIM^2)) time and space
    64 possible position (DIM^2), where in each position you have 8 possible moves.
    So in each of the (DIM^2) positions, you must consider 8 possible moves.
    All in all: 8^(DIM^2) 
*******************************************************************************/
stat_ty KnightsTour(pos_ty start_pos, pos_ty route_dest[DIM * DIM], time_t time_cap);

/*******************************************************************************
* Function Description: Translates a given coordination to a pos_ty
                        representation.
			       
* Arguments:
            x - row position 
            y - column position

* Return value:  pos_ty representation
   
* Notes: 
        
* Time Complexity:	O(1) time and space
*******************************************************************************/
pos_ty InitPos(int x, int y);

/*******************************************************************************
* Function Description:  Translates a given pos_ty representation to 
                        given coordination.
			       
* Arguments:
             pos - position to translate.
             x - pointer to row coordination
             y - pointer to column coordination

* Return value:  
   
* Notes: 
        
* Time Complexity:	O(1) time and space
*******************************************************************************/
void ParsePos(pos_ty pos, int *x, int *y);

#endif /* __KNIGHT_TOUR_H__ */
