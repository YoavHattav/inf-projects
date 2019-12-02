#include <assert.h>
#include <stdlib.h>

#include "linkedlist.h"

#define FREE(ptr) {\
				  	free(ptr); ptr = NULL;\
				  }

/* Creates a new node */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLCreateNode(node_t *next, const void *data)
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t));

	assert(NULL != data);

	if (NULL == new_node)
	{
		return NULL;
	}

	new_node->next = next;
	new_node->data = data;

	return new_node;
}

/* Destroys the data structure */
/* WARNING: Doesnt get NULL pointer */
void SLLDestroy(node_t *node)
{
	node_t *runner  = NULL;

	assert(NULL != node);

	while (NULL != runner)
	{
		runner = node->next;
		FREE (node);
		node = runner;
	}

	FREE(node);
}

/* Inserts a new node before the node sent to the function */
/* WARNING: Doesnt get NULL pointer */
int SLLInsert(node_t *node, node_t *old_node)
{
	node_t *temp = NULL;

	assert(NULL != node);
	assert(NULL != old_node);

	node->next = old_node->next;
	old_node->next = node;

	temp->data = node->data;
	node->data = old_node->data;
	old_node->data = temp->data;

	return 0;
}

/* Inserts a new node after the node sent to the function */
/* WARNING: Doesnt get NULL pointer */
int SLLInsertAfter(node_t *new_node, node_t *previous_node)
{

	assert(NULL != new_node);
	assert(NULL != previous_node);

	new_node->next = previous_node->next;
	previous_node->next = new_node;

	return 0;
}

/* Removes the node before the node sent to the function */
/* WARNING: Can't remove last  node */
/* WARNING: Doesnt get NULL pointer */
void SLLRemove(node_t *node)
{
	node_t *temp = node->next;

	assert(NULL != node);

	node->data = temp->data;
	node->next = temp->next;
	FREE(node->next); 
}

/* Removes the node after the node sent to the function */
/* WARNING: Doesnt get NULL pointer */
void SLLRemoveAfter(node_t *node)
{
	assert(NULL != node);

	{
		node_t *temp = node->next;
		node = temp->next;
		FREE(node->next);
	}
}

/* Returns a node according to a condition specified by the user */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLGetNode(const node_t *head, match_func_ptr, void *additional)
{
	node_t *runner = head;

	while (0 == match_func_ptr(runner, additional) && NULL != runner)
	{
		runner = runner->next;
	}

	return runner;
}

/* Performs a generic operation on all nodes in the data structure */
/* WARNING: Doesnt get NULL pointer */
int SLLForEach(const node_t *head, action_func_ptr, void *additional)
{
	const node_t *runner = head;

	while (1 == action_func_ptr(runner, additional) && NULL != runner)
	{
		runner = runner->next;
	}
	
	return !(NULL == runner);
}

/* Returns the number of nodes */
/* WARNING: Doesnt get NULL pointer */
size_t SLLSize(const node_t *head)
{
	size_t counter = 0;
	const node_t *runner = head;

	while (NULL != runner)
	{
		runner = runner->next;
		++counter;	
	}

	return counter;
}

/* Flips the direciton of pointing from last to first */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLFlip(node_t *head)
{
	node_t *previous = NULL;
	node_t *next = NULL;
	node_t *current = NULL;
	
	assert(NULL != head);

	current = head;

	while (NULL != current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	return previous;	
}

/* Checks if a loop occurs in the structure */
/* Returns 0 - loop occurs, 1 - loop doesnt occur */
/* WARNING: Doesnt get NULL pointer */
int SLLHasLoop(const node_t *head)
{
	node_t *runner = NULL;
	node_t *speedy = NULL;

	assert(NULL != head);

	runner = head;
	speedy = head;

	while (runner != speedy && NULL != runner)
	{
		runner = runner->next;
		speedy = runner->next;
	}

	return ((runner == speedy) && (runner != NULL));
}

/* Returns a pointer to the node the create an  */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLFindIntersection(const node_t *head1, const node_t *head2)
{
	node_t *speedy = NULL;
	node_t *gonzales = NULL;
	size_t speedysize = 0;
	size_t gonzalesize = 0;
	size_t difference = 0;
	size_t i = 0;

	assert(NULL != head1);
	assert(NULL != head2);
    
    speedysize = SLLSize(head1);
    gonzalesize = SLLSize(head2);

	if (speedysize > gonzalesize)
	{
		difference = speedysize - gonzalesize;
		speedy = head1;
		gonzales = head2;
	}
	else
	{
		difference = gonzalesize - speedysize;
		speedy = head2;
		gonzales = head1;
	}

	for (i = 0; i < difference i++)
	{ 
        speedy = speedy->next; 
    }

    while (speedy != NULL && gonzales != NULL)
    { 
        if (speedy == gonzales)
        {
        	return speedy; 
        }
        
        speedy = speedy->next; 
        gonzales = gonzales->next; 
    } 
	

	return NULL;
}
