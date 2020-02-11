/*********************************/
/*   TRIE                        */
/*   Yoav Hattav                 */
/*   Last Updated 30/01/20       */
/*   Reviewed by: Guy Cohen-Zedek*/
/*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "trie.h" /* API */

#define LSB 0x01
#define BITS_IN_BYTE 8
#define BITS_IN_IP 32

enum child {LEFT, RIGHT, NUM_OF_CHILDREN};

typedef struct TrieNode trie_node_t;

struct TrieNode
{
	struct TrieNode *direction[NUM_OF_CHILDREN];
	availability_t state;
};

struct Trie
{
	struct TrieNode *root;
	size_t height;
};

/***************************************************************************
							STATIC FUNCTIONS
***************************************************************************/

static int SidePickerIMP(unsigned char *ip, size_t height);
static size_t RecLeafCounterIMP(trie_node_t *root);
static availability_t IsAvailableIMP(trie_node_t *root,
					 size_t height, unsigned char *ip);
static void FreeLeafHelperIMP(trie_node_t *root, size_t height,
											 unsigned char *ip);
static status_t InsertHelperIMP(trie_node_t *root, size_t height,
										 const unsigned char *ip);
static void RecDestroyIMP(trie_node_t *root);
static trie_node_t *NodeGeneratorIMP();
static void UpdateAvilabilityIMP(trie_node_t *root);
static void NextAvailableIMP(trie_node_t *node, size_t height,
										 unsigned char *buffer);
static void ZeroingAvailBits(unsigned char *ip_allocated, size_t height);

/***************************************************************************
							API FUNCTIONS
***************************************************************************/

trie_t *TrieCreate(size_t height)
{
	trie_t *tree = malloc(sizeof(*tree));
	if (NULL == tree)
	{
		return NULL;
	}
	tree->root = NodeGeneratorIMP();
	if (NULL == tree->root)
	{
		free(tree);tree = NULL;
		return NULL;
	}
	tree->height = height;

	return tree;
}

void TrieDestroy(trie_t *trie)
{
	assert(NULL != trie);

	RecDestroyIMP(trie->root);trie->root = NULL;
	free(trie); trie = NULL;
}

status_t TrieInsert(trie_t *trie, const unsigned char *ip)
{
	const unsigned char *runner = ip;

	assert(NULL != trie);
	assert(NULL != ip);

	return (InsertHelperIMP(trie->root, trie->height, runner));
}

void TrieFreeLeaf(trie_t *trie, unsigned char *ip)
{
	unsigned char *runner = ip;

	assert(NULL != trie);
	assert(NULL != ip);

	FreeLeafHelperIMP(trie->root, trie->height, runner);
}

void TrieNextAvailable(trie_t *trie, unsigned char *ip_allocated)
{   
    assert(NULL != trie);
   	
   	ZeroingAvailBits(ip_allocated, trie->height);
    NextAvailableIMP(trie->root, trie->height, ip_allocated);
}

availability_t TrieIsAvailable(const trie_t *trie, unsigned char *ip)
{
	unsigned char *runner = ip;

	assert(NULL != trie);
	assert(NULL != ip);

	return (IsAvailableIMP(trie->root, trie->height, runner));
}
             
size_t TrieCountOccupiedLeafs(const trie_t *trie)
{
	assert(NULL != trie);

	return RecLeafCounterIMP(trie->root);	
}

/***************************************************************************
							STATIC FUNCTIONS
***************************************************************************/

static size_t RecLeafCounterIMP(trie_node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}

	if ((NULL == root->direction[LEFT]) && (NULL == root->direction[RIGHT]) && 
														(root->state == TAKEN))
	{
		return 1;
	}

	return (RecLeafCounterIMP(root->direction[LEFT]) + RecLeafCounterIMP(root->direction[RIGHT]));
}

static availability_t IsAvailableIMP(trie_node_t *root, size_t height,
													 unsigned char *ip)
{
	int side = SidePickerIMP(ip, height);
	if (TAKEN == root->state)
	{
		return TAKEN;
	}
	if ((0 == height) || (NULL == root->direction[side]))
	{
		return AVAILABLE;
	}
	
	return IsAvailableIMP(root->direction[side], (height - 1), ip);
}

static void FreeLeafHelperIMP(trie_node_t *root, size_t height,
											 unsigned char *ip)
{
	int side = SidePickerIMP(ip, height);
	if (NULL == root)
	{
		return;
	}

	if (0 == height)
	{
		root->state = AVAILABLE;
		return;
	}

	root->state = AVAILABLE;

	FreeLeafHelperIMP(root->direction[side], (height - 1), ip);
}

static status_t InsertHelperIMP(trie_node_t *root, size_t height,
										 const unsigned char *ip)
{
	status_t status = SUCC;
	unsigned char *runner = (unsigned char *)ip;
	int side = 0;

	if (0 == height)
	{
		root->state = TAKEN;
		return SUCC;
	}

	side = SidePickerIMP(runner, height);

	if (NULL == root->direction[side])
	{
		root->direction[side] = NodeGeneratorIMP();
		if (NULL == root->direction[side])
		{
			return FAIL;
		}
	}

	status = InsertHelperIMP(root->direction[side], (height - 1), ip);

	UpdateAvilabilityIMP(root);

	return status;
}

static void RecDestroyIMP(trie_node_t *root)
{
	if (NULL == root)
	{
		return;
	}
	RecDestroyIMP(root->direction[LEFT]);
	RecDestroyIMP(root->direction[RIGHT]);

	root->direction[LEFT] = NULL;
	root->direction[RIGHT] = NULL;
	free(root); root = NULL;
}

static int SidePickerIMP(unsigned char *ip, size_t height)
{
	assert(NULL != ip);

	return (((*(ip + (BITS_IN_IP - height) / BITS_IN_BYTE)) & 
		(LSB << (height - 1) % BITS_IN_BYTE)) >> ((height - 1) % BITS_IN_BYTE));
}

static trie_node_t *NodeGeneratorIMP()
{
	trie_node_t *node = malloc(sizeof(*node));
	if (NULL == node)
	{
		return NULL;
	}

	node->direction[LEFT] = NULL;
	node->direction[RIGHT] = NULL;
	node->state = AVAILABLE;

	return node;
}

static void UpdateAvilabilityIMP(trie_node_t *root)
{
	if ((NULL != root->direction[LEFT]) && (NULL != root->direction[RIGHT]))
	{
		if ((TAKEN == root->direction[LEFT]->state) && 
			(TAKEN == root->direction[RIGHT]->state))
		{
			root->state = TAKEN;
		}
	}
}

static void NextAvailableIMP(trie_node_t *root, size_t height,
										 unsigned char *buffer)
{
	assert(NULL != root);
	assert(NULL != buffer);

    if (NULL == root || 0 == height)
    {
        return;  
    }
   
    if (AVAILABLE == root->direction[LEFT]->state)
    {
        NextAvailableIMP(root->direction[LEFT], (height - 1), buffer);
    }
   
    else
    {
        *(buffer + (BITS_IN_IP - height) / BITS_IN_BYTE) |=
                 (LSB << (height - 1) % BITS_IN_BYTE);
        NextAvailableIMP(root->direction[RIGHT], (height - 1), buffer);
    }
}

static void ZeroingAvailBits(unsigned char *ip_allocated, size_t height)
{
	size_t available_bits = height;

	assert(NULL != ip_allocated);
	
	for (; height > 0; --height)
	{
		*(ip_allocated + (BITS_IN_IP - available_bits) / BITS_IN_BYTE) &=
                 ~(LSB << ((height - 1) % BITS_IN_BYTE));
	}
}