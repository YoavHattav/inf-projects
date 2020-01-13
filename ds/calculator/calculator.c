/*********************************/
/*   BST                         */
/*   Yoav Hattav                 */
/*   Last Updated 11/01/20       */
/*   Reviewed by:             */
/*********************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "calculator.h"
#include "../include/stack.h"

#define FREE(ptr) free(ptr); ptr = NULL;
#define ASCII_SIZE 256
#define NUM_OF_STATES 3

static int LUTInit(calc_t *calc);

typedef enum
{
	PLUS,
	MULTI,
	POW,
	PARENTHE
}presedence_t;

typedef struct State
{
	state_t next_state;
	func_state_t handler;
}calc_state_t;

typedef struct Operator
{
	func_op_t op_func;
	int presedence;
}calc_op_t;

struct Calc
{
	stack_t *num_stack;
	stack_t *op_stack;
	double *result;
	calc_state_t **calc_lut;
	calc_op_t *op_lut;
};

char *DummyHandlerNumFunc(const char *expression, calc_t *calc){}
double DummyActionFunc(double *data1, double *data2){}

calc_status_t Calculator(const char *expression, double *result)
{
	calc_t *calc =  NULL;
	state_t status = 0;

	assert(NULL != expression);
	assert(NULL != result);

	calc = CalcInit(result);

	status = CalcRun(expression, calc, result);

	return status;
}

char *CalcHandleNum(const char *expression, calc_t *calc)
{
	double buffer = 0;
	const char *cal_runner = NULL;

	assert(NULL != expression);
	assert(NULL != calc);

	buffer = strtod(expression, (char **)cal_runner);
	return (0 == StackPush(calc->num_stack, &buffer)) ? (char *)cal_runner : NULL;
}

static int SmallScaleCalc(calc_t *calc)
{
	double first_pop_data2 = 0, second_pop_data1 = 0, res_holder = 0;
	char *op_holder = NULL;

	assert(NULL != calc);

	op_holder = StackPeek(calc->op_stack);
	StackPop(calc->op_stack);
	first_pop_data2 = *(double *)StackPeek(calc->num_stack);
	StackPop(calc->num_stack);
	second_pop_data1 = *(double *)StackPeek(calc->num_stack);
	StackPop(calc->num_stack);

	res_holder = calc->op_lut[*op_holder].op_func(&second_pop_data1, &first_pop_data2);
	if (!StackPush(calc->num_stack, &res_holder))
	{
		return 1;
	}
	calc->result = StackPeek(calc->num_stack);

	return 0;
}

char *CalcHandleOp(const char *expression, calc_t *calc)
{
	const char *runner = NULL;
	int succ_flag = 0;

	assert(NULL != expression);
	assert(NULL != calc);

	runner = expression;

	if ('\0' == *runner && !StackIsEmpty(calc->op_stack))
	{
		while (!StackIsEmpty(calc->op_stack))
		{
			SmallScaleCalc(calc);
		}
		++runner;
		return (char *)runner;
	}

	else if (StackIsEmpty(calc->op_stack))
	{
		succ_flag = StackPush(calc->op_stack, runner);
		++runner;
		return (char *)runner;	}

	else
	{
		while (calc->op_lut[*runner].presedence >= calc->op_lut[*(int *)StackPeek(calc->op_stack)].presedence
																	&& !StackIsEmpty(calc->op_stack))
		{
			SmallScaleCalc(calc);
		}
		succ_flag = StackPush(calc->op_stack, runner);
		++runner;
		return (char *)runner;
	}
}

calc_t *CalcInit(const char *expression, double *result)
{
	size_t len = 0;

	assert(NULL != expression);
	assert(NULL != result);

	calc_t *new_calc = (calc_t *)malloc(sizeof(calc_t));
	if (NULL == new_calc)
	{
		return NULL;
	}

	len = strlen(expression);

	new_calc->num_stack = StackCreate(sizeof(double), len);
	if (NULL == new_calc->num_stack)
	{
		FREE(new_calc);
	}

	new_calc->op_stack = StackCreate(sizeof(double), len);
	if (NULL == new_calc->op_stack)
	{
		FREE(new_calc->num_stack);
		FREE(new_calc);
	}

	LUTInit(new_calc);

	new_calc->result = result;
	return new_calc;
}

static int LUTInit(calc_t *calc)
{
	int i = 0, j = 0; 
  
    calc_state_t *calc_lut[NUM_OF_STATES];
    calc_op_t *op_lut;

    for (i = 0; i < NUM_OF_STATES; ++i)
    {
        calc_lut[i] = (calc_state_t *)malloc(ASCII_SIZE * sizeof(calc_state_t));
        if (NULL == calc_lut[i])
        {
        	--i;
        	for (;i >= 0; --i)
        	{
        		FREE(calc_lut[i]);
        	}
        	printf("malloc failed\n");
        	return ERROR;
        } 
    }
  
   	calc->calc_lut = calc_lut;

   	for (i = 0; i < ASCII_SIZE; ++i)
   	{
   		calc->calc_lut[WAIT_FOR_NUM][i].next_state = ERROR;
   		calc->calc_lut[WAIT_FOR_NUM][i].handler = &DummyHandlerNumFunc;
   	}
   	calc->calc_lut[WAIT_FOR_NUM][32].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM][32].handler = &CalcHandleNum;

   	calc->calc_lut[WAIT_FOR_NUM][40].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM][40].handler = &CalcHandleNum;

   	calc->calc_lut[WAIT_FOR_NUM][43].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM][43].handler = &CalcHandleNum;

	calc->calc_lut[WAIT_FOR_NUM][45].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM][45].handler = &CalcHandleNum;
   	for (i = 48; i < 58; ++i)
   	{
   		calc->calc_lut[WAIT_FOR_NUM][i].next_state = WAIT_FOR_OP;
   		calc->calc_lut[WAIT_FOR_NUM][i].handler = &CalcHandleNum;
   	}



   	for (i = 0; i < ASCII_SIZE; ++i)
   	{
   		calc->calc_lut[WAIT_FOR_OP][i].next_state = ERROR;
   		calc->calc_lut[WAIT_FOR_OP][i].handler = &DummyHandlerNumFunc;
   	}

   	calc->calc_lut[WAIT_FOR_OP][43].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP][43].handler = &CalcHandleOp;

	calc->calc_lut[WAIT_FOR_OP][45].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP][45].handler = &CalcHandleOp;

   	calc->calc_lut[WAIT_FOR_OP]['\0'].next_state = ERROR;
   	calc->calc_lut[WAIT_FOR_OP]['\0'].handler = &CalcHandleOp;



	op_lut = (calc_op_t *)malloc(ASCII_SIZE * sizeof(calc_op_t));
	if (NULL == op_lut)
	{
		printf("malloc failed\n");
		return ERROR;
	}
    calc->op_lut = op_lut;

   	for (i = 0; i < ASCII_SIZE; ++i)
   	{
   		calc->op_lut[i].op_func = DummyActionFunc;
   		calc->op_lut[i].presedence = 0;
   	}
   	calc->op_lut[43].op_func = &PlusActionFunc;
   	calc->op_lut[43].presedence = PLUS;

   	calc->op_lut[40].op_func = &MinusActionFunc;
   	calc->op_lut[40].presedence = PLUS;

   	return 0;
}



void CalcDestroy(calc_t *calc)
{
	int i = 0;

	assert(calc);

	StackDestroy(calc->num_stack);
	StackDestroy(calc->op_stack);

	for (i = 0; i < NUM_OF_STATES; ++i)
	{
		FREE(calc->calc_lut[i]);
	}

	FREE(calc->op_lut);
	FREE(calc);
}

calc_status_t CalcRun(const char *expression, calc_t *calc, double *result)
{
	state_t calc_status = WAIT_FOR_NUM;
	const char *runner = NULL;

	assert(expression);
	assert(calc);

	runner = expression;

	while (ERROR != calc_status)
	{
		runner = calc->calc_lut[calc_status][*runner].handler(expression, calc);
		calc_status = calc->calc_lut[calc_status][*expression].next_state;
	}

	return calc_status;
}

