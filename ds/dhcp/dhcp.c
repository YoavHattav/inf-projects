/*********************************/
/*   BST                         */
/*   Yoav Hattav                 */
/*   Last Updated 09/01/20       */
/*   Reviewed by: Israel         */
/*********************************/

#include <stdio.h>  /* sizeof */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/trie.h" /* API */
#include "../include/dhcp.h"
     
dhcp_t *DhcpCreate(ipt_t subnet_mask, size_t subnet_mask_reserved_bits)
{

}
                  
void DhcpDetroy(dhct_t *dhcp)
{

}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ipt_t requested_ip, ip_t allocated_ip)
{

}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{

}

size_t DhcpCountFree(const dhcp_t *dhcp)
{

}

