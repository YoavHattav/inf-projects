/*********************************/
/*    Data Structures            */
/*    Bits Array                 */
/*    Author :Yoav Hattav        */
/*    Reviewed By:               */
/*    Date:     26/11/2019       */
/*                               */
/*********************************/

#include <assert.h> /* assert usage */

#include "bitsarray.h"

#define M1   0x5555555555555555 
#define M2   0x3333333333333333 
#define M4   0x0f0f0f0f0f0f0f0f 
#define M8   0x00ff00ff00ff00ff 
#define M16  0x0000ffff0000ffff 
#define M32  0x00000000ffffffff 
#define MSB  0x8000000000000000
#define ALLON 0xffffffffffffffff
#define ALLOFF 0x0
#define LSB  0x0000000000000001
#define WORD_IN_BITS 64



/* This function sets all bits to 1 */
size_t BArrSetAllBits(bitsarr_t bits)
{     
    bits |= ALLON;   
    
    return bits;
}

/* This function sets all bits to 0 */
size_t BArrResetAllBits(bitsarr_t bits)
{
    bits &= ALLOFF;
    
    return bits;
}

/* This function checks if given bit is 1 */
int BArrIsOn(const bitsarr_t bits, int position)
{   
    return ((unsigned long)(bits & (LSB << (position - 1))) == (unsigned long)(LSB << (position - 1)));
}

/* This function checks if given bit is 0 */
int BArrIsOff(bitsarr_t bits, int position)
{

    return ((bits & (LSB << (position - 1))) == 0x0);
}

/* This function return the number of the on bits using Hamming Weight */
size_t BArrCountOn(bitsarr_t bits)
{
    bits = (M1 & bits) + (M1 & (bits >> 1));
    bits = (M2 & bits) + (M2 & (bits >> 2));
    bits = (M4 & bits) + (M4 & (bits >> 4));
    bits = (M8 & bits) + (M8 & (bits >> 8));
    bits = (M16 & bits) + (M16 & (bits >> 16));
    bits = (M32 & bits) + (M32 & (bits >> 32));
    
    return (int)bits;
}

/* This function return the number of the off bits */
size_t BArrCountOff(bitsarr_t bits)
{
    return (WORD_IN_BITS - BArrCountOn(bits));
}

/* This function sets specific bit to the given status */
size_t BArrSetBit(bitsarr_t bits, int position, int status)
{
    
    if (0 == status)
    {
        bits &= ~(LSB << (position - 1));
    }
    else
    {
        bits |= (LSB << (position - 1));
    }
    
    return bits;
}

/* This function sets specific bit to 1 */
size_t BArrSetOn(bitsarr_t bits, int position)
{
    
    bits |= (LSB << (position - 1));
    
    return bits;
}

/* This function sets specific bit to 0 */
size_t BArrSetOff(bitsarr_t bits, int position)
{
    
    bits &= ~(LSB << (position - 1));
    
    return bits;
}

/* This function rotate the array to left n times */
size_t BArrRotateLeft(bitsarr_t bits, int num_of_rotations)
{
    int i = 0;
    
    for(i = 0; i < (num_of_rotations % WORD_IN_BITS); ++i)
    {
        bits = (bits << 1) | ((bits & MSB) >> (WORD_IN_BITS - 1));
    }
    
    return bits;
}

/* This function rotate the array to right n times */
size_t BArrRotateRight(bitsarr_t bits, int num_of_rotations)
{
    int i = 0;
    
    for(i = 0; i < (num_of_rotations % WORD_IN_BITS); ++i)
    {
        bits = (bits >> 1) | ((bits & LSB) << (WORD_IN_BITS - 1));
    }
    
    return bits;
}

/* This function return a string presentation of given bits array */
char* BArrToString(size_t bits, char* str)
{
	int i = 0;
	char* buffer = str;
    assert(NULL != buffer);

    bits = BArrMirror(bits);

    for (;i < WORD_IN_BITS;++i)
    {
    	*buffer = (bits & 1) + 48;
    	bits >>= 1;
    	++buffer;
    }
    *buffer = '\0';

    return str;
}

/* This function flips specific bit */
size_t BArrFlipBit(bitsarr_t bits, int position)
{
    bits ^= (LSB << (position - 1));
    
    return bits;
}

/* This function mirroring a given bits array */
size_t BArrMirror(bitsarr_t bits)
{
    int i = 0;
    size_t mirror = 0;
    
    for(i = 0;i < 63;++i)
    {
        mirror |= bits & LSB;
        mirror <<= 1;
        bits >>= 1; 
    }
    mirror |= bits & LSB;

    return mirror;
}















