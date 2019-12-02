/********************************/
/*	Yoav Hattav                 */
/*	24.11.19                    */
/*	MyMems                      */
/*                              */
/*	Reviewer: Ben               */
/********************************/
#include "Mymems.h"

size_t ByWord(int c)
{		
	size_t word_size_ch = (char)c;
	unsigned int i = 0;

	for (i=0; i < (sizeof(size_t)-1); ++i)
	{
		word_size_ch <<= WORD_SIZE;
		word_size_ch |= c;
	}


	return word_size_ch;
}


void *Mymemcpy(void *str1, const void *str2, size_t num)
{
	char *dest = (char*)str1;
	const char *src = (char*)str2;

	assert(NULL != str1);
	assert(NULL != str2);

	while ((0 != ((size_t)dest % WORD_SIZE)) && (0 < num))
	{
		*dest = *src;
		++dest;
		++src;
		--num;
	}


	while (sizeof(size_t) <= num)
	{
		*(size_t*)dest = *(size_t*)src;
		num = num - sizeof(size_t);
		dest = dest + sizeof(size_t);
		src = src + sizeof(size_t);
	}

	while (0 < num)
	{
		*dest = *src;
		++dest;
		++src;
		--num;
	}

	return str1;
}


void *Mymemset(void* str, int ch, size_t num)
{
	char *run = (char*)str;
	size_t word = 0;

	assert(NULL != str);

	while ((0 != ((size_t)run % WORD_SIZE)) && (0 < num))
	{
		*run = (char)ch;
		++run;
		--num;
	}

	word = ByWord(ch);

	while (sizeof(size_t) <= num)
	{
		*(size_t*)run = word;
		num = num - sizeof(size_t);
		run = run + sizeof(size_t);
	}

	while (0 != num)
	{
		*run = (char)ch;
		++run;
		--num;
	}

	return str;
}

void *MoveReverse(void *dest, const void *src, size_t num)
{
	char *dest_run = (char*)dest;
	char *src_run = (char*)src;
	dest_run = dest_run + num - 1;
	src_run = src_run + num - 1;

	assert(NULL != dest);
	assert(NULL != src);

	while(0 < num)
        {
            *dest_run = *src_run;
            --dest_run;
            --src_run;
            --num;
        }
        
        return dest;
}


void *MyMovePlaner(void *dest, const void *src, size_t num)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	if ((((char*)dest > (char*)src + num)) || ((char*)dest+strlen(dest) < (char*)src))
	{
		Mymemcpy(dest, src, num);
	}
	else 
	{
		MoveReverse(dest, src, num);
	}

	return dest;
}

void Test(int cond, const char *massage)
{
	if (1 == cond)
	{
		printf("\033[1;32m""SUCC-%s\n", massage);
	}
	else
	{
		printf("\033[0;31m""FAIL-%s\n", massage );
	}
}  




