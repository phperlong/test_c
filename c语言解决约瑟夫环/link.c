#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "link.h"

static int link_long = 0;
void link_init(link *head)
{
    *head = NULL;
}

link make_node(char str[],int n)
{
    link p = (link)malloc(sizeof(*p));
    p->num = n;
    strcpy(p->word, str);
    p->next = NULL;
    p->pre = NULL;
    return p;
}

void link_insert(link *head,link *tail,link p)
{
    if(*head == NULL)
    {
        *head = p;
        *tail = p;
        return;
    }
    p->next = *head;
    (*head)->pre = p;
    (*head) = p;
    link_long+=1;
}

link link_search(link *head,int key)
{
    link p;
    int i = 0;
    for(p = *head;p != NULL;p = p->next)
    {
        if(p->num == key)
        {
            return p;
        }
    }
    return NULL;
}

void link_delete(link *head,link *tail,link q)
{
    link p;
    if(q == *head)
    {
        *head = q->next;
        (*head)->pre = *tail;
        return;
    }
    if(q == *tail)
    {
        *tail = q->pre;
        (*tail)->next = *head;
        return;
    }
    q->pre->next = q->next;
    q->next->pre = q->pre;
    link_long-=1;
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

void link_compose(link *head,link *tail)
{
    (*head)->pre = *tail;
    (*tail)->next = *head;
}

void link_sort(link *head)
{
    link p,q;
    int num;
    char word[10];
    for(p = *head;p!=NULL;p=p->next)
    {
        if(p->next && p->num < p->next->num)
        {
            num = p->num;
            strcpy(word,p->word);

            p->num = p->next->num;
            strcpy(p->word,p->next->word);

            p->next->num = num;
            strcpy(p->next->word,word);
        }
    }


}

void link_new(link *tail)
{
    link p;
    int i = 0;
    for(p = *tail;link_long > 0 ;p=p->pre,link_long--)
    {
        p->num = (++i);
    }

}
