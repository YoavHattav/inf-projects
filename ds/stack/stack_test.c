#include<stdio.h>
#include<string.h>

#include "stack.h"

#define NRM "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"

#define RUN_TEST(test,err_msg) {\
							if (test) \
							{\
								printf(GREEN"success\n");\
							} \
							else\
							{\
								printf(RED"FAIL: %s\n",err_msg);\
							}\
						}

struct Stack
{
	void *start;
	void *current;
	void *end;
	size_t element_size;
};

void Test()
{
	int checker = 7 , i = 0;
	int *data = &checker;
	stack_t *new_stack1 = 0, *new_stack2 = 0;
	char *string = "123456789";

	printf(NRM"StackCreate Tests\n");
	new_stack1 = StackCreate(1,20);
	RUN_TEST((new_stack1 != NULL ), "can't create a stack");	
	RUN_TEST((sizeof(*new_stack1) == 32 ), "stack size diff then expectation");
	RUN_TEST(((size_t)new_stack1->end - (size_t)new_stack1->start == 20 ),
											 "stack size diff then expectation");
	StackDestroy(new_stack1);
	new_stack1 = StackCreate(4,20);
	RUN_TEST(((size_t)new_stack1->end - (size_t)new_stack1->start == 80 ),
											 "stack size diff then expectation");	
	printf(NRM"StackPush Tests\n");
	RUN_TEST((StackPush(new_stack1,data) == 1), "1can't push normal value");	
	
	RUN_TEST(((size_t)new_stack1->current - (size_t)new_stack1->start == 4 ),	
												"1adress delta not as expected");
	new_stack2 = StackCreate(10,20);
	RUN_TEST((StackPush(new_stack2,"123456789") == 1), "can't push string value");	
	RUN_TEST(((size_t)new_stack2->current - (size_t)new_stack2->start == 10 ),	
								"adress delta not as expected for string size");
	/*uncomment only if you want the assert to fail!
	RUN_TEST((StackPush(new_stack,NULL) == 0), "fails to detect NULL==data");
	*/
	printf(NRM"StackSize Tests & Loop Pushing \n");

	for (; i < 19; ++i)
	{
		RUN_TEST(StackPush(new_stack2,"123456789"),"could not push");
		RUN_TEST((StackSize(new_stack2) == i+2), "Wrong # of item");
		RUN_TEST(!(strcmp((char*)StackPeek(new_stack2),"123456789")),"Peek Value not expected for ");	
	}

	printf(NRM"Full Stack Tests\n");
	RUN_TEST(((size_t)new_stack2->current - (size_t)new_stack2->start == 200 ),	
						"FullStack adress delta not as expected for string size");
	RUN_TEST((StackPush(new_stack2,"123456789") == 0),
											 "dosen't fail when stack is full");
	printf(NRM"IsEmpty Tests\n");
	RUN_TEST((StackIsEmpty(new_stack2) == 0), 
		"fails to detect that the file aint empty");
	StackPop(new_stack1);
	RUN_TEST((StackIsEmpty(new_stack1) == 1), 
		"fails to detect that the file is empty");

	printf(NRM"Poping and peeking loop tests \n");
	for (i = 20; i > 1; --i)
	{
		RUN_TEST(!(strcmp((char*)StackPeek(new_stack2),"123456789")),"Peek Value not expected for ");
		RUN_TEST((StackSize(new_stack2) == i), "size failed");	
		StackPop(new_stack2);	
	}
	


	printf(NRM"Search and Destroy\n");
	{
	StackDestroy(new_stack1);
	StackDestroy(new_stack2);
	}

}

int main()
{
	Test();

	return 0;
}

