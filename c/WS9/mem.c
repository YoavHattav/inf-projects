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

void Mymemset(void* str, int ch, size_t num)
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

int main()
{
	int c = '$';
	char str1[43] = "Hello! my name is yoavhehehehehehehehehehe";
	char str2[43] = "Hello! my name is yoavhehehehehehehehehehe";
	size_t number_of_added = 32;
	printf("%s\n", str1);
	memset(str1+1, c, number_of_added);
	printf("%s\n", str1);
	Mymemset(str2+1, c, number_of_added);
	printf("%s\n", str2);

	return 0;
}
