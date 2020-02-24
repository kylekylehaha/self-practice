//merge sort with single & double linked_list
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int value;
    struct node* next; 
}List;

void dump(List* head){
    if(!head || !head->next)
        return;

    printf("%d",head->value);
    List* temp = head->next;
    while(temp){
        printf(" ,%d",temp->value);
        temp = temp->next;
    }
    printf("\n");
    return;
}

void create_List(List** ref, int value){
    List* node = malloc(sizeof(List));
    node->value = value;
    node->next  = NULL;
    if(!(*ref)){
        *ref = node;
    }
    else{
        node->next = *ref;
        (*ref) = node;
    }
    return;
}


List* mergeSort_single(List* start){
    if(!start || !start->next)
        return start;
    
    List *left, *right;
    left = start;
    right = start->next;
    left->next = NULL;

    left = mergeSort_single(left);
    right = mergeSort_single(right);

    for (List* merge = NULL; left || right;){
        if (!right || (left && left->value <= right->value)){
            if (!merge){
                merge = start = left;
            }
            else{
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        }
        else{
            if (!merge){
                merge = start = right;
            }
            else{
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}

int main(){
    int i;
    List *list = NULL;
    List *list1, *list2;
    srand(time(NULL));
    for (i=0;i<20;i++){
        create_List(&list, rand()%100);
    }
    printf("before mergesort\n");
    dump(list);
    list1 = mergeSort_single(list);
    //list2 = mergeSort_double(list);
    printf("list:\n");
    dump(list);
    printf("list1:\n");
    dump(list1);
    printf("\n");
    printf("list2:\n");
    //dump(list2);
}