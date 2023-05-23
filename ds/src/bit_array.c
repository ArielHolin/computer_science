/*******************************************************************************
*  bit_array.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Bnaya                                                             *
*******************************************************************************/
#include <assert.h> /* assert   */
#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* size_t   */

#include "../include/bit_array.h"

#define NUM_OF_BITS (sizeof(bit_arr_ty) * CHAR_BIT)
#define ASCII_LEN  256

#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

/*************** Helper Function - Set mask ***********************************/

/* Return a mask of 64 bits, where the only set bit is at position value. */
static bit_arr_ty SetMaskByPosition (size_t position)
{
	bit_arr_ty mask = (bit_arr_ty)1;
	
	return mask << position;
}


/************** BitsArrResetAll ***********************************************/

bit_arr_ty BitsArrResetAll(bit_arr_ty bit_array)
{
	return (bit_array & (bit_arr_ty)0);
}

/*************** BitsArrSetAll ************************************************/

bit_arr_ty BitsArrSetAll(bit_arr_ty bit_array)
{
	return ~BitsArrResetAll(bit_array);
}

/************* BitsArrSetOn ***************************************************/

bit_arr_ty BitsArrSetOn(bit_arr_ty bit_array, size_t position)
{	
	bit_arr_ty mask = SetMaskByPosition(position);
	
	assert (position < NUM_OF_BITS);
	
	return bit_array | mask;	
}

/*********** BitsArrSetOff ****************************************************/

bit_arr_ty BitsArrSetOff(bit_arr_ty bit_array, size_t position)
{
	bit_arr_ty mask = ~(SetMaskByPosition(position));
	
	assert (position < NUM_OF_BITS);
	
	return bit_array & mask;
}

/*********** BitsArrGetVal ****************************************************/

size_t BitsArrGetVal(bit_arr_ty bit_array, size_t position)
{
	bit_arr_ty mask = SetMaskByPosition(position);
	
	assert (position < NUM_OF_BITS);
	
	mask &= bit_array;
	
	return mask >> position;
}

/*********** BitsArrRotR ******************************************************/

bit_arr_ty BitsArrRotR(bit_arr_ty bit_array, size_t num_of_rot)
{
	size_t mod_num_of_rot = num_of_rot % NUM_OF_BITS; /* If num_of_rot >= 64 */
	bit_arr_ty left_most_bits = (bit_array << (NUM_OF_BITS - mod_num_of_rot));
	bit_array >>= mod_num_of_rot;
	
	return bit_array | left_most_bits;
}

/********** BitsArrRotL *******************************************************/

bit_arr_ty BitsArrRotL(bit_arr_ty bit_array, size_t num_of_rot)
{
	size_t mod_num_of_rot = num_of_rot % NUM_OF_BITS; /* If num_of_rot >= 64 */
	bit_arr_ty right_most_bits = (bit_array >> (NUM_OF_BITS - mod_num_of_rot));
	bit_array <<= mod_num_of_rot;
	
	return bit_array | right_most_bits;
}

/********** CountOn ***********************************************************/

static void InitBitsSetTable(size_t BitsSetTable[])
{
	size_t i = 0;
	
	BitsSetTable[0] = 0;
	
	for ( i = 1; i < ASCII_LEN; ++i)
	{
		BitsSetTable[i]  = (i & (bit_arr_ty)1) + BitsSetTable[i/2];
	}
}


size_t BitsArrCountOn(bit_arr_ty bit_array)
{
	static size_t BitsSetTable[ASCII_LEN];
	
	static int InitsBitFlag = 1;
	
	if ( InitsBitFlag )
	{
		InitBitsSetTable(BitsSetTable);
		InitsBitFlag -= 1;
	}
	
	return BitsSetTable[bit_array & 0xff] +
	       BitsSetTable[(bit_array >> 8) & 0xff] +
	       BitsSetTable[(bit_array >> 16) & 0xff] + 
	       BitsSetTable[(bit_array >> 24) & 0xff] +
	       BitsSetTable[(bit_array >> 32) & 0xff] + 
	       BitsSetTable[(bit_array >> 40) & 0xff] +
	       BitsSetTable[(bit_array >> 48) & 0xff] +
	       BitsSetTable[(bit_array >> 56) & 0xff];
}

/*********** CountOff *********************************************************/

size_t BitsArrCountOff(bit_arr_ty bit_array)
{
	bit_array = ~bit_array;
	
	return BitsArrCountOn(bit_array);
}

/************ Flip ************************************************************/

bit_arr_ty BitsArrFlip(bit_arr_ty bit_array, size_t position)
{
	bit_arr_ty mask = SetMaskByPosition(position);
	
	assert (position < NUM_OF_BITS);
	
	return bit_array ^ mask;
}

/*********** ToString *********************************************************/

char *BitsArrToString(bit_arr_ty bit_array, char *dest)
{
	char *start_dest = dest;
	
	bit_arr_ty mask = SetMaskByPosition(NUM_OF_BITS - 1);
	size_t position = NUM_OF_BITS - 1;
	
	assert(dest);
	
	while ( mask )
	{
		*dest = ((mask & bit_array)>>position) + '0';
		++dest;
		mask >>= (bit_arr_ty)1;
		--position;
	}
	
	*dest = '\0';
	
	return start_dest;
}

/*********** SetBit ***********************************************************/

bit_arr_ty BitsArrSetBit(bit_arr_ty bit_array, size_t position, size_t bit_state)
{
	bit_arr_ty set_off_position = BitsArrSetOff(bit_array, position);
	size_t mask = bit_state << position;
	
	assert (position < NUM_OF_BITS);
	
	return mask ^ set_off_position;
}

/*********** Mirror ***********************************************************/

bit_arr_ty BitsArrMirror(bit_arr_ty bit_array)
{
	size_t mirror_lut[ASCII_LEN] = { R6(0), R6(2), R6(1), R6(3) };
    
    bit_arr_ty reverse_num = 0;
  
     /* Reverse and then rearrange */ 
  
     reverse_num = mirror_lut[ bit_array & 0xff ] << 56 | 
  
                   mirror_lut[ (bit_array >> 8) & 0xff ] << 48 | 
  
                   mirror_lut[ (bit_array >> 16 ) & 0xff ] << 40 |
                   mirror_lut[ (bit_array >> 24 ) & 0xff ] << 32 |
                   mirror_lut[ (bit_array >> 32 ) & 0xff ] << 24 |
                   mirror_lut[ (bit_array >> 40 ) & 0xff ] << 16 |
                   mirror_lut[ (bit_array >> 48 ) & 0xff ] << 8 |
                   mirror_lut[ (bit_array >> 56 ) & 0xff ];
    
    return reverse_num;
}

/*bit_arr_ty BitsArrMirror(bit_arr_ty bit_array)
{
	bit_array = (bit_array & 0x00000000ffffffff) << 32 | (bit_array & 0xffffffff00000000) >> 32;
	bit_array = (bit_array & 0x0000ffff0000ffff) << 16 | (bit_array & 0xffff0000ffff0000) >> 16;
	bit_array = (bit_array & 0x00ff00ff00ff00ff) << 8 | (bit_array & 0xff00ff00ff00ff00) >> 8;
	bit_array = (bit_array & 0x0f0f0f0f0f0f0f0f) << 4 | (bit_array & 0xf0f0f0f0f0f0f0f0) >> 4;
	bit_array = (bit_array & 0x3333333333333333) << 2 | (bit_array & 0xcccccccccccccccc) >> 2;
	bit_array = (bit_array & 0x5555555555555555) << 1 | (bit_array & 0xaaaaaaaaaaaaaaaa) >> 1;
	
	return bit_array;
}*/

