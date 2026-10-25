#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    struct node *next;
    int data;
    struct node *prev;
} Dlist;

// For storing result
extern Dlist *Rhead;
extern Dlist *Rtail;

// For Multiplication
extern Dlist *R1head, *R1tail;
extern Dlist *R2head, *R2tail;

// Creare doubly linkedlist
int dl_insert_last(Dlist **, Dlist **, int);
int dl_insert_first(Dlist **, Dlist **, int);
int display(Dlist **);

// operation functions
int compare_numbers(Dlist **, Dlist **);
int addition(Dlist **, Dlist **);
int subtraction(Dlist **, Dlist **, Dlist **, Dlist **);
int multiplication(Dlist **, Dlist **);
int division(Dlist **, Dlist **, Dlist **, Dlist **);

#endif