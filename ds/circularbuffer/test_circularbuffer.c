/*********************************/
/*    Data Structures            */
/*    Bits Array                 */
/*    Author :Yoav Hattav        */
/*    Reviewed By:               */
/*    Date:     26/11/2019       */
/*                               */
/*********************************/
#include <stdlib.h> /* calloc usage*/
#include <string.h> /* strcmp usage */
#include <stdio.h>

#include "circularbuffer.h"


#define GREEN "\033[0;32m"
#define RED "\033[1;31m"
#define WHITE "\033[0m"



#define RUN_TEST(Test, msg) if (Test)\
                        {\
                            printf(GREEN);\
                            printf("SUCCESS- %s\n", msg);\
                        }\
                        else\
                        {\
                            printf(RED);\
                            printf("FAIL- %s\n", msg);\
                        }\
                        printf(WHITE);