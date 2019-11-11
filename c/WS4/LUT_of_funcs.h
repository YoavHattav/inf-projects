#ifndef _LUTOFFUNCS_H
#define _LUTOFFUNCS_H
#include <stddef.h>

int InWalid(char c);
int PrintIt(char ch);
int Terminate(char c);
int USELUT(int (*LUT[])(char));
int CreatLUT(int (*LUT[])(char));

#endif
