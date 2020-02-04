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

static alc_status_t AllocateProtectedAddressesIMP(dhcp_t *dhcp);

static alc_status_t Alternative_allocationIMP(dhcp_t *dhcp, ip_t allocated_ip);

static free_status_t AddressProtector(dhcp_t *dhcp, ip_t user_add);

/***************************************************************************
							API FUNCTIONS
***************************************************************************/

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
	dhcp_t *new_dhcp = malloc(sizeof(*new_dhcp));
	if (NULL == new_dhcp)
	{	
		return NULL;
	}

	new_dhcp->trie = TrieCreate(SIZE_OF_IP - subnet_mask_reserved_bits);
	if (NULL == new_dhcp->trie)
	{
		free(new_dhcp);new_dhcp = NULL;
	}

	new_dhcp->subnet_mask[0] = subnet_mask[0];
	new_dhcp->subnet_mask[1] = subnet_mask[1];
	new_dhcp->subnet_mask[2] = subnet_mask[2];
	new_dhcp->subnet_mask[3] = subnet_mask[3];

	new_dhcp->available_bits = SIZE_OF_IP - subnet_mask_reserved_bits;

	if (AS_REQUESTED != AllocateProtectedAddressesIMP(new_dhcp))
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

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{
	if (TAKEN == TrieIsAvailable(dhcp->trie, requested_ip))
	{	
		memcpy(allocated_ip, requested_ip, 4);
		return Alternative_allocationIMP(dhcp, allocated_ip);
	}

	else if(!TrieInsert(dhcp->trie, requested_ip))
	{
		return FAIL_TO_ALLOC;
	}

	return AS_REQUESTED;
}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{
	if (SUCCESS != AddressProtector(dhcp, ip_address))
	{
		return INVALID_ADDRESS;
	}
	TrieFreeLeaf(dhcp->trie, ip_address);

	return SUCCESS;
}

size_t DhcpCountFree(const dhcp_t *dhcp)
{
	size_t taken_count = 0;

	assert(NULL != dhcp);

	taken_count = TrieCountOccupiedLeafs(dhcp->trie);

	return (pow(BINARY_OPTIONS, dhcp->available_bits) - taken_count);
}

/***************************************************************************
							IMP FUNCTIONS
***************************************************************************/

static alc_status_t Alternative_allocationIMP(dhcp_t *dhcp, ip_t allocated_ip)
{
	TrieNextAvailable(dhcp->trie, allocated_ip);

	if(!TrieInsert(dhcp->trie, allocated_ip))
	{
		return FAIL_TO_ALLOC;
	}

	return NOT_AS_REQUESTED;
}

static free_status_t AddressProtector(dhcp_t *dhcp, ip_t user_add)
{
	unsigned char ip0000[4] = {0, 0, 0, 0};
	unsigned char ip1111[4] = {255, 255, 255, 255};
	unsigned char ip1110[4] = {255, 255, 255, 254};

	if ((0 == memcmp(user_add, ip0000, 4)) || (0 == memcmp(user_add, ip1111, 4)) || (0 == memcmp(user_add, ip1110, 4)))
	{
		return INVALID_ADDRESS;
	}

	return SUCCESS;
}

static alc_status_t AllocateProtectedAddressesIMP(dhcp_t *dhcp)
{
	unsigned char ip0000[4] = {0, 0, 0, 0};
	unsigned char ip1111[4] = {255, 255, 255, 255};
	unsigned char ip1110[4] = {255, 255, 255, 254};

	if(SUCC != TrieInsert(dhcp->trie, ip0000))
	{
		return FAIL_TO_ALLOC;
	}

	if(SUCC != TrieInsert(dhcp->trie, ip1111))
	{
		return FAIL_TO_ALLOC;
	}

	if(SUCC != TrieInsert(dhcp->trie, ip1110))
	{
		return FAIL_TO_ALLOC;
	}

	return AS_REQUESTED;
}