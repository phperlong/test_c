#include <stdio.h>
#include "queue.h"

int main()
{
    char *s = "abcd";
    while(*s != '\0')
        enqueue(*s++);
    while(!is_empty())
        putchar(dequeue());
    putchar('\n');
    return 0;
}