#ifndef __LINK_H__
#define __LINK_H__
typedef struct node *link;
struct node
{
    int item;
    link next;
    link pre;
};
void link_init(link *head);
link make_node(int item);
void link_insert(link *head,link *tail,link p);
link link_search(link *head,int key);
void link_delete(link *head,link *tail,link q);
void link_modfie(link p,int key);
void link_destory(link *head,link *tail);
void link_travel(link *head,void(*vist)(link));
#endif
