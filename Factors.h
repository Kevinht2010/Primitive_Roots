#ifndef FACTORS_HEADER_H_INCLUDED

#define FACTORS_H_INCLUDED

struct list_node* factorsof(unsigned int n);

int findfirstfactor(int n);

int myPow(int x, int n);

int findfirstfactorpower(int n);

struct list_node* primefact(int n);

int phi(int n); 

#endif // FACTORS_H_INCLUDED