/*********************************/
/*   TRIE                        */
/*   Yoav Hattav                 */
/*   Last Updated 30/01/20       */
/*   Reviewed by:          */
/*********************************/

#include <stdio.h>  /* sizeof */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/trie.h" /* API */

#define END_DATA 0xDEADBEEF

enum child {LEFT, RIGHT};
typedef enum availability {TAKEN, AVAILABLE} availability_t;


typedef struct TrieNode trie_node_t;

struct TrieNode
{
	struct TrieNode *direction[2];
	availability_t state;
};

struct Trie
{
	struct TrieNode *root;
};
  
static trie_node_t *NodeGenerator()
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

trie_t *TrieCreate()
{
	trie_t *tree = malloc(sizeof(*tree));
	if (NULL == tree)
	{
		return NULL;
	}
	tree->root = NodeGenerator();
	if (NULL == tree->root)
	{
		free(tree);tree = NULL;
		return NULL;
	}

	return tree;
}

 static void RecDestroy(trie_node_t *root)
{
	if (NULL == root)
	{
		return;
	}
	RecDestroy(root->direction[LEFT]);
	RecDestroy(root->direction[RIGHT]);

	free(root); root = NULL;
}

void TrieDestroy(trie_t *trie)
{
	assert(NULL != trie);

	RecDestroy(trie->root);
	free(trie); trie = NULL;
}

availability_t TrieIsAvailable(trie_t *trie, char *str)
{
	trie_node_t *current = NULL;

	assert(NULL != trie);
	assert(NULL != str);

	current = trie->root;
	while (*str)
	{
		if (NULL == current->direction[(int)*str])
		{
			return AVAILABLE;
		}
		if (TAKEN == current->state)
		{
			return TAKEN;
		}

		current = current->direction[(int)*str];
		++str;
	}

	return AVAILABLE;
}

static void UpdateAvilability(trie_node_t *root)
{
	if ((NULL != root->direction[LEFT]) && (NULL != root->direction[RIGHT]))
	{
		if ((TAKEN == root->direction[LEFT]->state) && (TAKEN == root->direction[RIGHT]->state))
		{
			root->state = TAKEN;
		}
	}
}

static status_t InsertHelper(trie_node_t *root, char *str)
{
	status_t status;

	if ('\0' == *str)
	{
		root->state = TAKEN;
		return SUCC;
	}

	if (NULL == root->direction[(int)*str])
	{
		root->direction[(int)*str] = NodeGenerator();
		if (NULL == root->direction[(int)*str])
		{
			return FAIL;
		}
	}

	status = InsertHelper(root->direction[(int)*str], str + 1);

	UpdateAvilability(root);

	return status;
}

status_t TrieInsert(trie_t *trie, char *str)
{
	assert(NULL != trie);
	assert(NULL != str);

	return (InsertHelper(trie->root, str));
}

                  
bool_t TrieIsEmpty(const trie_t *trie)
{
	return ((NULL == trie->root->direction[LEFT]) && (NULL == trie->root->direction[RIGHT]));
}

static size_t RecSize(trie_node_t *root)
{
	size_t size = 1;
	if (NULL == root)
	{
		return 0;
	}

	size += RecSize(root->direction[LEFT]);
	size += RecSize(root->direction[RIGHT]);

	return size;
}
             
size_t TrieSize(const trie_t *trie)
{
	assert(NULL != trie);

	return RecSize(trie->root);	
}

static size_t RecLeafCounter(trie_node_t *root)
{
	int size = 0;

	if (NULL == root)
	{
		return 0;
	}

	if ((NULL == root->direction[LEFT]) && (NULL == root->direction[RIGHT]) && (root->state == TAKEN))
	{
		++size;
	}

	size += RecSize(root->direction[LEFT]);
	size += RecSize(root->direction[RIGHT]);

	return size;
}
             
size_t TrieCountLeafs(const trie_t *trie)
{
	assert(NULL != trie);

	return RecLeafCounter(trie->root);	
}

