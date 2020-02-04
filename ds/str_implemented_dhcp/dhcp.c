/*********************************/
/*   DHCP                        */
/*   Yoav Hattav                 */
/*   Last Updated 30/01/20       */
/*   Reviewed by:          */
/*********************************/

#include <stdio.h>  /* sizeof */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <math.h>   /* pow */

#include "../include/trie.h" /* API */
#include "../include/dhcp.h"
#include "../include/ip.h"

#define SIZE_OF_IP_STR 33
#define SIZE_OF_IP 32
#define BINARY_OPTIONS 2
#define ONE 1
#define ZERO 0

struct DHCP
{
	trie_t *trie;
	ip_t subnet_mask;
	size_t available_bits;
};

static alc_status_t AllocateProtectedAddresses(dhcp_t *dhcp)
{
	char *str_address = malloc(sizeof(dhcp->available_bits + 1));

	SetbitsInStr(str_address, ZERO);
	*(str_address + dhcp->available_bits + 1) = '\0';
	if(!TrieInsert(dhcp->trie, str_address))
	{
		free(str_address); str_address = NULL;
		return FAIL_TO_ALLOC;
	}

	SetbitsInStr(str_address, ONE);
	*(str_address + dhcp->available_bits + 1) = '\0';
	if(!TrieInsert(dhcp->trie, str_address))
	{
		free(str_address); str_address = NULL;
		return FAIL_TO_ALLOC;
	}

	SetbitsInStr(str_address, ONE);
	*(str_address + dhcp->available_bits) = '0';
	if(!TrieInsert(dhcp->trie, str_address))
	{
		free(str_address); str_address = NULL;
		return FAIL_TO_ALLOC;
	}

	free(str_address); str_address = NULL;

	return AS_REQUESTED;
}

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
	dhcp_t *new_dhcp = malloc(sizeof(*new_dhcp));
	if (NULL != new_dhcp)
	{	
		return NULL;
	}

	new_dhcp->trie = TrieCreate();
	if (NULL == new_dhcp->trie)
	{
		free(new_dhcp);new_dhcp = NULL;
	}

	new_dhcp->subnet_mask = subnet_mask;
	new_dhcp->available_bits = SIZE_OF_IP - subnet_mask_reserved_bits;

	if (AS_REQUESTED != AllocateProtectedAddresses(new_dhcp))
	{
		DhcpDetroy(new_dhcp);
	}

	return new_dhcp;
}
                  
void DhcpDetroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	TrieDestroy(dhcp->trie);
	free(dhcp); dhcp = NULL;
}

alc_status_t Alternative_allocation(dhcp_t *dhcp, char *requested_address, ip_t allocated_ip)
{
	char *start_itr = NULL;

	char *alternative_address = malloc(sizeof(SIZE_OF_IP_STR));
	if (NULL == alternative_address)
	{
		return FAIL_TO_ALLOC;
	}

	start_itr = alternative_address;

	memcpy(alternative_address, requested_address, SIZE_OF_IP_STR);
	alternative_address = alternative_address + (SIZE_OF_IP_STR - (dhcp->available_bits + 1));
	TrieFirstAvailable(dhcp->trie, alternative_address);

	if(!TrieInsert(dhcp->trie, alternative_address))
	{
		free(start_itr); alternative_address = NULL;start_itr = NULL;

		return FAIL_TO_ALLOC;
	}

	StrToIp_t(alternative_address, allocated_ip);

	free(start_itr); alternative_address = NULL;

	return NOT_AS_REQUESTED;
}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{
	char *start_itr = NULL;

	char *str_address = malloc(sizeof(SIZE_OF_IP_STR));
	if (NULL == str_address)
	{
		return FAIL_TO_ALLOC;
	}
	Ip_tToStr(str_address, requested_ip);

	start_itr = str_address;
	str_address = str_address + (SIZE_OF_IP_STR - (dhcp->available_bits + 1));

	if (TAKEN == TrieIsAvailable(dhcp->trie, str_address))
	{
		alc_status_t return_value_alternate_alloc = NOT_AS_REQUESTED;
		return_value_alternate_alloc =  Alternative_allocation(dhcp, str_address, allocated_ip);
		
		free(start_itr); str_address = NULL;start_itr = NULL;

		return return_value_alternate_alloc;
	}

	else if(!TrieInsert(dhcp->trie, str_address))
	{
		free(start_itr); str_address = NULL;start_itr = NULL;
		return FAIL_TO_ALLOC;
	}

	StrToIp_t(start_itr, allocated_ip);

	free(start_itr); str_address = NULL;start_itr = NULL;

	return AS_REQUESTED;
}

static free_status_t AddressProtector(char *user_add)
{
	size_t len = strlen(user_add);
	char *protected_one = alloca(sizeof(len));
	char *protected_two = alloca(sizeof(len));
	char *protected_three = alloca(sizeof(len));

	SetbitsInStr(protected_one, ZERO);
	SetbitsInStr(protected_two, ONE);
	SetbitsInStr(protected_three, ONE);
	*(protected_three + len -1) = '0';

	if ((0 == strcmp(user_add, protected_one)) || (0 == strcmp(user_add, protected_two)) || (0 == strcmp(user_add, protected_three)))
	{
		return INVALID_ADDRESS;
	}

	return SUCCESS;
}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{
	char *str_address = malloc(sizeof(SIZE_OF_IP_STR));
	Ip_tToStr(str_address, dhcp->subnet_mask);

	str_address = str_address + (SIZE_OF_IP_STR - (dhcp->available_bits + 1));

	if (SUCCESS != AddressProtector(str_address))
	{
		return INVALID_ADDRESS;
	}
	TrieFreeLeaf(dhcp->trie, str_address);

	free(str_address); str_address = NULL;
	
	return SUCCESS;
}

size_t DhcpCountFree(const dhcp_t *dhcp)
{
	size_t taken_count = 0;

	assert(NULL != dhcp);

	taken_count = TrieCountLeafs(dhcp->trie);

	return (pow(BINARY_OPTIONS, dhcp->available_bits) - taken_count);
}

