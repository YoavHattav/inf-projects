/*********************************/
/*   calculator                  */
/*   Yoav Hattav                 */
/*   Last Updated 14/01/20       */
/*   Reviewed by:   Israel       */
/*********************************/

#include <assert.h> /*assert*/
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */ 

#include "arithmetics.h" /* arithmetics functions */ 
#include "calculator.h" /* API */
#include "stack.h" /* stack DS usage */ 

#define FREE(ptr) free(ptr); ptr = NULL;
#define ASCII_SIZE 256
#define NUM_OF_STATES 2

static int LUTInit(calc_t *calc);

typedef enum
{
	PARENTHE,
	PLUS,
	MULTI,
	POW
}presedence_t;

typedef struct State
{
	state_t next_state;
	func_state_t handler;
}calc_state_t;

typedef struct Operator
{
	func_op_t op_func;
	presedence_t presedence;
}calc_op_t;

struct Calc
{
	stack_t *num_stack;
	stack_t *op_stack;
	stack_t *paranth_stack;
	double *result;
	calc_state_t **calc_lut;
	calc_op_t *op_lut;
};

char *DummyHandlerNumFunc(const char *expression, 
	calc_t *calc){UNUSED(calc);return (char *)expression;}
char *DummyHandlerOPFunc(const char *expression, 
	calc_t *calc){UNUSED(calc);return (char *)expression;}
double DummyActionFunc(double *data1, double *data2)
{UNUSED(data1);UNUSED(data2); return 0;}

static char *SpaceAdvancer(const char *expression, calc_t *calc)
{
	UNUSED(calc);
	++expression;
	return (char*)expression;
}

calc_status_t Calculator(const char *expression, double *result)
{
	calc_t *calc =  NULL;
	state_t status = 0;

	assert(NULL != expression);

	calc = CalcInit(expression, result);

	status = CalcRun(expression, calc);

	*result = *(double *)StackPeek(calc->num_stack);

	CalcDestroy(calc);

	return status;
}

static char *CalcHandleNum(const char *expression, calc_t *calc)
{
	static double buffer = 0;
	char *cal_runner = NULL;

	assert(NULL != expression);
	assert(NULL != calc);

	cal_runner = (char *)expression;

	buffer = strtod(expression, &cal_runner);

	if (0 == StackPush(calc->num_stack, &buffer))
	{
		return NULL;
	}
	return cal_runner;
}

static int SmallScaleCalc(calc_t *calc)
{
	double first_pop_data2 = 0, second_pop_data1 = 0, res_holder = 0;
	char *op_holder = NULL;

	assert(NULL != calc);

	op_holder = (char *)StackPeek(calc->op_stack);
	StackPop(calc->op_stack);

	first_pop_data2 = *(double *)StackPeek(calc->num_stack);
	StackPop(calc->num_stack);

	second_pop_data1 = *(double *)StackPeek(calc->num_stack);
	StackPop(calc->num_stack);

	res_holder = calc->op_lut[(int)*op_holder].op_func(&second_pop_data1, &first_pop_data2);
	
	return StackPush(calc->num_stack, &res_holder);
}

static char *CalcHandleParentheses(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	static char char_holder = 0;

	assert(NULL != expression);
	assert(NULL != calc);

	runner = (char *)expression;
	char_holder = *runner;

	if (char_holder == '(')
	{
		StackPush(calc->paranth_stack, &char_holder);
		StackPush(calc->op_stack, &char_holder);

		++runner;
		return runner;
	}

	else 
	{
		if (StackIsEmpty(calc->paranth_stack))
		{
			return NULL; 
		}

		while (*(char *)StackPeek(calc->op_stack) != '(')
		{
			SmallScaleCalc(calc);
		}
		StackPop(calc->paranth_stack);
		StackPop(calc->op_stack);
		++runner;

		return runner;
	}
}

static char *CalcHandleOp(const char *expression, calc_t *calc)
{
	char *runner = NULL;
	static char char_holder = 0;

	assert(NULL != expression);
	assert(NULL != calc);

	runner = (char *)expression;
	char_holder = *runner;

	if (StackIsEmpty(calc->op_stack))
	{
		StackPush(calc->op_stack, &char_holder);
		++runner;
	}

	else if ( '^' == char_holder)
	{
		StackPush(calc->op_stack, &char_holder);
		++runner;
	}

	else
	{
		while (!StackIsEmpty(calc->op_stack) && calc->op_lut[char_holder].presedence <= 
						calc->op_lut[*(char *)StackPeek(calc->op_stack)].presedence)
		{
			SmallScaleCalc(calc);
		}
		StackPush(calc->op_stack, &char_holder);
		++runner;
	}

	return runner;
}

calc_t *CalcInit(const char *expression, double *result)
{
	size_t len = 0;
	calc_t *new_calc = NULL;

	new_calc = (calc_t *)malloc(sizeof(calc_t));
	if (NULL == new_calc)
	{
		return NULL;
	}

	len = strlen(expression);

	new_calc->num_stack = StackCreate(sizeof(double), len);
	if (NULL == new_calc->num_stack)
	{
		FREE(new_calc);
		return NULL;

	}

	new_calc->op_stack = StackCreate(sizeof(char), len);
	if (NULL == new_calc->op_stack)
	{
		StackDestroy(new_calc->num_stack);new_calc->num_stack = NULL;
		FREE(new_calc);
		return NULL;

	}

	new_calc->paranth_stack = StackCreate(sizeof(char), len);
	if (NULL == new_calc->paranth_stack)
	{
		StackDestroy(new_calc->num_stack);new_calc->num_stack = NULL;
		StackDestroy(new_calc->op_stack);new_calc->op_stack = NULL;
		FREE(new_calc);
		return NULL;		
	}

	LUTInit(new_calc);

	new_calc->result = result;

	return new_calc;
}

static int LUTInit(calc_t *calc)
{
	int i = 0; 
  
    calc_state_t **calc_lut = (calc_state_t **)malloc(NUM_OF_STATES * sizeof(calc_state_t *));
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
        	return MEMORY_FAIL;
        } 
    }
  
   	calc->calc_lut = calc_lut;

   	for (i = 0; i < ASCII_SIZE; ++i)
   	{
   		calc->calc_lut[WAIT_FOR_NUM][i].next_state = ERROR;
   		calc->calc_lut[WAIT_FOR_NUM][i].handler = &DummyHandlerNumFunc;
   	}
   	for (i = '0'; i <= '9'; ++i)
   	{
   		calc->calc_lut[WAIT_FOR_NUM][i].next_state = WAIT_FOR_OP;
   		calc->calc_lut[WAIT_FOR_NUM][i].handler = &CalcHandleNum;
   	}

   	calc->calc_lut[WAIT_FOR_NUM][' '].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM][' '].handler = &CalcHandleNum;

   	calc->calc_lut[WAIT_FOR_NUM]['+'].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM]['+'].handler = &CalcHandleNum;

	calc->calc_lut[WAIT_FOR_NUM]['-'].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM]['-'].handler = &CalcHandleNum;

   	calc->calc_lut[WAIT_FOR_NUM]['.'].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_NUM]['.'].handler = &CalcHandleNum;

   	calc->calc_lut[WAIT_FOR_NUM]['('].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_NUM]['('].handler = &CalcHandleParentheses;
   	
   	calc->calc_lut[WAIT_FOR_NUM][')'].next_state = ERROR;
   	calc->calc_lut[WAIT_FOR_NUM][')'].handler = &DummyHandlerNumFunc;
 	
   	for (i = 0; i < ASCII_SIZE; ++i)
   	{
   		calc->calc_lut[WAIT_FOR_OP][i].next_state = ERROR;
   		calc->calc_lut[WAIT_FOR_OP][i].handler = &DummyHandlerOPFunc;
   	}

   	calc->calc_lut[WAIT_FOR_OP][' '].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_OP][' '].handler = &SpaceAdvancer;

   	calc->calc_lut[WAIT_FOR_OP]['+'].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP]['+'].handler = &CalcHandleOp;

	calc->calc_lut[WAIT_FOR_OP]['-'].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP]['-'].handler = &CalcHandleOp;

   	calc->calc_lut[WAIT_FOR_OP]['*'].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP]['*'].handler = &CalcHandleOp;

   	calc->calc_lut[WAIT_FOR_OP]['/'].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP]['/'].handler = &CalcHandleOp;

   	calc->calc_lut[WAIT_FOR_OP]['^'].next_state = WAIT_FOR_NUM;
   	calc->calc_lut[WAIT_FOR_OP]['^'].handler = &CalcHandleOp;
   	
   	calc->calc_lut[WAIT_FOR_OP]['('].next_state = ERROR;
   	calc->calc_lut[WAIT_FOR_OP]['('].handler = &CalcHandleOp;

   	calc->calc_lut[WAIT_FOR_OP][')'].next_state = WAIT_FOR_OP;
   	calc->calc_lut[WAIT_FOR_OP][')'].handler = &CalcHandleParentheses;

	op_lut = (calc_op_t *)malloc(ASCII_SIZE * sizeof(calc_op_t));
	if (NULL == op_lut)
	{
		return ERROR;
	}
    calc->op_lut = op_lut;

   	for (i = 0; i < ASCII_SIZE; ++i)
   	{
   		calc->op_lut[i].op_func = &DummyActionFunc;
   		calc->op_lut[i].presedence = 0;
   	}

   	calc->op_lut['+'].op_func = &PlusActionFunc;
   	calc->op_lut['+'].presedence = PLUS;

   	calc->op_lut['-'].op_func = &MinusActionFunc;
   	calc->op_lut['-'].presedence = PLUS;

   	calc->op_lut['*'].op_func = &MultiActionFunc;
   	calc->op_lut['*'].presedence = MULTI;

   	calc->op_lut['/'].op_func = &DivideActionFunc;
   	calc->op_lut['/'].presedence = MULTI;

   	calc->op_lut['^'].op_func = &POWActionFunc;
   	calc->op_lut['^'].presedence = POW;

   	calc->op_lut['('].op_func = &DummyActionFunc;
   	calc->op_lut['('].presedence = PARENTHE;

   	calc->op_lut[')'].op_func = &DummyActionFunc;
   	calc->op_lut[')'].presedence = PARENTHE;

   	return 0;
}

void CalcDestroy(calc_t *calc)
{
	int i = 0;

	assert(calc);

	StackDestroy(calc->num_stack);calc->num_stack = NULL;
	StackDestroy(calc->op_stack);calc->op_stack = NULL;
	StackDestroy(calc->paranth_stack);calc->paranth_stack = NULL;

	for (i = 0; i < NUM_OF_STATES; ++i)
	{
		FREE(calc->calc_lut[i]);
	}

	FREE(calc->calc_lut);
	FREE(calc->op_lut);
	FREE(calc);
}

calc_status_t CalcRun(const char *expression, calc_t *calc)
{
	state_t calc_status = WAIT_FOR_NUM;
	const char *runner = NULL;

	assert(NULL != expression);
	assert(NULL != calc);

	runner = expression;

	while (ERROR != calc_status && runner != NULL && '\0' != *runner)
	{
		char runner_holder = *runner;

		runner = calc->calc_lut[calc_status][runner_holder].handler(runner, calc);
		calc_status = calc->calc_lut[calc_status][runner_holder].next_state;
	}

	if (ERROR == calc_status || WAIT_FOR_NUM == calc_status || runner == NULL)
    {
        return SYNTAX_ERROR;
    }

	while (1 < StackSize(calc->num_stack))
	{
		SmallScaleCalc(calc);
	}
		
	return calc_status;
}

