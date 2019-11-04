#include <stdio.h>
#ifndef _mystrs_h
#define _mystrs_h


size_t Strlenies(const char *str);
int Strcmpies(const char *str_1, const char *str_2);
void Strcpyies(char *dest, char *sour);
void Strncpyies(char *dest, char *sour, int n);
int Strcasecmpies(const char *a, const char *b);
char *strchries(const char *chrstr, const char check);

#endif
