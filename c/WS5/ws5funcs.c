/********************************/
/*	Yoav Hattav			        */
/*	13.11.19		        	*/
/*	Files and strings       	*/
/*								*/
/*	Reviewer: Raz the slayer	*/
/********************************/

#include <string.h>
#include <stdio.h>
#include "ws5funcs.h"
#include <assert.h>

/* the function counts the lines in the file */
enum State LCounter(const char *filename, const char *s)
{
	
	FILE *fp;
	int counter=0;
	char ch;

	UNUSED(s);

	fp=fopen(filename, "r");

	if (NULL == fp)
	{
		printf("cant open file: %s\n", filename);
		return FAILED_TO_OPEN_FILE;
	}

	for ( ch=getc(fp); ch != EOF; ch = getc(fp))
	{
		if ('\n' == ch)
		{
			counter += 1;
		}
	}

	fclose(fp);
	printf("Flie %s has %d lines\n", filename, counter);

	return GJ;
}

/*  the function deletes the txt file. */
enum State Delete(const char *filename, const char *s)
{
	UNUSED(s);
	if (0 == remove(filename))
	{
		printf("file has been removed\n");
		return GJ;
	}
	else
	{
		printf("file could not be removed!!\n");
		return Failed_to_Delete;
	}
}

/* the function adds a string to the end of the file */
enum State AddNormal(const char *filename, const char *s)
{
	FILE* fp = fopen(filename, "a+");

	if ( NULL == fp)
	{
		printf("couldnt open the file\n");
		return FAILED_TO_OPEN_FILE;
	}

	fputs(s, fp);
	fclose(fp);

	return GJ; 
}

/* the function adds a string to the start of the file
by copying the file's content to a new one  */
enum State AddToTop(const char *filename, const char *s)
{
	char ch = 0;
	const char *srun = s+1;
	int res = 0;
	
	FILE* fpcpy = fopen("Add2topTempcpy.txt", "w+");
	FILE* fp = fopen(filename, "a+");

	assert(NULL != s);
	assert(NULL != filename);

	
	if ( NULL == fpcpy ) 
    { 
        return FAILED_TO_OPEN_CPYFILE;
    } 

	if ( NULL == fp ) 
    { 
        return FAILED_TO_OPEN_FILE;
    } 
	
	while ('\0' != *srun)
	{
		ch = *srun;
		fputc(ch, fpcpy);
		++srun;
 	}

    ch = fgetc(fp); 
    while (ch != EOF) 
    { 
        fputc( ch, fpcpy ); 
        ch = fgetc(fp); 
    }

    fclose(fp); 
    fclose(fpcpy); 

    Delete(filename,s);
  	res = rename("Add2topTempcpy.txt", filename);

  	if(0 == res)
  	{
  		return GJ;
  	}
  	else
  	{
  		return Failed_to_DelRename;
  	} 
}

/* the function exits the program. */
enum State Exit(const char *filename, const char *s)
{
	UNUSED(s);
	UNUSED(filename);

	printf("Exiting program..\n");
	return EXIT;
}

/* the function gets 2 strings and compers them */
int Mystrcmp(const char *str, const char *instr)
{
	int result=0;
	const char *strcase = str;
	const char *s = instr;

	assert(NULL != str);
	assert(NULL != instr);

	while( ('\0' != *strcase  ||  '\0' != *s) && ('\0' != *strcase))
	{
		if(*strcase != *s)
		{
			result = (*strcase - *s);
			break;
		}
		++strcase;
		++s;
	}

	if ( 0 == result)
	{
		return 0;
	}
	return 1;
}

/* the function gets a string and a char and checks
 whether the char is in the start of the string */
int Mychrcmp(const char *instr, const char *check)
{
    assert(NULL != instr);
    assert(NULL != check);

    if ( *check == *instr)
    {
    	return 0;
    }
    return 1;
}

/* an empty function for the use off addint without interference */
int EmptyFun(const char *str, const char *s)
{
	
	assert(NULL != str);
	assert(NULL != s);

	return 0;
}

/* a function used to init the structure-array */
void initiate(chain op[])
{

op[0].s = "-exit";
op[0].pcmp = &Mystrcmp;
op[0].pop = &Exit;

op[1].s = "-remove";
op[1].pcmp = &Mystrcmp;
op[1].pop = &Delete;

op[2].s = "-count";
op[2].pcmp = &Mystrcmp;
op[2].pop = &LCounter;

op[3].s = "<";
op[3].pcmp = &Mychrcmp;
op[3].pop = &AddToTop;

op[4].s = "adding anything after other blocks..";
op[4].pcmp = &EmptyFun;
op[4].pop = &AddNormal;

}
/* the brain of the algorithm */
void Infrastructure(const char *filename, chain op[])
{
	int i = 0;
	int status = 0;
	char strin[MAX];

	do 
	{
		printf("Pls enter a string.\n");
		fgets(strin, MAX, stdin);

		for ( i = 0 ; i < 5 ; i++ )
		{
			if(0 == op[i].pcmp(op[i].s,strin))
			{
				status = op[i].pop(filename,strin);
				break;
			}
		}
	}while (status == GJ );

}