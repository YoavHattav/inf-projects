#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/bst.h"

#define END_DATA 0xDEADBEEF

typedef struct BSTNode bst_node_t;

struct BSTNode
{
	void *data;
	struct BSTNode *child[2];
	struct BSTNode parent;
};

struct BSTree
{
	bst_node_t dummy;
	compare_func_t cmp;
	void *param;
};





static int WhichChild(bst_itr_t itr)
{

}

/*********************************************** 
    Returns a pointer to the BST data structure
	Complexity of malloc     
 ***********************************************/
bst_t *BSTCreate(compare_func_t cmp, void *param)
{
	bst_t *tree = NULL;
	bst_node_t *dummy = NULL;

	assert(NULL != param);
	assert(NULL != cmp);

	tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == tree)
	{
		return NULL;
	}

	tree->cmp = cmp;
	tree->param = param;

	tree->dummy.data = (void *)0xDEADBEEF;
	tree->dummy.child[LEFT] = NULL;
	tree->dummy.child[RIGHT] = NULL;
	tree->dummy.parent = NULL;

	return tree;
}
/*userdata > data2*/

/************************************************** 
	Destroys the DLL data and free it from memory 
	Complexity of free                            
 **************************************************/
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
		WhichChild() = side;
		itr = itr->parent;
		free(itr->child[side]); itr->child[side] = NULL;
	}
}

/********************************************************************* 
	Gets a pointer to the tree and insert new data in the right place  
	Return 0 for success, otherwise: 1
	Complexity of malloc + O(log(n))                            
 ********************************************************************/
int BSTInsert(bst_t *tree, void *data)
{

}

/*********************************************** 
	Get an iterator to remove from the tree
	Complexity: O(1)
 ***********************************************/
void BSTRemove(bst_itr_t it)
{

}

/*********************************************************************** 
	Gets a pointer to the tree and search if the data exist in the tree
	Returns an iterator to the data if it was found, otherwise: NULL
	Complexity: avg-case: O(log(n)), worst-case: O(n)
 ***********************************************************************/
bst_itr_t BSTFind(const bst_t *tree, const void *data)
{
	bst_itr_t itr = NULL;

	assert(NULL != tree);
	assert(NULL != data);

	itr = tree->dummy.child[LEFT];
	while (itr->data != *data && (itr->child[LEFT] != NULL && itr->child[RIGHT] != NULL))
	{
		itr = itr->child[tree->cmp(data, itr->data)]
	}

	return (itr->data == *data == *data ? itr : NULL);
}

/********************************************************************************** 
	Gets iterators to the start and the end,
		 action function to operate on the elements in the tree
	Returns 0 for success, otherwise: non-zero value
	Complexity: worst-case: O(n) 
 ***********************************************************************************/
int BSTForeach(bst_itr_t start, bst_itr_t end, action_func_ptr action, void *param);

/*********************************************** 
	Gets a pointer to the tree
	Returns the size of the tree
	complexity: O(n)                  
 ***********************************************/
size_t BSTSize(const bst_t *tree)
{
	bst_itr_t itr = NULL;
	size_t size = 0;

	assert(NULL != tree);

	itr = BSTBegin(tree);
	while (0xDEADBEEF)
	{

	}

}

/*********************************************** 
	Gets a pointer to the tree
	Returns 1 if empty, otherwise: 0
	Complexity: O(1)
 ***********************************************/
int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);

	return (tree->dummy.child[LEFT] == tree->dummy.child[RIGHT]);
}

/*********************************************** 
	Gets an iterator 
	Returns the data it contains
	complexity: O(1)                       
 ***********************************************/
void *BSTGetData(const bst_itr_t it)
{
	assert(NULL != it);

	return it->data;
}

/***************************************************** 
	Gets pointer to the tree
	Returns the first element in the tree
	Complexity: avg-case: O(log(n)), worst-case: O(n)
 *****************************************************/
bst_itr_t BSTBegin(const bst_t *tree)
{
	bst_itr_t itr = NULL;

	assert(NULL != tree);

	itr = tree->dummy.child[LEFT];
	while (NULL != itr->child[LEFT])
	{
		itr = itr->child[LEFT];
	}

	return itr;
}

/***************************************************** 
	Gets pointer to the tree
	Returns the last element in the tree
	Complexity: avg-case: O(log(n)), worst-case: O(n)
 *****************************************************/
bst_itr_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);

	return (bst_itr_t)&(tree->dummy);
}

/******************************************************* 
	Gets an iterator
	Returns an iterator to the next element in the tree
	Complexity: O(1)
 *******************************************************/
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
		return it;
	}
	
	while (RIGHT == WhichChild(it))
	{
		it = it->parent;
	}
	it = it->parent;
	
	return it;	
}

/******************************************************* 
	Gets an iterator
	Returns an iterator to the previous element in the tree
	Complexity: O(1)
 *******************************************************/
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
		return it;
	}
	
	while (LEFT == WhichChild(it))
	{
		it = it->parent;
	}
	it = it->parent;
	
	return it;
}

/******************************************************* 
	Gets 2 iterators
	Returns 1 if they are equal, otherwise: 0
	Complexity: O(1)
 *******************************************************/
int BSTIsSameItr(const bst_itr_t it1, const bst_itr_t it2)
{
	assert(NULL != it1);
	assert(NULL != it2);

	return (it1 == it2);
}