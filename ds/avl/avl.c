#include <assert.h>	/* assert */ 
#include <stdlib.h>	/* malloc */

#include "../include/avl.h"

#define NOT_NEEDED 0xDEADBEEF

enum Bool {FALSE, TRUE};
enum Children {LEFT, RIGHT};
enum Status {SUCC, FAIL};

struct AVLNode
{
	void *data;
	struct AVLNode *child[2];
	size_t height;
};

struct AVLTree
{
	avl_node_t *root;
	compare_func_t cmp;
};

avl_t *AVLCreate(compare_func_t cmp)
{
	avl_t *tree = NULL;

	assert(NULL != cmp);

	tree = malloc(sizeof(*tree));
	if (NULL != tree)
	{
		tree->root = NULL;
		tree->cmp = cmp;
	}

	return tree;
}

static void RecDestroy(avl_node_t *root)
{
	if (NULL == root)
	{
		return;
	}
	RecDestroy(root->child[LEFT]);
	RecDestroy(root->child[RIGHT]);

	free(root); root = NULL;
}

void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);

	RecDestroy(tree->root);
	free(tree); tree = NULL;
}

static avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = NULL;

	new_node = malloc(sizeof(*new_node));

	if (NULL != new_node)
	{
		new_node->data = data;
		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
		new_node->height = 0;
	}

	return new_node;
}

static void UpdateHighet(avl_node_t *subtree)
{
	if ((NULL != subtree->child[LEFT]) && (NULL != subtree->child[RIGHT]))
	{
		subtree->height = (subtree->child[RIGHT]->height > subtree->child[LEFT]->height) ?
					subtree->child[RIGHT]->height + 1 : subtree->child[LEFT]->height + 1;

	return;
	}

	if ((NULL == subtree->child[LEFT]) && (NULL != subtree->child[RIGHT]))
	{
		subtree->height = subtree->child[RIGHT]->height + 1;
		return;
	}

	if ((NULL != subtree->child[LEFT]) && (NULL == subtree->child[RIGHT]))
	{
		subtree->height = subtree->child[LEFT]->height + 1;
		return;
	}

	if ((NULL == subtree->child[LEFT]) && (NULL == subtree->child[RIGHT]))
	{
		subtree->height = 0;
		return;
	}
}

static avl_node_t *SingleRotation(avl_node_t *root, int side)
{
	avl_node_t *new_root = NULL;

	assert(NULL != root);

	new_root = root->child[side];
	root->child[side] = new_root->child[!side];
	new_root->child[!side] = root;

	UpdateHighet(root);
	UpdateHighet(new_root);

	return new_root;
}

static int NodeHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return -1;
	}

	return node->height;
}

static int IsBalanceNeeded(avl_node_t *root)
{
	int heightdeff = 0;

	assert(NULL != root);

	heightdeff = NodeHeight(root->child[LEFT]) - NodeHeight(root->child[RIGHT]);
	
	if (-1 > heightdeff)
	{
		return RIGHT;
	}
	else if (1 < heightdeff)
	{
		return LEFT;
	}

	return NOT_NEEDED;
}

static avl_node_t *AVLBalance(avl_node_t *root)
{
	unsigned int inbalance = 0; 

	UpdateHighet(root);

	inbalance = IsBalanceNeeded(root);

	if (inbalance == LEFT)
	{
		if (NodeHeight(root->child[LEFT]->child[LEFT]) < NodeHeight(root->child[LEFT]->child[RIGHT]))
		{
			root->child[LEFT] = SingleRotation(root->child[LEFT], RIGHT);
		}

		return SingleRotation(root, LEFT);
	}

	else if (inbalance == RIGHT)
	{
		if (NodeHeight(root->child[RIGHT]->child[RIGHT]) < NodeHeight(root->child[RIGHT]->child[LEFT]))
		{
			root->child[RIGHT] = SingleRotation(root->child[RIGHT], LEFT);	
		}
		
		return SingleRotation(root, RIGHT);
	}

	return root;
}

static avl_node_t *RecInsert(avl_node_t *root, compare_func_t cmp, avl_node_t *node)
{
	int side = LEFT;

	assert(NULL != root);
	assert(NULL != node);
	assert(NULL != cmp);

	side = cmp(node->data, root->data);
	side = (side > 0);

	if (NULL == root->child[side])
	{
		root->child[side] = node;
		AVLBalance(root);

		return root;
	}

	root->child[side] = RecInsert(root->child[side], cmp, node);
	
	return AVLBalance(root);

}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = NULL;

	assert(NULL != tree);
	assert(NULL != data);

	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return FAIL;
	}

	if (NULL != tree->root)
	{
		tree->root = RecInsert(tree->root, tree->cmp, new_node);

		return SUCC;
	}
	
	tree->root = new_node;

	return SUCC;
}

static avl_node_t *FindSuccessor(avl_node_t *node, avl_node_t **successor)
{
	if (NULL == node->child[LEFT])
	{
		*successor = node;
		return node->child[RIGHT];
	}

	node->child[LEFT] = FindSuccessor(node->child[LEFT], successor);

	return AVLBalance(node);
}

static avl_node_t *FindReplacemant(avl_node_t *node)
{
	if (NULL != node->child[RIGHT])
	{
		if (NULL != node->child[LEFT])
		{
			avl_node_t *successor = NULL;

			if (NULL == node->child[RIGHT]->child[LEFT])
			{
				successor = node->child[RIGHT];
			}

			else
			{
				node->child[RIGHT] = FindSuccessor(node->child[RIGHT], &successor);
				successor->child[RIGHT] = node->child[RIGHT];
			}
			
			successor->child[LEFT] = node->child[LEFT];
			return AVLBalance(successor);
		}

		return node->child[RIGHT];
	}

	return node->child[LEFT];
}

static avl_node_t *RecRemove(avl_node_t *node, compare_func_t cmp, const void *data)
{
	avl_node_t *new_node = NULL;
	int side = cmp(data, node->data);
	side = (side > 0);

	if (NULL == node)
	{
		return NULL;
	}

	else if (0 == cmp(data, node->data))
	{
		new_node = FindReplacemant(node);
		free(node);
		return new_node;
	}

	node->child[side] = RecRemove(node->child[side], cmp, data);

	return AVLBalance(node);
}

void AVLRemove(avl_t *tree, const void *data)
{
	assert(NULL != tree);
	assert(NULL != data);

	tree->root = RecRemove(tree->root, tree->cmp, data);
}

static avl_node_t *RecFind(avl_node_t *root, compare_func_t cmp, void *data)
{
	int side = LEFT;

	if (NULL == root)
	{
		return NULL;
	}
	
	assert(NULL != data);
	assert(NULL != cmp);

	side = cmp(data, root->data);
	if (0 == side)
	{
		return root;
	}
	side = (side > 0);

	return RecFind(root->child[side], cmp, data);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	avl_node_t *result = NULL;

	assert(NULL != tree);
	assert(NULL != data);


	result = RecFind(tree->root, tree->cmp, (void *)data);


	if (NULL == result)
	{
		return NULL;
	}
	return result->data;
}

static int RecForEach(avl_node_t *root, action_ptr_t action, void *param)
{
	int result = 0;

	if (NULL == root)
	{
		return SUCC;
	}

	result += RecForEach(root->child[LEFT], action, param);
	result += action(root->data, param);
	result += RecForEach(root->child[RIGHT], action, param);

	return result;
}

int AVLForeach(avl_t *tree, action_ptr_t action, void *param)
{
	assert(tree);
	assert(action);

	return RecForEach(tree->root, action, param);
}

static size_t RecSize(avl_node_t *root)
{
	size_t size = 1;
	if (NULL == root)
	{
		return 0;
	}

	size += RecSize(root->child[LEFT]);
	size += RecSize(root->child[RIGHT]);

	return size;
}

size_t AVLSize(const avl_t *tree)
{
	assert(NULL != tree);

	return RecSize(tree->root);
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(NULL != tree);

	return (NULL == tree->root);
}

size_t AVLGetHeight(const avl_t *tree)
{
	assert(NULL != tree);

	if (NULL == tree->root)
	{
		return 0;
	}
	return tree->root->height;	
}

