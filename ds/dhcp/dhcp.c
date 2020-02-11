/*********************************/
/*   DHCP                        */
/*   Yoav Hattav                 */
/*   Last Updated 30/01/20       */
/*   Reviewed by: Guy Cohen-Zedek*/
/*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <math.h>   /* pow */

#include "trie.h" /* tire API functions */
#include "dhcp.h" /* API */

#define BINARY_OPTIONS 2
#define SIZE_OF_IP 32
#define BYTES_IN_IP 4
#define BITS_IN_BYTE 8
#define MASK_MAX 0xff
#define MASK_PREMAX 0xfe
#define LSB 0x1

struct DHCP
{
	trie_t *trie;
	ip_t subnet_mask;
	size_t available_bits;
};

/***************************************************************************
							STATIC FUNCTIONS
***************************************************************************/

static alc_status_t AllocateProtectedAddressesIMP(dhcp_t *dhcp);
static alc_status_t Alternative_allocationIMP(dhcp_t *dhcp, ip_t allocated_ip);
static free_status_t AddressProtector(dhcp_t *dhcp, ip_t user_add);
static status_t CheckRequestedIMP(dhcp_t *dhcp, ip_t requested_ip);

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
		return NULL;
	}

	memcpy(new_dhcp->subnet_mask, subnet_mask, BYTES_IN_IP);

	new_dhcp->available_bits = SIZE_OF_IP - subnet_mask_reserved_bits;

	if (AS_REQUESTED != AllocateProtectedAddressesIMP(new_dhcp))
	{
		DhcpDestroy(new_dhcp);
		new_dhcp = NULL;
	}

	return new_dhcp;
}
                  
void DhcpDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	TrieDestroy(dhcp->trie);
	dhcp->trie = NULL;
	free(dhcp); dhcp = NULL;
}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{
	assert(NULL != dhcp);

	if (0 == DhcpCountFree(dhcp))
	{
		return FAIL_TO_ALLOC;
	}

	memcpy(allocated_ip, requested_ip, BYTES_IN_IP);

	if (TAKEN == TrieIsAvailable(dhcp->trie, requested_ip))
	{	
		return Alternative_allocationIMP(dhcp, allocated_ip);
	}

	else if(TrieInsert(dhcp->trie, requested_ip))
	{
		return FAIL_TO_ALLOC;
	}

	return AS_REQUESTED;
}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{
	assert(NULL != dhcp);

	if (SUCCESS != AddressProtector(dhcp, ip_address))
	{
		return INVALID_ADDRESS;
	}

	if (CheckRequestedIMP(dhcp, ip_address))
	{
		return ADDRESS_NOT_FOUND;
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
							STATIC FUNCTIONS
***************************************************************************/

static alc_status_t Alternative_allocationIMP(dhcp_t *dhcp, ip_t allocated_ip)
{
	assert(NULL != dhcp);
	
	TrieNextAvailable(dhcp->trie, allocated_ip);

	if(TrieInsert(dhcp->trie, allocated_ip))
	{
		return FAIL_TO_ALLOC;
	}

	return NOT_AS_REQUESTED;
}

static void FirstAddress(ip_t first_ad, size_t available_bits)
{
	size_t num_of_avilable = available_bits;
	for (; available_bits > 0; --available_bits)
	{
		*(first_ad + (SIZE_OF_IP - num_of_avilable) / BITS_IN_BYTE) &=
                 ~(LSB << ((available_bits - 1) % BITS_IN_BYTE));
	}
}

static void LastAddress(ip_t last_ad, size_t available_bits)
{
	size_t num_of_avilable = available_bits;
	int i = 0;

	for (i = ((SIZE_OF_IP - num_of_avilable)/BITS_IN_BYTE);i < BYTES_IN_IP;++i)
	{
		*(last_ad + i) |= (MASK_MAX >> (available_bits % BITS_IN_BYTE));
		if (0 == (available_bits % BITS_IN_BYTE))
		{
			available_bits -= BITS_IN_BYTE;
		}
		else
		{
			available_bits -= (available_bits % BITS_IN_BYTE);
		}
	}
}

static void PreLastAdress(ip_t prelast_ad, size_t available_bits)
{
	LastAddress(prelast_ad, available_bits);

	*(prelast_ad + (BYTES_IN_IP -1)) &= MASK_PREMAX;
}

static free_status_t AddressProtector(dhcp_t *dhcp, ip_t user_add)
{
	ip_t first_ad = {0}; 
	ip_t last_ad = {0}; 
	ip_t prelast_ad = {0}; 

	memcpy(first_ad, dhcp->subnet_mask, BYTES_IN_IP);
	memcpy(last_ad, dhcp->subnet_mask, BYTES_IN_IP);
	memcpy(prelast_ad, dhcp->subnet_mask, BYTES_IN_IP);

	FirstAddress(first_ad, dhcp->available_bits);
	LastAddress(last_ad, dhcp->available_bits);
	PreLastAdress(prelast_ad, dhcp->available_bits);

	if ((0 == memcmp(user_add, first_ad, BYTES_IN_IP)) ||
	 	(0 == memcmp(user_add, last_ad, BYTES_IN_IP)) || 
	 	(0 == memcmp(user_add, prelast_ad, BYTES_IN_IP)))
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

static status_t CheckRequestedIMP(dhcp_t *dhcp, ip_t requested_ip)
{
    ip_t requested = {0};
    size_t height = 0;
    size_t shift_holder = 0;
   
    height = dhcp->available_bits;
    memcpy(requested, requested_ip, ADDRESS_SIZE_IN_BYTES);
   
    while (0 < height)
    {
        shift_holder = height % BITS_IN_BYTE;
        if (0 == shift_holder)
        {
            *(requested + (SIZE_OF_IP - height) / BITS_IN_BYTE) &= 0;
            height -= BITS_IN_BYTE;    
        }
        else
        {
            *(requested + (SIZE_OF_IP - height) / BITS_IN_BYTE) =
           (*(requested + (SIZE_OF_IP - height) / BITS_IN_BYTE) >> shift_holder)
            << shift_holder;
            height -= shift_holder;
        }      
    }

    return !(0 == memcmp(requested, dhcp->subnet_mask, ADDRESS_SIZE_IN_BYTES));
}