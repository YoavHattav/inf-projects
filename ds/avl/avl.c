#include <assert.h>
#include <stdlib.h>
#include "../include/avl.h"


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
	RecDestroy(tree->root);
	free(tree); tree = NULL;
}

#ifndef NDEBUG
static avl_node_t *AVLBalance(avl_t *tree)
{
	assert(NULL != tree);
}
#endif

static avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = NULL;

	assert(NULL != data);

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

static void RecInsert(avl_node_t *root, compare_func_t cmp, avl_node_t *node)
{
	int side = LEFT;

	assert(NULL != root);
	assert(NULL != node);
	assert(NULL != cmp);

	side = cmp(node->data, root->data);
	side = (side == RIGHT);

	if (NULL == root->child[side])
	{
		root->child[side] = node;

		return;
	}

	RecInsert(root->child[side], cmp, node);

	return;
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
		RecInsert(tree->root, tree->cmp, new_node);

		#ifndef NDEBUG
		AVLBalance(tree);
		#endif

		return SUCC;
	}
	
	tree->root = new_node;

	return SUCC;
}

void AVLRemove(avl_t *tree, const void *data)
{

}

static avl_node_t *RecFind(avl_node_t *root, compare_func_t cmp, void *data)
{
	int side = LEFT;

	assert(NULL != root);
	assert(NULL != data);
	assert(NULL != cmp);

	side = cmp(data, root->data);
	side = (side == RIGHT);
	if (0 == side)
	{
		return root;
	}

	return RecFind(root->child[side], cmp, data);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	return (RecFind(tree->root, tree->cmp, (void *)data))->data;
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
	return RecSize(tree->root);
}

int AVLIsEmpty(const avl_t *tree)
{
	return (NULL == tree->root);
}

size_t AVLGetHeight(const avl_t *tree)
{

}

