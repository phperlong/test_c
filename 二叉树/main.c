#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
struct tnode *talloc(void);
char *sstrdup(char *);
struct tnode *addtree(struct tnode *,char *);
void treeprint(struct tnode *);
int getword(char *,int);

int main()
{
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while(getword(word,MAXWORD) != EOF)
        if(isalpha(word[0]))
        {
           root = addtree(root,word);
        }

    treeprint(root);
    return 0;
}



struct tnode *addtree(struct tnode *p,char *w)
{
    int cond;
    if(p == NULL)
    {
        p = talloc();
        p->word = sstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }else if((cond = strcmp(w,p->word)) == 0){
        p->count++;
    }else if(cond < 0)
        p->left = addtree(p->left,w);
     else
        p->right = addtree(p->right,w);
     return p;
}

int getword(char *word,int lim)
{
    int c,getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace((c = getch())))
        ;
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c)){
        *w = '\0';
        return c;
    }
    for (;--lim>0;w++)
        if(!isalnum(*w = getch())){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
};

char buf[MAXWORD];
int bufp = 0;
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    buf[bufp++] = c;
}

void treeprint(struct tnode *p)
{
    if( p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n",p->count,p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *sstrdup(char *s)
{
    char *p = (char *)malloc(strlen(s)+1);
    if(p != NULL)
        strcpy(p,s);
    return p;
}
























































