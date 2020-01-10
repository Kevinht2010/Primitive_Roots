#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "Lists_and_Trees.h"

struct list_node* sub_one(struct list_node* list1)
{
    list1->data = list1->data - 1;
    return list1;
}

struct list_node* add_one(struct list_node* list1)
{
    list1->data = list1->data + 1;
    return list1;
}


struct list_node* factorsof(unsigned int n)
{
    if (n == 0)
    {
        return NULL;
    }
    else
    {
        struct list_node* newnode;
        struct list_node* accumulator = NULL;

        for (int i = 1; i <= (n / 2); i++)
        {
            if ((n % i) == 0)
            {
                newnode = (struct list_node*)malloc(sizeof(struct list_node));
                newnode->data = i;
                newnode->next = newnode;
                newnode->prev = newnode;

                accumulator = append(accumulator, newnode);
            }
            else
            {
                NULL;
            }
        }
        newnode = build_node(n);

        accumulator = append(accumulator, newnode);

        return accumulator;
    }
}

int findfirstfactor(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        int p = 0;

        for (int i = 2; i <= sqrt(n) && (p == 0); i++)
        {
            if ((n % i) == 0)
            {
                p = i;
            }
            else
            {
                NULL;
            }
        }

        if (p == 0)
        {
            return n;
        }
        else
        {
            return p;
        }
    }
}

int myPow(int x, int n)
{
    int number = 1;

    for (int i = 0; i < n; ++i)
        number *= x;

    return(number);
}

int findfirstfactorpower(int n)
{
    int p;
    int power = 0;

    p = findfirstfactor(n);

    while ((n % p) == 0)
    {
        power = power + 1;
        n = (n / p);
    }
    return myPow(p, power);
}

struct list_node* primefact(int n)
{
    if (n == 0)
    {
        return build_node(0);
    }
    else
    {

        struct list_node* accumulator = NULL;
        struct list_node* newnode;
        int p = 1;
        if (n == 1)
        {
            return build_node(1);
        }
        else
        {
            while (n != 1)
            {
                p = findfirstfactor(n);
                newnode = (struct list_node*)calloc(1, sizeof(struct list_node));
                newnode->data = p;
                newnode->next = newnode;
                newnode->prev = newnode;

                accumulator = append(accumulator, newnode);

                n = (n / p);
            }

            return accumulator;
        }
    }
}

int phi(int n)
{
    struct list_node* primefactors = remove_duplicates(primefact(n));
    int p = listproduct(primefactors);
    struct list_node* newlist = map(sub_one, primefactors);
    int m = listproduct(newlist);

    return ((n / p) * m);
}
