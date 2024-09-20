#include "dlist.h"
#include <stdio.h>

#define BEGIN 0

int main()
{

    printf("Initializing dlist ...\n");
    dlist_t* dlist = dlist_create();
    for(int i = 0; i < 5; i++)
    {
        int* myInt = (int*)malloc(sizeof(int));
        *myInt = i;
        dlist_insert(dlist, BEGIN, (void*)myInt);
    }
    int* x = (int*)malloc(sizeof(int));
    *x = 42;
    printf("dlist initialized\nInserting: %d the middle...\n", *x);
    dlist_insert(dlist, 3, x);
    printf("Inserted: %d\n", *x);
    printf("Freeing dlist...\n");
    dlist_destroy(dlist);
    printf("dlist freed!\n");
    return 0;
}