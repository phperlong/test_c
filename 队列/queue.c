#include <stdio.h>

//入队游标f 出队游标r 存储空间512
static int f = 0,r = 0,sz = 512;
//队内存储空间
static int queue[512];

//入队
void enqueue(int item)
{
    f %= sz;
    queue[f++] = item;
}
//出队
int dequeue(void)
{
    r %= sz;
    return queue[r++];
}
//判断是否为空
int is_empty(void)
{
    return r == f;
}
//判断时候满员
int is_full(void)
{
    return (r+1)%sz == f;
}





