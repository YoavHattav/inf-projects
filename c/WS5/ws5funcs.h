/********************************/
/*	Yoav Hattav			        */
/*	13.11.19		        	*/
/*	Files and strings       	*/
/*								*/
/*	Reviewer: Raz the slayer	*/
/********************************/


#ifndef _WS5FUNCS_H
#define _WS5FUNCS_H 

#include <stdio.h>
#include <stdlib.h>

#define MAX 150
#define UNUSED(s) (void)(s)


typedef enum State {GJ, FAILED_TO_OPEN_FILE, Failed_to_Delete,
 Failed_to_DelRename, FAILED_TO_OPEN_CPYFILE, EXIT} State;


typedef struct  chain
{
	char *s;
	int (*pcmp)(const char *str, const char *s);
	State (*pop)(const char *filename, const char *s);

}chain;

/*operational functions: */
enum State LCounter(const char *filename, const char *s);
enum State Delete(const char *filename, const char *s);
enum State AddNormal(const char *filename, const char *s);
enum State AddToTop(const char *filename, const char *s);
enum State Exit(const char *filename, const char *s);

/* cmp functions */
int Mystrcmp(const char *str, const char *instr);
int Mychrcmp(const char *instr, const char *check);
int EmptyFun(const char *str, const char *s);

/* initiation funcs */
void initiate(chain op[]);
void Infrastructure(const char *filename, chain op[]);

#endif
