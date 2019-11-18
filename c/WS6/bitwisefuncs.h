/********************************/
/*	Yoav Hattav                 */
/*	13.11.19                    */
/*	Files and strings           */
/*                              */
/*	Reviewer: Raz the slayer    */
/********************************/
#ifndef _BITWISEFUNCS_H_
#define _BITWISEFUNCS_H_ 

#include <stdio.h>

#define MAX 10

typedef enum status {FALSE, TRUE} status;

void ShowBits(unsigned int n);
long Pow2(unsigned int x, unsigned int y);
enum status IsItpow2(unsigned n);
enum status IsItpow2p2(unsigned n);
int AddOne(int a);
void ThreeOn(unsigned int *arr);
int HowManySet(int n);
void Swap(unsigned int *a, unsigned int *b);
unsigned int ByteMirror(unsigned int x);
unsigned int Closest(unsigned int x);
unsigned char SwapThirdAndFifth(unsigned char x);
unsigned char BothTwoAndSix(unsigned char x);
unsigned char OneOfTwoAndSix(unsigned char x);
int SetBitCounterNoLoop(unsigned int x);
unsigned int ByteMirrorNoLoop(unsigned int x);
int Float_bit(int a, int loc); 
void Float_print(float a);


#endif