#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

typedef void (*Func)(int param);

struct node
{
    struct node* left;
    struct node* right;
    int data;
    int height;
};

int mymax(int a, int b)
{
    if (a < b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int height(struct node* n1)
{
    if (n1 == NULL)
    {
        return 0;
    }
    else
    {
        return n1->height;
    }
};

struct node* sub_left(struct node* tree, struct node* subtree)
{
    tree->left = subtree;
    tree->height = 1 + mymax(height(tree->left), height(tree->right));
    return tree;
}

struct node* sub_right(struct node* tree, struct node* subtree)
{
    tree->right = subtree;
    tree->height = 1 + mymax(height(tree->left), height(tree->right));
    return tree;
}

struct node* raise_left(struct node* tree)
{
    struct node* tt;
    struct node* ttt;
    tt = tree->left;
    ttt = tt->right;
    sub_left(tree, ttt);
    sub_right(tt, tree);
    return tt;
}

struct node* raise_right(struct node* tree)
{
    struct node* tt;
    struct node* ttt;
    tt = tree->right;
    ttt = tt->left;
    sub_right(tree, ttt);
    sub_left(tt, tree);
    return tt;
}

struct node* rebalance(struct node* tree)
{
    if (NULL == tree)
    {
        return NULL;
    }
    else if (height(tree->left) > height(tree->right) + 1)
    {
        if (height((tree->left)->left) > height((tree->left)->right))
        {
            return raise_left(tree);
        }
        else
        {
            tree->left = raise_right(tree->left);
            return raise_left(tree);
        }
    }

    else if (height(tree->right) > height(tree->left) + 1)
    {
        if (height((tree->right)->right) > height((tree->right)->left))
        {
            return raise_right(tree);
        }
        else
        {
            tree->right = raise_left(tree->right);
            return raise_right(tree);
        }
    }
    else return tree;
}

int avlmax(struct node* n1)
{
    struct node* step = n1;

    while (step->right != NULL)
    {
        step = step->right;
    }

    return step->data;
}

int avlmin(struct node* n1)
{
    struct node* step = n1;

    while (step->left != NULL)
    {
        step = step->left;
    }

    return step->data;
}

struct node* deleteavl(int n, struct node* n1)
{
    if (n1 == NULL)
    {
        return NULL;
    }
    else if (n1->data == n)
    {
        if (n1->right == NULL)
        {
            return rebalance(n1->left);
        }
        else if (n1->left == NULL)
        {
            return rebalance(n1->right);
        }
        else
        {
            struct node* step1 = n1->right;
            while (step1->left != NULL)
            {
                step1 = step1->left;
            }

            deleteavl(step1->data, n1->right);

            sub_right(step1, n1->right);
            sub_left(step1, n1->left);

            return (step1);
        }
    }
    else if (n1->data > n)
    {
        return rebalance(sub_left(n1, deleteavl(n, n1->left)));
    }
    else
    {
        return rebalance(sub_right(n1, deleteavl(n, n1->right)));
    }
}

struct node* insertavl(int n, struct node* tree)
{
    struct node* tt;
    tt = (struct node*)malloc(sizeof(struct node));
    tt->left = NULL;
    tt->right = NULL;
    tt->data = n;
    tt->height = 1;

    if (NULL == tree)
    {
        return NULL;
    }
    else if (n == tree->data)
    {
        printf("The value is already present withing the tree \n");
        return tree;
    }
    else if (n > tree->data)
    {
        if (tree->right == NULL)
        {
            sub_right(tree, tt);
            return tree;
        }
        else
        {
            return rebalance(sub_right(tree, (insertavl(n, tree->right))));
        }
    }
    else
    {
        if (tree->left == NULL)
        {
            sub_left(tree, tt);
            return tree;
        }
        else
        {
            return rebalance(sub_left(tree, (insertavl(n, tree->left))));
        }
    }
}

void printnode(struct node* tree)
{
    printf("Data: %d \nHeight: %d \n", tree->data, tree->height);
}

int fib(int n)
{
    int a;
    int b;
    int c;

    a = 1;
    b = 2;

    if (n == 1)
    {
        return 1;
    }
    else
    {
        while (n > 2)
        {
            c = a + b;
            a = b;
            b = c;

            --n;
        }
        return b;
    }
}

struct list_node
{
    int data;
    struct list_node* next;
    struct list_node* prev;
};

struct list_node* append(struct list_node* n1, struct list_node* n2)
{
    if (NULL == n1)
    {
        return n2;
    }
    else if (NULL == n2)
    {
        return n1;
    }
    else
    {
        struct list_node* list1_end;
        list1_end = n1->prev;

        struct list_node* list2_end;
        list2_end = n2->prev;

        (n2->prev)->next = n1;

        (n1->prev)->next = n2;

        n2->prev = list1_end;
        n1->prev = list2_end;

        return n1;
    }
}

struct list_node* Tree_to_List(struct node* n1)
{
    struct list_node* newnode;

    newnode = (struct list_node*)calloc(1, sizeof(struct list_node));

    if (n1 == NULL)
    {
        return NULL;
    }
    else
    {
        struct list_node* final_list;
        final_list = (struct list_node*)calloc(1, sizeof(struct list_node));

        newnode->data = n1->data;
        newnode->next = newnode;
        newnode->prev = newnode;
        final_list = append(Tree_to_List(n1->left), append(newnode, Tree_to_List(n1->right)));

        return final_list;
    }
}

void print_list(struct list_node* n1)
{
    if (!n1)
    {
        printf("The list is empty. \n");
    }
    else
    {
        struct list_node* n2;
        n2 = n1;

        {
            while (n2->next != n1)
            {
                printf("%d \n", n2->data);

                n2 = n2->next;
            }
        }
        printf("%d \n", n2->data);
    }
}

struct list_node* buildlist(int n)
{
    struct list_node* accumulator;
    struct list_node* temp;
    int placeholder = 0;
    accumulator = NULL;

    for (; n > 0; --n)
    {
        temp = (struct list_node*)malloc(sizeof(struct list_node));

        temp->data = placeholder;
        temp->next = temp;
        temp->prev = temp;

        accumulator = append(accumulator, temp);

        ++placeholder;
    }

    return accumulator;
}


int length(struct list_node* list1)
{
    if (list1 == NULL)
    {
        return 0;
    }
    else
    {
        struct list_node* step = list1;
        int acc = 1;

        while (step->next != list1)
        {
            ++acc;
            step = step->next;
        }

        return acc;
    }
}

struct list_node* split(struct list_node* head)
{
    struct list_node* fast = head;
    struct list_node* slow = head;
    while ((fast->next != head) && (fast->next->next != head))
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct list_node* temp = slow->next;
    struct list_node* temp2 = head->prev;

    slow->next = head;
    head->prev = slow;

    temp->prev = temp2;
    temp2->next = temp;

    return temp;
}

struct list_node* cdr(struct list_node* list_node)
{
    if (list_node == NULL)
    {
        return NULL;
    }
    else if (list_node->next == list_node)
    {
        return NULL;
    }
    else
    {
        list_node->next->prev = list_node->prev;
        list_node->prev->next = list_node->next;
        return list_node->next;
    }
}

struct list_node* car(struct list_node* list_node)
{
    if (list_node == NULL)
    {
        return NULL;
    }
    else
    {
        list_node->prev = list_node;
        list_node->next = list_node;
        return list_node;
    }
}

struct list_node* list_merge(struct list_node* sorted_list1, struct list_node* sorted_list2)
{
    struct list_node* acc = NULL;
    struct list_node* temp1;

    while ((sorted_list1 != NULL) && (sorted_list2 != NULL))
    {
        if (sorted_list1->data > sorted_list2->data)
        {
            temp1 = sorted_list2;
            sorted_list2 = cdr(sorted_list2);
            temp1->next = temp1;
            temp1->prev = temp1;

            acc = append(acc, temp1);
        }
        else
        {
            temp1 = sorted_list1;
            sorted_list1 = cdr(sorted_list1);
            temp1->next = temp1;
            temp1->prev = temp1;

            acc = append(acc, temp1);
        }
    }

    if (sorted_list1 == NULL)
    {
        return append(acc, sorted_list2);
    }
    else
    {
        return append(acc, sorted_list1);
    }
}

struct list_node* mergesort(struct list_node* head)
{
    if (head == NULL || head->next == head)
    {
        return head;
    }
    else
    {
        struct list_node* second;
        second = split(head);

        head = mergesort(head);
        second = mergesort(second);

        return list_merge(head, second);
    }
}

struct list_node* map(struct list_node* (*func)(struct list_node*), struct list_node* list)
{
    if (list == NULL)
    {
        return NULL;
    }
    else if (list->next == list)
    {
        return (func(list));
    }
    else
    {
        return append(func(car(list)), map(*func, cdr(list)));
    }
}

struct list_node* build_node(int n)
{
    struct list_node* ptr; ptr = (struct list_node*)malloc(sizeof(struct list_node));

    ptr->data = n;
    ptr->prev = ptr;
    ptr->next = ptr;

    return ptr;
}

void freelist(struct list_node* list1)
{
    struct list_node* temp = list1;
    struct list_node* temp2;
    while (temp->next != temp)
    {
        temp2 = temp;
        temp = cdr(temp);
        free(temp2);
    }
    free(temp);
}

struct list_node* remove_duplicates(struct list_node* list1)
{
    struct list_node* accumulator = NULL;
    struct list_node* step;
    step = list1;

    while (step->next != list1)
    {
        if (step->data == step->next->data)
        {
            step = step->next;
        }
        else
        {
            accumulator = append(accumulator, build_node(step->data));
            step = step->next;
        }
    }

    accumulator = append(accumulator, build_node(step->data));
    return accumulator;
}

int listproduct(struct list_node* list1)
{
    int accumulator = 1;
    struct list_node* step = list1;

    while (step->next != list1)
    {
        accumulator = accumulator * step->data;
        step = step->next;
    }

    accumulator = accumulator * step->data;
    return accumulator;
}
