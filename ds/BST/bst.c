/*********************************/
/*   BST                         */
/*   Yoav Hattav                 */
/*   Last Updated 09/01/20       */
/*   Reviewed by: Israel         */
/*********************************/

#include <stdio.h>  /* sizeof */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/bst.h"    /* API */

#define END_DATA 0xDEADBEEF

enum Bool {FALSE, TRUE};
enum Side {LEFT, RIGHT};
enum State {SUCC, FAIL};

typedef struct BSTNode bst_node_t;

struct BSTNode
{
	void *data;
	struct BSTNode *child[2];
	struct BSTNode *parent;
};

struct BSTree
{
	bst_node_t dummy;
	compare_func_t cmp;
	void *param;
};

static int WhichChild(bst_itr_t itr)
{
	assert(NULL != itr);

	return (itr->parent->child[LEFT] != itr);
}

bst_t *BSTCreate(compare_func_t cmp, void *param)
{
	bst_t *tree = NULL;

	assert(NULL != cmp);

	tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == tree)
	{
		return NULL;
	}

	tree->cmp = cmp;
	tree->param = param;

	tree->dummy.data = (void *)END_DATA;
	tree->dummy.child[LEFT] = NULL;
	tree->dummy.child[RIGHT] = NULL;
	tree->dummy.parent = NULL;

	return tree;
}

void BSTDestroy(bst_t *tree)
{
	bst_itr_t itr = NULL;
	int side = 0;

	assert(NULL != tree);

	itr = tree->dummy.child[LEFT];

	while (TRUE != BSTIsEmpty(tree))
	{
		while (NULL != itr->child[LEFT] || NULL != itr->child[RIGHT])
		{
			if (NULL != itr->child[LEFT])
			{
				itr = itr->child[LEFT];
			}
			else
			{
				itr = itr->child[RIGHT];
			}
		}
		side = WhichChild(itr);
		itr = itr->parent;
		free(itr->child[side]); itr->child[side] = NULL;
	}
	free(tree); tree = NULL;
}

int BSTInsert(bst_t *tree, void *data)
{
	bst_itr_t node_ptr = NULL;
	bst_itr_t connect_to_itr = NULL;
	int default_side = LEFT;

	assert(NULL != tree);
	assert(NULL != data);

	node_ptr = (bst_itr_t)malloc(sizeof(bst_node_t));
	if (NULL == node_ptr)
	{
		return FAIL;
	}
	
	connect_to_itr = (bst_itr_t)&tree->dummy;

	if (TRUE != BSTIsEmpty(tree))
	{
		connect_to_itr = tree->dummy.child[LEFT];
		while (NULL != connect_to_itr->child[tree->cmp(data, connect_to_itr->data, NULL)])
		{
			connect_to_itr = connect_to_itr->child[tree->cmp(data, connect_to_itr->data, NULL)];
		}
		default_side = tree->cmp(data, connect_to_itr->data, NULL);
	}

	connect_to_itr->child[default_side] = node_ptr;

	node_ptr->data = data;
	node_ptr->child[RIGHT] = NULL;
	node_ptr->child[LEFT] = NULL;
	node_ptr->parent = connect_to_itr;

	return SUCC;
}

void BSTRemove(bst_itr_t it)
{
	bst_itr_t successor_it = NULL;

	assert(NULL != it);

	if (NULL != it->child[LEFT] && NULL != it->child[RIGHT])
	{
		successor_it = BSTNext(it);
		it->parent->child[WhichChild(it)] = it->child[RIGHT];
		it->child[RIGHT]->parent = it->parent;

		it->child[LEFT]->parent = successor_it;
		successor_it->child[LEFT] = it->child[LEFT]; 
	}
	else if (NULL != it->child[LEFT] || NULL != it->child[RIGHT])
	{
		if (NULL != it->child[LEFT])
		{
			it->parent->child[WhichChild(it)] = it->child[LEFT];
			it->child[LEFT]->parent = it->parent;
		}
		else
		{
			it->parent->child[WhichChild(it)] = it->child[RIGHT];
			it->child[RIGHT]->parent = it->parent;
		}
	}
	else
	{
		it->parent->child[WhichChild(it)] = NULL;
	}

	free(it); it = NULL;
}

bst_itr_t BSTFind(const bst_t *tree, const void *data)
{
    int direction = 0;    
    bst_itr_t it = NULL;
   
    assert(NULL != tree);
   
    it = &((bst_t *)tree)->dummy;
     
    while (NULL != it->child[direction])
    {  
        it = it->child[direction];
        direction = tree->cmp(data, it->data, tree->param);
   
        if ((0 == direction) && (0 == tree->cmp(it->data, data, tree->param)))
        {
            return it;
        }
    }
   
    return BSTEnd(tree);
}

int BSTForeach(bst_itr_t start, bst_itr_t end, action_func_t action, void *param)
{
	bst_itr_t itr = NULL;

	assert(NULL != start);
	assert(NULL != end);
	assert(NULL != action);

	itr = start;
	for ( ; itr != end ; itr = BSTNext(itr))
	{
		if (SUCC != action(itr->data, param))
		{
			return FAIL;
		}
	}

	return SUCC;
}

size_t BSTSize(const bst_t *tree)
{
	bst_itr_t itr = NULL;
	size_t size = 0;

	assert(NULL != tree);

	itr = BSTBegin(tree);
	while (NULL != itr->parent)
	{
		++size;
		itr = BSTNext(itr);
	}

	return size;
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);

	return (tree->dummy.child[LEFT] == tree->dummy.child[RIGHT]);
}

void *BSTGetData(bst_itr_t it)
{
	assert(NULL != it);

	return it->data;
}

bst_itr_t BSTBegin(const bst_t *tree)
{
	bst_itr_t itr = NULL;

	assert(NULL != tree);

	itr = (bst_itr_t)&tree->dummy;
	while (NULL != itr->child[LEFT])
	{
		itr = itr->child[LEFT];
	}

	return itr;
}

bst_itr_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);

	return (bst_itr_t)&(tree->dummy);
}

bst_itr_t BSTNext(bst_itr_t it)
{
	assert(NULL != it);

	if (NULL != it->child[RIGHT])
	{
		it = it->child[RIGHT];
		while (NULL != it->child[LEFT])
		{
			it = it->child[LEFT];
		}
	}
	else
	{
		while (RIGHT == WhichChild(it))
		{
			it = it->parent;
		}
		it = it->parent;
	}

	return it;	
}

bst_itr_t BSTPrev(bst_itr_t it)
{
	assert(NULL != it);

	if (NULL != it->child[LEFT])
	{
		it = it->child[LEFT];
		while (NULL != it->child[RIGHT])
		{
			it = it->child[RIGHT];
		}
	}
	
	else
	{
		while (NULL != it->parent->parent && LEFT == WhichChild(it))
		{
			it = it->parent;
		}
		it = it->parent;
	}
	
	return it;
}

int BSTIsSameItr(bst_itr_t it1, bst_itr_t it2)
{
	assert(NULL != it1);
	assert(NULL != it2);

	return (it1 == it2);
}