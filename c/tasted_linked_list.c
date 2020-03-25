#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#define LEN 10000

typedef struct _node node;
struct _node {
    int data;
    struct _node *next;
};

node *head;

node *create(int data)
{
    node *tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;
   
    return tmp;
}


static void insert_v1(node *newt) {
    node *tmp = (node*)head, *prev = NULL;
    while (tmp != NULL && tmp->data < newt->data) {
        prev = tmp;
        tmp = tmp->next;
    }
    newt->next = tmp;
    if (prev == NULL)
        head = newt;
    else
        prev->next = newt;
}

static void insert_v2(node *newt)
{
    node **link = &head;
    while (*link && (*link)->data < newt->data)
        link = &(*link)->next;
    newt->next = *link;
    *link = newt;
}


static void clear()
{
    node *curr =(node*) head;
    node *curr_next =(node*) curr->next;
    
    while(curr) {
        node *tmp = NULL;
        if (curr_next)
            tmp = (node*)curr_next->next;
       // printf("%2d", curr->data);
        free(curr);
        curr = curr_next;
        curr_next = tmp;
    }
    head = NULL;
    //printf("\n");
    return;
}

unsigned int diff_in_ns(struct timespec t1, struct timespec t2)
{
    struct timespec result;
    if ((t2.tv_nsec - t1.tv_nsec) < 0) {
        result.tv_sec = t2.tv_sec - t1.tv_sec - 1;
        result.tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
    } else {
        result.tv_sec = t2.tv_sec - t1.tv_sec;
        result.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (unsigned int) result.tv_sec * 1000000000 + result.tv_nsec ;
}


int main(){
    
    /* test for insert_v1 */
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0;i < LEN;i++) {
        insert_v2(create(i));
    }
    clock_gettime(CLOCK_REALTIME, &end);
    printf("tasted insert time: %u\n", diff_in_ns(start, end));
    clear();
    
    /* test for insert_v2. i.e. tasted insert */
    struct timespec t3, t4;
    clock_gettime(CLOCK_REALTIME, &t3);
    for (int i = 0;i < LEN;i++) {
        insert_v1(create(i));
    }
    clock_gettime(CLOCK_REALTIME, &t4);
    printf("ori time: %u\n", diff_in_ns(t3, t4));
    clear();
    
    return 0;
}
