#include "utilities.h"

#define UNUSED(x) (void)(x)

size_t Hash(const void *data)
{

}

static int Action(void *table_data, void *param)
{
    *(int *)table_data += *(int *)param;
    
    return 0;
}

static int PrintNodes(void *node_data, void *param)
{
    UNUSED(param);
    
    printf("%d\n", *(int *)node_data);
    
    return 0;
}

int IsMatch(const void *user_data, const void *table_data)
{
	return (*user_data == table_data);
}



int main()
{

	return 0;
}
