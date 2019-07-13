#include <stdio.h>
#include "link.h"

void print_link(link p)
{
    printf("%d \n",p->item);
}

int main(void)
{
    link head,tail,p,squ;
    int i,j,k,g;
    link_init(&head);
    p = make_node(3);
    link_insert(&head,&tail,p);
    p = make_node(1);
    link_insert(&head,&tail,p);
    p = make_node(4);
    link_insert(&head,&tail,p);
    for(i=0;i<3;i++)
    {
        for(squ = head,g = 0;g < 2;squ = squ->next,g++)
        {
//            printf("%d",squ->item);
            if(squ->item > squ->next->item && squ->next != NULL)
            {
                k = squ->item;
                j = squ->next->item;
                squ->next->item = k;
                squ->item = j;
            }
        }
    }
//    printf("%d",head->item);
    link_travel(&head,print_link);
    return 0;
}