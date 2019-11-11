#include <stdio.h>
#include <stdlib.h>

/********************************/
/*	Yoav Hattav			        */
/*	11.11.19		        	*/
/*	LUT of Fun       			*/
/*								*/
/*	Reviewer: Shye The Presser	*/
/********************************/


int main()
{
	int (*LUT[256])(char);

	CreatLUT(LUT);
	USELUT(LUT);

	return 0;
}