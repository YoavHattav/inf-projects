#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ip.h"

#define BITS_IN_BYTE 8
#define BITS_IN_WORD 32

void CharIntoBinary(char *address_to_be, unsigned char chr)
{
    int i = BITS_IN_BYTE - 1;
    char *runner = address_to_be;

    for (; i >= 0; --i)
    {
        *(runner + i) = chr % 2 + 48;
        chr /= 2;
    }
}

void Ip_tToStr(char *address_to_be, ip_t user_address)
{
    char *runner = address_to_be;
    int i = 0;

    for (i = 0; i < 4; ++i)
    {
        CharIntoBinary(runner, user_address.address[i]);
        runner = runner + BITS_IN_BYTE;
    }
    *(address_to_be + BITS_IN_WORD) = '\0';
}



unsigned char BinaryIntoChar(char *address_to_be)
{
    int result = 0;
    unsigned char return_val = 0;
    char *runner = address_to_be;
    int i = 0;

    for (; i < 8; ++i)
    {
        if ('1' == *runner)
        {
            result += (char)pow(2, i);  
        }
        --runner;
    }
    return_val = result;

    return return_val;
}

void StrToIp_t(char *address, ip_t user_address)
{
    int i  = 4;
    for (;i > 0; --i)
    {
        user_address.address[i - 1] = BinaryIntoChar(address + (i*BITS_IN_BYTE));
    }
}