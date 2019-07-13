#include <stdio.h>
#include <stdlib.h>

static int sz = 512;
static char *stack;
static int top = 0;
void init_stack(int size)
{
    if(size == 0)
        size = sz
        sz = size;
    stack = (char *)malloc(sz);
}

void free_stack(void)
{
    free(stack);
}

void push(char ch)
{
    if(top == sz)
    {
        sz+=sz;
        stack = realloc(stack,sz);
    }
    stack[top++] = ch;
}

char pop(void)
{
    return stack[--top];
}

int is_empty(void)
{
    return top == 0;
}

int is_full(void)
{
    return top == sz;
}



