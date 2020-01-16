/*********************************/
/*   Implementing file DS 4      */
/*   linked list                 */
/*   Yoav Hattav                 */
/*   Last Updated 2/12/19        */
/*   Reviewed by: Israel         */
/*                               */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "linked_list.h" /* linked list functions */

#define FREE(ptr) free(ptr); ptr = NULL;
                 

/* Creates a new node */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLCreateNode(node_t *next, const void *data)
{
    node_t *newnode = NULL;
    
    newnode = (node_t *)malloc(sizeof(node_t));
    if (NULL == newnode)
    {
        return NULL;
    }

    newnode->data = (void *)data;
    newnode->next = next;
    
    return newnode;
}

/* Destroys the data structure */
/* WARNING: Doesnt get NULL pointer */
void SLLDestroy(node_t *node)
{
	node_t *runner  = NULL;

	assert(NULL != node);

	runner = node;

	while (NULL != runner)
	{
		runner = node->next;
		node->next = NULL;
		FREE (node);
		node = runner;
	}
}

/* Inserts a new node before the node sent to the function */
/* WARNING: Doesnt get NULL pointer */
int SLLInsert(node_t *node, node_t *next_node)
{
	void *temp = NULL;

	assert(NULL != node);
	assert(NULL != next_node);

	node->next = next_node->next;
	next_node->next = node;

	temp = node->data;
	node->data = next_node->data;
	next_node->data = temp;

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
	node_t *temp = NULL;

	assert(NULL != node);
	
    temp = node->next;
	node->data = temp->data;
	node->next = temp->next;
	FREE(temp); 
}

/* Removes the node after the node sent to the function */
/* WARNING: Doesnt get NULL pointer */
void SLLRemoveAfter(node_t *node)
{
    node_t *temp_node = NULL;    
    
    assert(NULL != node);  
	
	temp_node = node->next;
	node->next = temp_node->next;
	FREE(temp_node);
}

/* Returns a node according to a condition specified by the user */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLGetNode(const node_t *head, match_func_ptr ptr_to_func, void *additional)
{
	node_t *runner = NULL;
    
    assert(NULL != head);
    
    runner = (node_t *)head;
    
	while (NULL != runner->next)
	{
		if (0 == ptr_to_func(runner, additional))
		{
			runner = runner->next;
		}
		else
		{
			return runner;
		}
		
	}
	
	return NULL;
}

/* Performs a generic operation on all nodes in the data structure */
/* WARNING: Doesnt get NULL pointer */
int SLLForEach(node_t *head, action_func_ptr ptr_to_func, void *additional)
{
	node_t *runner = NULL;
	
	assert(NULL != head);
    
    runner = head;

	while ((0 == ptr_to_func(runner, additional)) && (NULL != runner->next))
	{
		runner = runner->next;
	}
	
	return !(NULL == runner->next);
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

node_t *SLLRecFlip(node_t *head)
{
	node_t *new_head = NULL;

	if (NULL == head->next)
	{
		return head;
	}

	new_head = SLLRecFlip(head->next);

	head->next->next = head;
	head->next = NULL;

	return new_head;
}


char *StrcatRec(char *dest, const char *src)
{
	if (*dest != '\0')
	{
		StrcatRec(dest + 1 , src);
	}

	else if ((*dest = *src) != '\0')
	{
		StrcatRec(dest + 1 , src + 1);
	}

	return dest;
}

/* Checks if a loop occurs in the structure */
/* Returns 0 - loop occurs, 1 - loop doesnt occur */
/* WARNING: Doesnt get NULL pointer */
int SLLHasLoop(const node_t *head)
{
	node_t *slow = NULL;
	node_t *fast = NULL;
	node_t *temp = NULL;

	assert(NULL != head);

	slow = (node_t *)head;
	fast = (node_t *)head;
	temp = (node_t *)head;
    
    
	while ((NULL != slow->next) && (NULL != fast->next) && (NULL != temp->next))
	{
		
			slow = slow->next;
			temp = fast->next;
			fast = temp->next;

			if (slow == fast)
			{
				break;
			}
	}

	return ((slow == fast) && (NULL != slow));
}

/* Returns a pointer to the node the create an  */
/* WARNING: Doesnt get NULL pointer */
node_t *SLLFindIntersection(const node_t *head1, const node_t *head2)
{
	node_t *run1 = NULL;
	node_t *run2 = NULL;
	size_t run1_size = 0;
	size_t run2_size = 0;
	size_t diff = 0;
	size_t i = 0;

	assert(NULL != head1);
	assert(NULL != head2);
    
    run1_size = SLLSize(head1);
    run2_size = SLLSize(head2);

	if (run1_size > run2_size)
	{
		diff = run1_size - run2_size;
		run1 = (node_t *)head1;
		run2 = (node_t *)head2;
	}
	else
	{
		diff = run2_size - run1_size;
		run1 = (node_t *)head2;
		run2 = (node_t *)head1;
	}

	for (i = 0; i < diff; ++i)
	{ 
        run1 = run1->next; 
    }

    while (NULL != run1 && NULL != run2)
    { 
        if (run1 == run2)
        {
        	return run1; 
        }
        
        run1 = run1->next; 
        run2 = run2->next; 
    } 
	
	return NULL;
}

