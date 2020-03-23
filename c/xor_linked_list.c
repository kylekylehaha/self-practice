#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr;
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

void insert_node(list **l, int d) {
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
}

void delete_list(list *l) {
    while (l) {
        list *next = l->addr;
        if (next)
            next->addr = XOR(next->addr, l);
        free(l);
        l = next;
    }
}

list *merge(list *left, list *right)
{
   list *start = NULL;
   for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(left, merge->addr);
                left->addr = merge;
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(right, merge->addr);
                right->addr = merge;
                merge = right;
            }
            right = next;
        }
    }

    return start;
}

void print(list *l)
{
    if (!l) {
        printf("list is not exist now\n");
        return;
    }
    printf("list: ");
    list *next = l->addr;
    while(l) {
        list *tmp;
        printf("%3d", l->data);
        if (next) {
            tmp = XOR(next->addr, l);
        }
        l = next;
        next = tmp;
    }
    printf("\n");
    return;
}

list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

    start = merge(left, right);
    return start;
}

list *insertion_sort(list *head)
{
    if (!head || !head->addr)
        return head;

    list *sorted = head;
    list *next = sorted->addr;
    if (next)
        next->addr = XOR(sorted, next->addr);
    sorted->addr = NULL;

    for (list *cur = next; cur;) {
        next = cur->addr;
        if (next)
            next->addr = XOR(cur, next->addr);
        cur->addr = NULL;
        sorted = merge(sorted, cur);
        cur = next;
    }
    return sorted;
}

int main(){
    list **start;
    srand((unsigned)time(NULL));

    for(int i = 0;i < SIZE;i++){
        insert_node(start, rand()%100);
    }
    print(*start);
    *start = insertion_sort(*start);
    print(*start);
    return 0;
}