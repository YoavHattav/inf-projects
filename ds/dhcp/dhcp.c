/*********************************/
/*   DHCP                        */
/*   Yoav Hattav                 */
/*   Last Updated 30/01/20       */
/*   Reviewed by:          */
/*********************************/

#include <stdio.h>  /* sizeof */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/trie.h" /* API */
#include "../include/dhcp.h"

struct DHCP
{
	trie_t *trie;
	ip_t subnet_mask;
	size_t available_bits;
};

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
	dhcp_t *new_dhcp = NULL;

	
}
                  
void DhcpDetroy(dhcp_t *dhcp)
{

}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{

}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{

}

size_t DhcpCountFree(const dhcp_t *dhcp)
{

}

