#ifndef __LINK__
#define __LINK__
typedef struct wordcal *link;
struct wordcal
{
    char word[10];
    int num;
    link next;
    link pre;
};
void link_init(link *head);
link make_node(char str[],int j);
void link_insert(link *head,link *tail,link p);
link link_search(link *head,int key);
void link_delete(link *head,link *tail,link q);
void link_destory(link *head);
void link_sort(link *head);
void link_compose(link *head,link *tail);
void link_travel(link *head,void(*vist)(link));
void link_new(link *tail);
#endif