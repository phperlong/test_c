#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


int reversed_cal(char *s)
{
    int a,b,res;
    char *p = s;
    if(s == NULL)
        return 0;

    p = strtok(s," ");
    push(atoi(p));
    while((p = strtok(NULL," ")) != NULL)
    {
        switch(*p)
        {
            case '+':b=pop();a=pop();res=a+b;push(res);break;
            case '-':b=pop();a=pop();res=a-b;push(res);break;
            case '*':b=pop();a=pop();res=a*b;push(res);break;
            case '/':b=pop();a=pop();res=a/b;push(res);break;
            default: push(atoi(p));
        }
    }
    return pop();
 }

int main(void)
{
    int res;
    char str[] = "64 4 + 2 / 3 *";
    init_stack(100);
    res = reversed_cal(str);
    printf("%d \n",res);
    free_stack();
    return 0;
}

