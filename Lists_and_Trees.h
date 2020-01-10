#ifndef LISTS_AND_TREES_HEADER_H_INCLUDED

#define LISTS_AND_TREES_HEADER_H_INCLUDED

struct node
{
    struct node* left;
    struct node* right;
    int data;
    int height;
};

struct list_node
{
    int data;
    struct list_node* next;
    struct list_node* prev;
};

int mymax(int a, int b);

int height(struct node* n1);

struct node* rebalance(struct node* tree);

int avlmax(struct node* n1);

int avlmin(struct node* n1);

struct node* deleteavl(int n, struct node* n1);

struct node* insertavl(int n, struct node* tree);

void printnode(struct node* tree);

void print_list(struct list_node* n1);

struct list_node* build_node(int n);

struct list_node* append(struct list_node* n1, struct list_node* n2);

struct list_node* Tree_to_List(struct node* n1);

struct list_node* buildlist(int n);


int length(struct list_node* list1);

void freelist(struct list_node* list1); 

struct list_node* split(struct list_node* head);

struct list_node* cdr(struct list_node* list_node);

struct list_node* car(struct list_node* list_node);

struct list_node* list_merge(struct list_node* sorted_list1, struct list_node* sorted_list2);

struct list_node* mergesort(struct list_node* head);

struct list_node* map(struct list_node* (*func)(struct list_node*), struct list_node* list);

int listproduct(struct list_node* list1);

struct list_node* remove_duplicates(struct list_node* list1);

#endif // LISTS_AND_TREES_HEADER_H_INCLUDED
