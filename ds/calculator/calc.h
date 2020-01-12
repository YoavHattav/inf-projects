#ifndef __CALC_H__
#define __CALC_H__


typedef struct Calc calc_t;

typedef char *(*func_state_t)(const char *expression, calc_t *calc);
typedef double *(*func_op_t)(double *data1, double *data2);

typedef enum
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	ERROR
} state_t;

/* Initiates LUT of all ASCII table 
	pointer to calculator struct or NULL for memory fail */
calc_t *CalcInit();

/* free all resorces in use */ 
void CalcDestroy(calc_t *calc);

state_t CalcRun(const char *expression, calc_t *calc, double *result);

char *CalcHandleNum(const char *expression, calc_t *calc);

char *CalcHandleOp(const char *expression, calc_t *calc);

#endif
