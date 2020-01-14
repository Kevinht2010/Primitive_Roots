#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#include "Factors.h"
#include "Lists_and_Trees.h"

typedef void (*Func)(int param);

bool has_primitive_roots(int n)
{
    int m = findfirstfactorpower(n);
    int p = (n / m);

    if (n == 1 || n == 2 || n == 4)
    {
        return true;
    }
    else if (p == 1 && (n % 2 != 0))
    {
        return true;
    }
    else if ((p != 1) && (n % 2 == 0))
    {
        int p2 = (n / 2) / (findfirstfactorpower(n / 2));

        if (p2 == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

long long int myPowLong(long long int x, int y)
{
    long long acc;
    acc = 1;
    while (y != 0)
    {
        acc = acc * x;
        --y;
    }
    return acc;
}

int mod(int n, long long int p, int k)
{
    if (k == 1)
    {
        return p;
    }
    else if (k == 0)
    {
        return 1;
    }
    else
    {
        long long int acc = 1;  
        while (k != 1)
        {
            acc = acc * (myPowLong(p, k % 2) % n) % n;
            p = (p * p % n);
            k = (k / 2);
        }

        return ((acc * p) % n);
    }
}

struct list_node* sieve(int n, struct list_node* list1)
{
    struct list_node* accumulate = NULL;
    struct list_node* step = list1;
    struct list_node* temp = NULL;
    while (step->next != list1)
    {
        if (step->data % n == 0)
        {
            temp = step;
            step = step->next;
            free(temp);
        }
        else
        {
            temp = step;
            step = step->next;
            temp = car(temp);
            accumulate = append(accumulate, temp);
        }
    }

    if (step->data % n == 0)
    {
        return accumulate;
    }
    else
    {
        temp = step;
        temp->next = temp;
        temp->prev = temp;
        return append(accumulate, car(step));
    }
}

struct list_node* relative_primes(int n)
{
    struct list_node* accumulator;
    accumulator = (struct list_node*)calloc((n - 1), sizeof(struct list_node));
    accumulator = cdr(buildlist(n));

    struct list_node* factors = remove_duplicates(primefact(n));
    struct list_node* step = factors;

    while (step->next != factors)
    {
        accumulator = sieve(step->data, accumulator);
        step = step->next;
    }

    accumulator = sieve(step->data, accumulator);
    return accumulator;
}

bool is_primitive_root(int p, int n)
{
    if (n % p == 0)
    {
        return false;
    }
    else
    {
        struct list_node* factors = factorsof(phi(n));
        struct list_node* step = factors;
        long long int m = p;

        while (((mod(n, m, step->data) % n) != 1) && (step->next != factors))
        {
            step = step->next;
        }

        if (step->data == phi(n))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int find_primitive_root(int n)
{
    struct list_node* primes = relative_primes(n);
    struct list_node* step = primes;
    bool is_p_root = false;

    while (step->next != primes && is_p_root == false)
    {
        is_p_root = is_primitive_root(step->data, n);
        step = step->next;
    }

    return step->prev->data;
}

struct list_node* primitive_roots_of(int n)
{

    if (has_primitive_roots(n))
    {
        unsigned long long int p = find_primitive_root(n);
        struct list_node* primes = relative_primes(phi(n));
        struct list_node* step = primes;
        while (step->next != primes)
        {
            step->data = mod(n, p, step->data);
            step = step->next;
        }
        step->data = (mod(n, p, step->data));
        return mergesort(primes);
    }
    else
    {
        printf("The value you entered has zero primitive roots. \n");
        return NULL;
    }
}

void Primitive_Root_Calculator(void)
{
    print("Please enter the desired integer value:");

    int n;

    scanf_s("%d", &n);

    struct list_node* PRoots = find_primtive_roots(n);

    if (Proots == NULL)
    {
    }
    else
    {
        print_list(PRoots);
    }
}

int main(void)
{
    Primitive_Root_Calculator();
}

