#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 16

typedef struct ListItem
{
    char word[MAX_LEN];
    struct ListItem *next;
    struct ListItem *prev;
} Word;

typedef struct StackItem
{
    Word *head;
    Word *tail;
    struct StackItem *next;
} Item;

void Push(void);
void Pop(void);
void Input(void);
void Insert(char *value);
void DisplayList(Word *head);
void Sort(Item *ptr);
void ReverseDisplay(Item *ptr);

Item *top = NULL;
Word *res = NULL;
Word *resTail = NULL;

int main()
{
    printf("Enter words, separate lists with .\n");
    Input();
    printf("\nReversed:\n");
    ReverseDisplay(top);
    printf("\nSorted:\n");
    Sort(top);
    DisplayList(res);
    return 0;
}

void Push(void)
{
    Item *p;
    p = (Item *)malloc(sizeof(Item));
    p->head = NULL;
    p->tail = NULL;
    p->next = top;
    top = p;
}

void Pop(void)
{
    Item *p;
    if (top != NULL)
    {
        p = top;
        top = top->next;
        free(p);
    }
}

void Input(void)
{
    char input[MAX_LEN];
    char isLast = '\0';
    Push();
    while(scanf("%16s", input) != EOF)
    {
        if(isalpha(input[0]))
        {
            if(input[strlen(input)-1] == '.')
            {
                input[strlen(input)-1] = '\0';
                isLast = '1';
            }
            Insert(input);
            if(isLast)
            {
                Push();
                isLast = '\0';
            }
        }
    }
}

void Insert(char *value)
{
    Word *p, *cur = top->head;
    p = (Word *)malloc(sizeof(Word));
    strcpy(p->word, value);
    p->next = p->prev = NULL;
    if (top->head == NULL)
    {
        top->head = top->tail = p;
        return;
    }
    top->tail->next = p;
    p->prev = top->tail;
    p->next = NULL;
    top->tail = p;
}

void ReverseDisplay(Item *ptr)
{
    Word *w;
    w = ptr->tail;
    while(w != NULL)
    {
        printf("%s ", w->word);
        w = w->prev;
    }
    if(ptr->next != NULL)
    {
        ReverseDisplay(ptr->next);
    }
}

void Sort(Item *ptr)
{
    Word *w;
    Word *p, *cur = res;
    w = ptr->tail;
    while(w != NULL)
    {
        p = (Word *)malloc(sizeof(Word));
        strcpy(p->word, w->word);
        p->next = p->prev = NULL;
        if (res == NULL)
        {
            res = resTail = p;
            w = w->prev;
            continue;
        }
        while (cur != NULL && strcmp(cur->word, w->word) < 0)
        {
            cur = cur->next;
        }
        if (cur == res)
        {
            p->next = res;
            res->prev = p;
            res = p;
        }
        else if (cur == NULL)
        {
            resTail->next = p;
            p->prev = resTail;
            p->next = NULL;
            resTail = p;
        }
        else
        {
            cur->prev->next = p;
            p->prev = cur->prev;
            cur->prev = p;
            p->next = cur;
        }
        cur = res;
        w = w->prev;
    }
    if(ptr->next != NULL)
    {
       Sort(ptr->next);
    }
}

void DisplayList(Word *head)
{
    Word *w = head;
    FILE *fp = fopen("output.txt", "w");
    if(fp != NULL)
    {
            while (w != NULL)
            {
                printf("%s ", w->word);
                fprintf(fp, "%s ", w->word);
                w = w->next;
            }
            printf("\n\n");
    }
}

