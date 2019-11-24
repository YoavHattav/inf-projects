#include <stdio.h>
#include <string.h>

#define WORD_SIZE 8

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

/*size_t ByWordCpy(char* dest, char* src)
{		
	size_t word_size_ch = *src;
	unsigned int i = 0;

	for (i=0; i < (sizeof(size_t)-1); ++i)
	{
		word_size_ch <<= WORD_SIZE;
		word_size_ch |= c;
	}


	return word_size_ch;
}*/



void *Mymemcpy(void *str1, const void *str2, size_t num)
{
	char *dest = (char*)str1;
	char *src = (char*)str2;

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
}


void *Mymemset(void* str, int ch, size_t num)
{
	char *run = (char*)str;
	size_t word = 0;

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

int main()
{
	int c = '$';
	char str1[43] = "Hello! my name is yoavhehehehehehehehehehe";
	char str2[43] = "Hello! my name is yoavhehehehehehehehehehe";
	char str3[50] = "sdhgcxfghfcxghfdghfdhg";
	char str4[43] = "Hello! myhehehehehehehehehehe name is yoav";
	char str5[50] = "sdhgcxfghfcxghfdghfdhg";
	char str6[43] = "Hello! myhehehehehehehehehehe name is yoav";
	size_t number_of_added = 32;

	char *ptr1 = str1;
	char *ptr2 = str2;
	
	printf("%d", strcmp(memset(ptr1,c,number_of_added), Mymemset(ptr2,c,number_of_added)));
	/*memset(str1, c, number_of_added);
	printf("%s\n", str1);
	Mymemset(str2,c,number_of_added);
	printf("%s\n", str2);*/
/*
	puts(ptr1);
	puts(ptr2);
	Test(0 == strcmp(memset(ptr1,c,number_of_added), Mymemset(ptr2,c,number_of_added)), "simple true");
	puts(ptr1);
	puts(ptr2);
*/
	/*printf("%s\n", str1);
	Mymemset(str2+1, c, number_of_added);
	printf("%s\n", str2);

	printf("%s\n", str3);
	memcpy(str3, str4, number_of_added);
	printf("%s\n", str3);
	Mymemcpy(str5, str6, number_of_added);
	printf("%s\n", str5);*/

	return 0;
}
