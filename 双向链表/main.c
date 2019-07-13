#include <stdio.h>
#include "link.h"

void print_link(link p)
{
    printf("%d \n",p->item);
}

int main(void)
{
    link head,p;
    link_init(&head);
    p = make_node(3);
    link_insert(&head,&tail,p);
    p = make_node(4);
    link_insert(&head,&tail,p);
    p = make_node(5);
    link_insert(&head,&tail,p);
    link_travel(&head,print_link);
    return 0;
}