#ifndef __IP_H__
#define __IP_H__

#include <stddef.h> /*size_t*/

#define ADDRESS_SIZE_IN_BYTES 4

typedef struct IP
{
	unsigned char address[ADDRESS_SIZE_IN_BYTES];
} ip_t;

void CharIntoBinary(char *address_to_be, unsigned char chr);

void Ip_tToStr(char *address_to_be, ip_t user_address);

unsigned char BinaryIntoChar(char *address_to_be);

void StrToIp_t(char *address, ip_t user_address);

#endif

