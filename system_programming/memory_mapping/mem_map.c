/*********************************/
/*   System Programming          */
/*   vsa                         */
/*   Yoav Hattav                 */
/*   Last Updated 23/12/19       */
/*   Reviewed by: Yonatan        */   
/*********************************/

#include <stddef.h>	/*size_t*/
#include <assert.h> /* assert */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int const_global_var = 4;
int global_var = 5;
static int static_global_bss_var = 0;
static const int static_const_global_var = 2;

static void StaticFunc()
{
    printf("static func \n");
}

extern void ExternFunc()
{
    printf("extern func \n");
}

int main(int argc, char *argv[], char *envp[])
{
    char *heap_ptr = (char *)malloc((sizeof(char) * 46));
    char str_literal[46] = "hey i wanna know how the memory is referenced";
    char *bla = "bla bla";
    const int const_var = 15;
    int nonconst_var = 17;
    static int static_local_var = 7, *ptr_static_local_var = &static_local_var;

    static const int static_const_local_var = 9, *ptr_const_local_var = &static_const_local_var;

    memmove(heap_ptr, str_literal, 46);


    return 0;
}
