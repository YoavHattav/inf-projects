/********************************/
/*	Yoav Hattav                 */
/*	13.11.19                    */
/*	Files and strings           */
/*                              */
/*	Reviewer: Ben               */
/********************************/
#ifndef _MYMEMS_
#define _MYMEMS_ 

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define WORD_SIZE 8

size_t ByWord(int c);
void *Mymemcpy(void *str1, const void *str2, size_t num);
void *Mymemset(void* str, int ch, size_t num);
void *MoveReverse(void *dest, const void *src, size_t num);
void *MyMovePlaner(void *dest, const void *source, size_t n);
void Test(int cond, const char *massage);



#endif