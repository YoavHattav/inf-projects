#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include "calculator.h"

typedef enum States
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	ERROR
} state_t;

typedef struct Calculator calc_t;

typedef char* (*func_state_t)(const char *expression, calc_t *calculator);
typedef int (*func_op_t)(calc_t *calculator);

/* Initialize LUT of all ASCII table and Operators LUT
   Returns a pointer to calculator struct or NULL for memory fail */
calc_t *CalculatorInit(const char *expression, double *result);

/* free all resorces in use */ 
void CalculatorDestroy(calc_t *calc);

/* Gets an expression and pointer to calculator 
   Returns if the calculate succeed/syntax error/memory fail */
calc_status_t CalculatorRun(const char *expression, calc_t *calc);

/* Gets an expression and pointer to calculator 
   Active the correct operations to handle the current number in the expression
   Returns the promoted expression */
char *CalculatorHandleNum(const char *expression, calc_t *calc);

/* Gets an expression and pointer to calculator 
   Active the correct operations to handle the current operator in the expression
   Returns the promoted expression */
char *CalculatorHandleOp(const char *expression, calc_t *calc);

/* Gets an expression and pointer to calculator 
   Active the correct operations to handle the current character in the expression
   Returns the promoted expression */
char *CalculatorhandleDummy(const char *expression, calc_t *calc);

/* Gets an expression 
   Returns 1 - if the expression has valid parentheses , otherwise: 0*/
int IsValidParentheses(const char *expression);

#endif
