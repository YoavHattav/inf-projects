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
#include "bitsarray.h"

#define GREEN "\033[0;32m"
#define RED "\033[1;31m"
#define WHITE "\033[0m"
#define ALLSET 18446744073709551615UL
#define STRING1 "0000000000000000000000000000000000000000000000000000000000100010" /* 34 */
#define STRING2 "0000000000000000000000000000000000000000000000000001000010010010" /* 4242 */
#define STRING3 "0000000000000000000000000000000000000000000000000001101010000101" /* 6789 */
#define STRING4 "0110101010101000000000000000000000000000000000000101010101010101" /* 7685392764107773269 */
#define BIGNUM 7685392764107773269UL /* 7685392764107773269 */

#define TEST(Test, msg) if (Test)\
                        {\
                            printf(GREEN);\
                            printf("SUCCESS\n");\
                        }\
                        else\
                        {\
                            printf(RED);\
                            printf("FAIL-%s\n", msg);\
                        }\
                        printf(WHITE);

static int TestBArrSetAllBits()
{
    printf("test for BArrSetAllBits \n");
    TEST(BArrSetAllBits(0) == ALLSET, "simple true");
    TEST(BArrSetAllBits(1) == ALLSET, "simple true");
    TEST(BArrSetAllBits(2) == ALLSET, "simple true");
    TEST(BArrSetAllBits(19) == ALLSET, "simple true");
    TEST(BArrSetAllBits(895) == ALLSET, "simple true");

    return 0;
}

static int TestBArrResetAllBits()
{
    printf("\ntest fo BArrResetAllBits \n");
    TEST(BArrResetAllBits(1) == 0 , "simple true");
    TEST(BArrResetAllBits(10) == 0 , "simple true");
    TEST(BArrResetAllBits(100) == 0 , "simple true");
    TEST(BArrResetAllBits(111111) == 0 , "simple true");
    TEST(BArrResetAllBits(0) == 0 , "simple true");

    return 0;
}

static int TestBArrIsOn()
{
    printf("\ntest for BArrIsOn \n");
    TEST(BArrIsOn(12, 4) == 1 , "12 bit 4");
    TEST(BArrIsOn(34, 2) == 1 , "34 bit 2");
    TEST(BArrIsOn(1048576, 21) == 1 , "1048576 bit 21");
    TEST(BArrIsOn(1048576, 20) != 1 , "1048576 bit 20");
    TEST(BArrIsOn(8200, 4) == 1 , "bit");

    return 0;
}

static int TestBArrIsOff()
{
    printf("\ntest for BArrIsOff \n");
    TEST(BArrIsOff(12, 2) == 1 , "12 bit 2");
    TEST(BArrIsOff(12, 4) != 1 , "12 bit 4");
    TEST(BArrIsOff(12, 25) == 1 , "12 bit 25");
    TEST(BArrIsOff(12, 33) == 1 , "12 bit 33");
    TEST(BArrIsOff(12, 0) == 1 , "position 0");


    return 0;
}

static int TestBArrCountOn()
{
    printf("\ntest for BArrCountOn \n");
    TEST(BArrCountOn(7) == 3 , "7-3");
    TEST(BArrCountOn(534287) == 9 , "534,287-9");
    TEST(BArrCountOn(30591) == 13 , "30,591-13");
    TEST(BArrCountOn(1799) == 6 , "1799-6");
    TEST(BArrCountOn(5911) == 8 , "5911-8");

    return 0;
}

static int TestBArrSetBit()
{
    printf("\ntest for BArrSetBit \n");
    TEST(BArrSetBit(4, 1, 1) == 5 , "4, 1, 1 == 5");
    TEST(BArrSetBit(4, 3, 0) == 0 , "4, 3, 0 == 0");
    TEST(BArrSetBit(8, 4, 0) == 0 , "8, 4, 0 == 0");
    TEST(BArrSetBit(8, 1, 1) == 9 , "8, 1, 1 == 9");
    TEST(BArrSetBit(5911, 12, 1) == 7959 , "5911, 12, 1 == 7959");

    return 0;
}

static int TestBArrSetOn()
{
    printf("\ntest for BArrSetOn \n");
    TEST(BArrSetOn(0, 11) == 1024 , "simple true");
    TEST(BArrSetOn(0, 10) == 512 , "simple true");
    TEST(BArrSetOn(5, 11) == 1029 , "simple true");
    TEST(BArrSetOn(1024, 11) == 1024 , "simple true");
    TEST(BArrSetOn(53, 7) == 117 , "simple true");


    return 0;
}

static int TestBArrSetOff()
{
    printf("\ntest for BArrSetOff \n");
    TEST(BArrSetOff(1024, 11) == 0 , "simple true");
    TEST(BArrSetOff(1024, 1) == 1024 , "simple true");
    TEST(BArrSetOff(1024, 1) != 0 , "simple true");
    TEST(BArrSetOff(8, 4) == 0 , "simple true");
    TEST(BArrSetOff(ALLSET, 1) == ALLSET-1 , "simple true");

    return 0;
}

static int TestBArrRotateLeft()
{
    printf("\ntest for BArrRotateLeft \n");
    TEST(BArrRotateLeft(1, 65) == 2 , "simple true");
    TEST(BArrRotateLeft(1, 66) == 4 , "simple true");
    TEST(BArrRotateLeft(1, 67) == 8 , "simple true");
    TEST(BArrRotateLeft(1, 68) == 16 , "simple true");


    return 0;
}

static int TestBArrRotateRight()
{
    printf("test for BArrRotateRight \n");
    TEST(BArrRotateRight(1, 63) == 2 , "simple true");
    TEST(BArrRotateRight(1, 3) == (1UL<<61) , "simple true");
    TEST(BArrRotateRight(1, 0) == 1 , "simple true");
    TEST(BArrRotateRight(4, 2) == 1 , "simple true");

    return 0;
}

static int TestBArrToString()
{
    char *buffer = (char*)calloc(65, sizeof(char)); 

    printf("\ntest for BArrToString \n");
    
    TEST(strcmp(BArrToString(34, buffer), STRING1) == 0 , "34 in bits");
    TEST(strcmp(BArrToString(4242, buffer), STRING2) == 0 , "4242 in bits");
    TEST(strcmp(BArrToString(6789, buffer), STRING3) == 0 , "6789 in bits");
    TEST(strcmp(BArrToString(BIGNUM, buffer), STRING4) == 0 , "BIGNUM is bits");
    TEST(strcmp(BArrToString(0, buffer), "hi im erniu") != 0 , "FAIL (hi im erniu)");
    TEST(strcmp(BArrToString(6789, buffer), STRING3) == 0 , "6789 in bits");
    TEST(strcmp(BArrToString(BIGNUM, buffer), STRING4) == 0 , "BIGNUM is bits");
    
    free(buffer);

    return 0;
}

static int TestBArrFlipBit()
{
    printf("\ntest for BArrFlipBit \n");
    TEST(BArrFlipBit(0, 2) == 2 , "simple true");
    TEST(BArrFlipBit(0, 3) == 4 , "simple true");
    TEST(BArrFlipBit(8, 4) == 0 , "simple true");
    TEST(BArrFlipBit(8, 3) == 12 , "simple true");


    return 0;
}

static int TestBArrMirror()
{
    printf("\ntest for BArrMirror \n");
    TEST((BArrMirror(1) == (1UL << 63)), "simple true");
    TEST((BArrMirror(2) == (1UL << 62)), "simple true");
    TEST((BArrMirror(4) == (1UL << 61)), "simple true");
    TEST((BArrMirror(8) == (1UL << 60)), "simple true");
    TEST((BArrMirror(0x8000000000000000) == (1UL)), "simple true");
    TEST((BArrMirror(0x00ff00ff00ff00ff) == (0xff00ff00ff00ff00)), "simple true");


    return 0;
}

int main()
{

    TestBArrSetAllBits();
    TestBArrResetAllBits();
    TestBArrIsOn();
    TestBArrIsOff();
    TestBArrCountOn();
    TestBArrSetBit();
    TestBArrSetOn();
    TestBArrSetOff();
    TestBArrRotateLeft();
    TestBArrRotateRight();
    TestBArrToString();
    TestBArrFlipBit();
    TestBArrMirror();

    return 0; 
}
