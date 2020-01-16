#ifndef __RECU_H__
#define __RECU_H__

#define UNUSED(x) (void)(x)

size_t FibIter(size_t n);

size_t FibRec(size_t n);

size_t StrlenRec(char *str);

int StrcmpRec(const char *str1, const char *str2);

char *StrcpyRec(char *str1, const char *str2);

char *StrcatRec(char *dest, const char *src);

char *StrstrRec(char *haystack, char *needle);



#endif
