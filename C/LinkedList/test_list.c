#include "list.h"
#include <stdio.h>

#define BEGIN 0


int compare_int(void* int_1, void* int_2)
{
    int i1 = *((int*)int_1);
    int i2 = *((int*)int_2);
    printf("Comparing %d, against %d: ", i1, i2);
    if(i1 == i2)
    {
        printf("Match!\n");
        return 1;
    }
    printf("No Match!\n");
    return 0;
}

void compare_lists(list_t* list1, list_t* list2)
{
    if(list_compare(list1, list2, &compare_int))
        printf("Lists Match!\n");
    else
        printf("Lists Do Not Match!\n");
}


void test_compare()
{
    list_t* list_1 = list_create();
    list_t* list_2 = list_create();
    list_t* diff_list = list_create();

    for(int i = 0; i < 10; i++)
    {
        int* int_1 = (int*)malloc(sizeof(int));
        int* int_2 = (int*)malloc(sizeof(int));
        int* diff_int = (int*)malloc(sizeof(int));
        *int_1 = i;
        *int_2 = i;
        *diff_int = i+1;
        list_insert(list_1, BEGIN, int_1);
        list_insert(list_2, BEGIN, int_2);
        list_insert(diff_list, BEGIN, diff_int);
    }

    printf("Comparing list1 and list2 ...\n");
    compare_lists(list_1, list_2);
    printf("Comparing list1 with different list ...\n");
    compare_lists(list_1, diff_list);

    printf("Freeing lists ...\n");
    list_destroy(list_1);
    list_destroy(list_2);
    list_destroy(diff_list);
    printf("Lists freed!\n");
}

int main()
{
    test_compare();
    return 0;
}