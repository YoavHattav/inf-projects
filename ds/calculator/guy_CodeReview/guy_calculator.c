/*********************************/
/*    Calculator                 */       
/*    Author: Guy Cohen Zedek    */
/*    Reviewed By: Yoav          */
/*    Date:   13/01/2020         */
/*                               */
/*********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* NULL */

#include "arithmetics.h"
#include "calculator.h"

calc_status_t Calculator(const char *expression, double *result)
{
    calc_t *calculator = NULL;
    const char *runner = expression;
    calc_status_t current_status = SUCCESS;
    
    assert(NULL != expression);
    assert(NULL != result);
    
    if(!IsValidParentheses(expression))
    {
        current_status = SYNTAX_ERROR;
    }
    
    else
    {
        calculator = CalculatorInit(runner, result);
        if (NULL == calculator)
        {
            return MEMORY_FAIL;
        }
        
        current_status = CalculatorRun(runner, calculator);
        
        CalculatorDestroy(calculator);
    }
    
    return current_status;
}
