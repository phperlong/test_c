#include <stdio.h>
#include <malloc.h>
#include "link.h"

void link_init(link *head)
{
    *head = NULL;
}

link make_node(int item)
{
    link p = (link)malloc(sizeof(*p));
    p->item = item;
    p->next = NULL;
    return p;
}

void link_insert(link *head,link p)
{
    p->next = *head;
    *head = p;
}

link link_search(link *head, int key)
{
    link p;
    for(p = *head;p != NULL;p = p->next)
        if(p->item == key)
            return p;
    return NULL;
}

void link_delete(link *head,link q)
{
    link p;
    if(q == *head)
    {
        *head = q->next;
        return;
    }
    for(p = *head;p != NULL;p = p->next)
    {
        if(q == p->next)
        {
            p->next = q->next;
            return;
        }
    }
}

void link_modfie(link p, int key)
{
    p->item = key;
}

void link_destory(link *head)
{
    link p = *head,q;
    while(p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    *head = NULL;
}


void link_travel(link *head,void(*vist)(link))
{
    link p;
    for(p = *head;p!=NULL;p=p->next)
        vist(p);
}
