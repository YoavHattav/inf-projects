#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	ERROR
} state_t;

typedef struct State
{
	state_t next_state;
	func_state_t action;
} calc_state_t;

typedef struct Operator
{
	func_op_t op_handler;
	int presedence;
} calc_op_t;

typedef struct Calc
{
	stack_t *num;
	stack_t *ops;
	double *result;
	calc_state_t *calc_lut;
	calc_op_t *op_lut;
} calc_t;

/* Initiates LUT of all ASCII table 
	pointer to calculator struct or NULL for memory fail */
calc_t *CalcInit();

/* free all resorces in use */ 
void CalcDestroy(calc_t *calc);

state_t CalcRun(const char *expression, calc_t *calc);

char *CalcHandleNum(const char *expression, calc_t *calc);

char *CalcHandleOp(const char *expression, calc_t *calc);

#endif
