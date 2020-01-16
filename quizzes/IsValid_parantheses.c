static int IsValidExpression(const char *expression)
{
    const char *runner = NULL;
    char char_holder = 0;
    stack_t *paranth_stack = NULL;
    
    assert(NULL != expression);
    
    paranth_stack = StackCreate(sizeof(char), strlen(expression));
    
    runner = expression;
    while ('\0' != *runner)
    {
        char_holder = *runner;
        if ('(' == char_holder)
        {
            StackPush(paranth_stack, &char_holder);
        }
        
        else if (!StackIsEmpty(paranth_stack) && (')' == char_holder) && 
                ('(' == *(char *)(StackPeek(paranth_stack))))
        {
            StackPop(paranth_stack);
        }
        
        else if (StackIsEmpty(paranth_stack) && (')' == char_holder))
        {
            StackDestroy(paranth_stack); paranth_stack = NULL;
            return 0;
        }
        
        ++runner;
    }
    
    if (StackIsEmpty(paranth_stack))
    {
        StackDestroy(paranth_stack); paranth_stack = NULL;
        return 1;
    }
    
    return 0;
}