#include <stdio.h>
#ifndef _mystrs_h
#define _mystrs_h


size_t Mystrlen(const char *str);
int Mystrcmp(const char *str_1, const char *str_2);
void Mystrcpy(char *dest, char *sour);
void Mystrncpy(char *dest, char *sour, int n);
int Mystrcasecmp(const char *a, const char *b);
char *Mystrchr(const char *chrstr, const char check);

#endif
