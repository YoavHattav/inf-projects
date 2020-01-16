/*********************************/
/*    Calculator                 */       
/*    Author: Guy Cohen Zedek    */
/*    Reviewed By: Yoav          */
/*    Date:   13/01/2020         */
/*                               */
/*********************************/

#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <math.h>   /* pow    */
#include <assert.h> /* assert */

#include "stack.h"  /* stack functions */

#include "arithmetics.h"

#define UNUSED(x) (void)(x)

#define NUM_OF_STATES    3
#define NUM_OF_OPERATORS 5
#define ASCII_SIZE       256

typedef struct State
{
	state_t next_state;
	func_state_t action;
} calc_state_t;

typedef struct Operator
{
	int presedence;
	func_op_t op_handler;
} calc_op_t;

struct Calculator
{
	stack_t *numbers;
	stack_t *operators;
	double *result;
	calc_state_t *calc_lut;
	calc_op_t *op_lut;
};

static void InitializeOp(calc_op_t *op);
static void InitializeNum(calc_state_t *nums);
static int CalcResult(calc_t *calc);

int IsValidParentheses(const char *expression)
{
    const char *runner = expression;
    char c = 0;
    stack_t *stack = NULL;
    
    assert(NULL != expression);
    
    stack = StackCreate(sizeof(char), strlen(expression));
    
    while ('\0' != *runner)
    {
        c = *runner;
        if ('(' == c)
        {
            StackPush(stack, &c);
        }
        
        else if (!StackIsEmpty(stack) && (')' == c) && 
                ('(' == *(char *)(StackPeek(stack))))
        {
            StackPop(stack);
        }
        
        else if (StackIsEmpty(stack) && (')' == c))
        {
            StackDestroy(stack); stack = NULL;
            return 0;
        }
        
        ++runner;
    }
    
    if (StackIsEmpty(stack))
    {
        StackDestroy(stack); stack = NULL;
        return 1;
    }
    
    return 0;
}

calc_t *CalculatorInit(const char *expression, double *result)
{
    calc_t *calculator = (calc_t *)malloc(sizeof(*calculator));
    if (NULL != calculator)
    {
        calculator->numbers = StackCreate(sizeof(double), strlen(expression));
        if (NULL == calculator->numbers)
        {
            free(calculator); calculator = NULL;
            return NULL;
        }
        
        calculator->operators = StackCreate(sizeof(char), strlen(expression));
        if (NULL == calculator->operators)
        {
            StackDestroy(calculator->numbers); calculator->numbers = NULL;
            free(calculator); calculator = NULL;
            return NULL;
        }
        
        calculator->calc_lut =
               (calc_state_t *)malloc(sizeof(*calculator->calc_lut) * NUM_OF_STATES * ASCII_SIZE);
        if (NULL == calculator->calc_lut)
        {
            StackDestroy(calculator->numbers); calculator->numbers = NULL;
            StackDestroy(calculator->operators); calculator->operators = NULL;
            free(calculator); calculator = NULL;
            return NULL;
        }
        
        calculator->op_lut =
               (calc_op_t *)malloc(sizeof(*calculator->op_lut) * ASCII_SIZE);
        if (NULL == calculator->op_lut)
        {
            StackDestroy(calculator->numbers); calculator->numbers = NULL;
            StackDestroy(calculator->operators); calculator->operators = NULL;
            free(calculator->calc_lut); calculator->calc_lut = NULL; 
            free(calculator); calculator = NULL;
            return NULL;
        }
        
        calculator->result = result;
        
        InitializeNum(calculator->calc_lut);
        InitializeOp(calculator->op_lut);
    }
    
    return calculator;
}

void CalculatorDestroy(calc_t *calculator)
{
    StackDestroy(calculator->numbers); calculator->numbers = NULL;
    StackDestroy(calculator->operators); calculator->operators = NULL;
    free(calculator->calc_lut); calculator->calc_lut = NULL; 
    free(calculator->op_lut); calculator->op_lut = NULL; 
    free(calculator); calculator = NULL;
}

calc_status_t CalculatorRun(const char *expression, calc_t *calc)
{
    calc_status_t status = SUCCESS;
    state_t current_state = WAIT_FOR_NUM;
    const char *runner = expression, *runner2 = NULL;
    int position = 0;
    
    assert(NULL != expression);
    assert(NULL != calc);
    
    while ((ERROR != current_state) && ('\0' != *runner))
    {
        position = *runner + (ASCII_SIZE * current_state);
        runner2 = calc->calc_lut[position].action(runner, calc);
        current_state = calc->calc_lut[position].next_state;
        runner = runner2;
    }
    
    if (ERROR == current_state || WAIT_FOR_NUM == current_state)
    {
        status = SYNTAX_ERROR;
    }
    
    else
    {
        while (!StackIsEmpty(calc->operators) && CalcResult(calc));
        
        *calc->result = *(double *)StackPeek(calc->numbers);
    }
    
    return status;
}

char *CalculatorHandleNum(const char *expression, calc_t *calc)
{
    static double number = 0.0;
    char *runner = (char *)expression;
    
    assert(NULL != expression);
    assert(NULL != calc);
    
    number = strtod(runner, &runner);
        
    if (StackPush(calc->numbers, &number) == 0)
    {
        return NULL;
    }
    
    return (char *)runner;
}

char *CalculatorHandleOp(const char *expression, calc_t *calc)
{
    const char *runner = expression;
    static char c = 0;
    
    assert(NULL != expression);
    assert(NULL != calc);
    
    c = *runner;
    
    if ((!StackIsEmpty(calc->operators)) && 
        (calc->op_lut[(int)c].presedence <= 
         calc->op_lut[(int)(*(char *)StackPeek(calc->operators))].presedence) &&
        (3 != calc->op_lut[(int)c].presedence))
    {
        calc->op_lut[(int)(*(char *)StackPeek(calc->operators))].op_handler(calc);
    }
    
    if (StackPush(calc->operators, &c) == 0)
    {
        return NULL;
    }
    
    return (char *)(++runner);
}

char *CalculatorhandleDummy(const char *expression, calc_t *calc)
{    
    assert(NULL != expression);
    
    UNUSED(calc);
    
    return (char *)(++expression);
}

char *CalculatorhandleReduce(const char *expression, calc_t *calc)
{
    const char *runner = expression;
    
    assert(NULL != expression);
    assert(NULL != calc);
    
    if ((!StackIsEmpty(calc->operators) && (0 == CalcResult(calc))) ||
        ('\0' == *runner))
    {
        return NULL;
    }
    
    return (char *)(++runner);
}

static int CalcResult(calc_t *calc)
{
    char op = 0;
    
    assert(NULL != calc);
    
    op = *(char *)StackPeek(calc->operators);
    
    if (1 < StackSize(calc->numbers))
    {
        return calc->op_lut[(int)op].op_handler(calc);
    }
    
    return 0;
}

static int Add(calc_t *calculator)
{
    double num1 = 0.0, num2 = 0.0;
    
    assert (NULL != calculator);
    
    num1 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);

    num2 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);
    
    num2 += num1;
    
    StackPop(calculator->operators);
    
    return (StackPush(calculator->numbers, &num2) != 0);
}

static int Sub(calc_t *calculator)
{
    double num1 = 0.0, num2 = 0.0;
    
    assert (NULL != calculator);
    
    num1 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);

    num2 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);
    
    num2 -= num1;
    
    StackPop(calculator->operators);
    
    return (StackPush(calculator->numbers, &num2) != 0);
}

static int Mult(calc_t *calculator)
{
    double num1 = 0.0, num2 = 0.0;
    
    assert (NULL != calculator);
    
    num1 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);

    num2 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);
    
    num2 *= num1;
    
    StackPop(calculator->operators);
    
    return (StackPush(calculator->numbers, &num2) != 0);
}

static int Div(calc_t *calculator)
{
    double num1 = 0.0, num2 = 0.0;
    
    assert (NULL != calculator);
    
    num1 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);

    num2 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);
    
    num2 /= num1;
    
    StackPop(calculator->operators);
    
    return (StackPush(calculator->numbers, &num2) != 0);
}

static int Pow(calc_t *calculator)
{
    double num1 = 0.0, num2 = 0.0;
    
    assert (NULL != calculator);
    
    num1 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);

    num2 = *(double *)StackPeek(calculator->numbers);
    StackPop(calculator->numbers);
    
    num2 = pow(num2, num1);
    
    StackPop(calculator->operators);
    
    return (StackPush(calculator->numbers, &num2) != 0);
}

static int ErrorOp(calc_t *calc)
{
    UNUSED(calc);
    
    return 1;
}

static void InitializeNum(calc_state_t *nums)
{
    int i = 0;
    
    assert(NULL != nums);
    
    for (i = 0; i < (NUM_OF_STATES * ASCII_SIZE); ++i)
    {
        nums[i].next_state = ERROR;
        nums[i].action = &CalculatorhandleDummy;
    }
    
    for ( i = '0'; i <= '9'; ++i)
    {
        nums[i].next_state = WAIT_FOR_OP;
        nums[i].action = &CalculatorHandleNum;
    }
    
    nums['.'].next_state = WAIT_FOR_OP;
    nums['.'].action = &CalculatorHandleNum;
    
    nums['+'].next_state = WAIT_FOR_OP;
    nums['+'].action = &CalculatorHandleNum;
    
    nums['-'].next_state = WAIT_FOR_OP;
    nums['-'].action = &CalculatorHandleNum;
    
    nums[' '].next_state = WAIT_FOR_OP;
    nums[' '].action = &CalculatorHandleNum;
    
    nums['('].next_state = WAIT_FOR_NUM;
    nums['('].action = &CalculatorhandleDummy;
    
    nums['+' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    nums['+' + ASCII_SIZE].action = &CalculatorHandleOp;
    
    nums['-' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    nums['-' + ASCII_SIZE].action = &CalculatorHandleOp;
    
    nums['*' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    nums['*' + ASCII_SIZE].action = &CalculatorHandleOp;
    
    nums['/' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    nums['/' + ASCII_SIZE].action = &CalculatorHandleOp;
    
    nums['^' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    nums['^' + ASCII_SIZE].action = &CalculatorHandleOp;
    
    nums[')' + ASCII_SIZE].next_state = WAIT_FOR_OP;
    nums[')' + ASCII_SIZE].action = &CalculatorhandleReduce;

    nums[' ' + ASCII_SIZE].next_state = WAIT_FOR_OP;
    nums[' ' + ASCII_SIZE].action = &CalculatorhandleDummy;
}

static void InitializeOp(calc_op_t *op)
{
    int i = 0;
    
    assert(NULL != op);
    
    for (i = 0; i < ASCII_SIZE; ++i)
    {
        op[i].presedence = 0;
        op[i].op_handler = &ErrorOp;
    }
    
    op['+'].presedence = 1;
    op['+'].op_handler = &Add;
    
    op['-'].presedence = 1;
    op['-'].op_handler = &Sub;
    
    op['*'].presedence = 2;
    op['*'].op_handler = &Mult;
    
    op['/'].presedence = 2;
    op['/'].op_handler = &Div;
    
    op['^'].presedence = 3;
    op['^'].op_handler = &Pow;
}
