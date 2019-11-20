#ifndef _WS8EX1_H_
#define _WS8EX1_H_ 

#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define SIZEOFSTR 16
#define UNUSED(x) (void)(x)


typedef enum State {Succ,
					FAILED_TO_OPEN_FILE,
					Failed_to_Delete,
 					Failed_to_DelRename,
 					FAILED_TO_OPEN_CPYFILE,
 					EXIT
 					} State;




#endif