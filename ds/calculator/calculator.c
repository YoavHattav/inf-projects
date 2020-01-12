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
	PARENTHE,
	POW,
	MULTI,
	PLUS
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
	stack_t *num;
	stack_t *ops;
	double *result;
	calc_state_t **calc_lut;
	calc_op_t *op_lut;
};

char *DummyFuncNUM(const char *expression, calc_t *calc){}
double *DummyActionFunc(double *data1, double *data2){}

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

double *PlusActionFunc(double *data1, double *data2)
{
	double res = (*data1 + *data2);

	return &res;
}

double *MinusActionFunc(double *data1, double *data2)
{
	double res = (*data1 - *data2);

	return &res;
}






char *CalcHandleNum(const char *expression, calc_t *calc)
{
	double buffer = 0;
	const char *cal_runner = NULL;

	assert(NULL != expression);
	assert(NULL != calc);

	buffer = strtod(expression, (char **)cal_runner);
	return (0 == StackPush(calc->num, &buffer)) ? (char *)cal_runner : NULL;
}

char *CalcHandleOp(const char *expression, calc_t *calc)
{

}

calc_t *CalcInit(const char *expression, double *result)
{
	size_t len = 0;

	calc_t *new_calc = (calc_t *)malloc(sizeof(calc_t));
	if (NULL != new_calc)
	{
		return NULL;
	}

	new_calc->result = result;
	new_calc->calc_lut = NULL;
	new_calc->op_lut = NULL;

	len = strlen(expression);

	new_calc->num = StackCreate(sizeof(double), len);
	if (NULL != new_calc->num)
	{

		FREE(new_calc);
	}

	new_calc->ops = StackCreate(sizeof(double), len);
	if (NULL != new_calc->ops)
	{

	}

	LUTInit(new_calc);

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
   		calc->calc_lut[WAIT_FOR_NUM][i].handler = &DummyFuncNUM;
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
   		calc->calc_lut[WAIT_FOR_OP][i].handler = &DummyFuncNUM;
   	}

   	calc->calc_lut[WAIT_FOR_OP][43].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP][43].handler = &CalcHandleOp;

	calc->calc_lut[WAIT_FOR_OP][45].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP][45].handler = &CalcHandleOp;



	op_lut = (calc_op_t *)malloc(ASCII_SIZE * sizeof(calc_op_t));
	if (NULL != op_lut)
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
   	calc->op_lut[43].presedence = 0;

   	calc->op_lut[40].op_func = &MinusActionFunc;
   	calc->op_lut[40].presedence = 0;

   	return 0;
}



void CalcDestroy(calc_t *calc)
{
	int i = 0;

	assert(calc);

	StackDestroy(calc->num);
	StackDestroy(calc->ops);

	for (i = 0; i < NUM_OF_STATES; ++i)
	{
		FREE(calc->calc_lut[i]);
	}

	FREE(calc->op_lut);
	FREE(calc);
}

state_t CalcRun(const char *expression, calc_t *calc, double *result)
{
	state_t calc_status = WAIT_FOR_NUM;

	assert(expression);
	assert(calc);

	while ('\0' != *expression && ERROR != calc_status)
	{
		result = calc->calc_lut[calc_status][*expression].handler(expression, calc);
		calc_status = calc->calc_lut[calc_status][*expression].next_state;
	}

	return calc_status;
}

