/********************************/
/*	Yoav Hattav                 */
/*	24.11.19                    */
/*	MyMems                      */
/*                              */
/*	Reviewer: Ben               */
/********************************/
#include "Mymems.h"

int main()
{
	int c = '$';
	char str1[43] = "Hello! my name is rickkkk";
	char str1cpy[43] = "Hello! my name is rickkkk";
	char str2[43] = "Hello! my name is morty";
	const char str_to_str2[43] = "i am being copied to str2";
	char str2cpy[43] = "Hello! my name is morty";
	char str3[43] = "Hello! my name is PickleRick";
	const char str_to_str3[43] = "i am being moved to str3";
	char str3cpy[43] = "Hello! my name is PickleRick";
	size_t number_to_set = 15;
	size_t number_to_cpy = 15;
	size_t number_to_move = 15;

	/* memset test */
	printf("%s\n", str1);
	printf("%s\n", (char *)memset(str1, c, number_to_set));
	strcpy(str1, str1cpy);
	printf("%s\n", (char *)Mymemset(str1, c, number_to_set));


	/* memcpy test */
	printf("%s\n", str2);
	printf("%s\n", (char *)memcpy(str2, str_to_str2, number_to_cpy));
	strcpy(str2, str2cpy);
	printf("%s\n", (char *)Mymemcpy(str2, str_to_str2, number_to_cpy));

	/* memmove test */
	printf("%s\n", str3);
	printf("%s\n", (char *)memmove(str3, str_to_str3, number_to_move));
	strcpy(str3, str3cpy);
	printf("%s\n", (char *)MyMovePlaner(str3, str_to_str3, number_to_move));

	return 0;
}
