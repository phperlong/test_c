#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

void print_link(link p)
{
    printf("%d %s\n",p->num,p->word);
}
void calc(link *head,link *tail,link p,int j)
{
        int l = j,i=0;
        for(;l>=0,*head != *tail;p = p->pre,l--)
        {
            if(l == 0)
            {
                link_delete(&(*head),&(*tail),p);
                calc(&(*head),&(*tail),p->pre,j);
            }
        }

}

int main()
{
    int i,j = 0,k = 5;
    char s[20];
    link head,p,tail,q;

//    printf("请输入注册人数 大于0 或小于10\n");
//    gets(s);
//    i = atoi(s);
//    if(i<=0 || i>10)
//    {
//       printf("输入的数据有误 退出程序");
//       return 0;
//    }

    link_init(&head);
    printf("input your input num name\n");
    for(j = 1;j <= 5;j++)
    {
        scanf("%s",&s);
        p = make_node(s,j);
        link_insert(&head,&tail,p);
    }
    link_compose(&head,&tail);
    printf("game start , input what num start\n");
    scanf("%d",&i);
    printf("input what run num\n");
    scanf("%d",&j);
    p = link_search(&head,i);
    calc(&head,&tail,p,j);
    printf("%s %d",head->word,head->num);
    return 0;
}