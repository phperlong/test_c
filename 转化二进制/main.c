#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    int num;
    scanf("%d",&num);
    int data = 1 << 31;
    if(num < 0)
    {
       num = ~num+1;
       num = num | data;
    }
    for(i=1;i<=32;i++)
    {
        if((num&data) == 0)
            putchar('0');
        else
            putchar('1');
        num <<= 1;
        if(i%4 == 0)
            printf(" ");
    }
    return 0;
}
