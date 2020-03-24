#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define LIST_LEN 20
#define EXP_TIME 10

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

static void split(list *src, list **left, list **right, int *left_len, int *right_len, int thres)
{
    list *fast = src, *prev_fast = NULL, *next_fast;
    list *slow = src, *prev_slow = NULL, *next_slow;
    int len = 0;
    while (fast && XOR(fast->addr, prev_fast)) {
        /* fast = fast->next->next */
        next_fast = XOR(fast->addr, prev_fast);
        fast = XOR(fast, next_fast->addr);
        prev_fast = next_fast;
        /* slow = slow->next */
        next_slow = XOR(slow->addr, prev_slow);
        prev_slow = slow;
        slow = next_slow;
        len++;
    }
    *left = src;
    if (!src) {
        *right = NULL;
    } else if (fast) {
        /* list is odd */
        list *next = XOR(prev_slow, slow->addr);
        next->addr = XOR(slow, next->addr);
        *right = next;
        slow->addr = XOR(slow->addr, next);
        *left_len = len;
        *right_len = len + 1;
    } else {
        /* list is even */
        prev_slow->addr = XOR(prev_slow->addr, slow);
        slow->addr = XOR(prev_slow, slow->addr);
        
        *right = slow;
        *left_len = *right_len = len;
    }
    return;
}

list *op_merge_sort(list *start, int list_len, int thres)
{
    if (!start || !start->addr)
        return start;
    if (list_len < thres) {
        return insertion_sort(start);
    }

    list *head = start;
    list *left, *right;
    int left_len = 0, right_len = 0;
    split(head, &left, &right, &left_len, &right_len, thres);

    left = op_merge_sort(left, left_len, thres);
    right = op_merge_sort(right, right_len, thres);
    
    return merge(left, right);
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
    return (unsigned int) result.tv_sec * 1000000000 + result.tv_nsec;
}

int main(){
    FILE *fp = fopen("threshold.txt", "wb+");       // <- 這行怪怪的
    
    if (!fp) {
        printf("error open file\n");
        return 0;
    }
    srand((unsigned)time(NULL));

   // for (int i = 0;i <EXP_TIME; i++) {
        list **start;
        *start = NULL;
        printf("fuck\n");
        for (int j = 0;j < LIST_LEN; j++) {
            insert_node(start, rand()%100);
        }
        //struct timespec time_start, time_end;
        //clock_gettime(CLOCK_REALTIME, &time_start);
        printf("haha\n");
        *start = op_merge_sort(*start, LIST_LEN, 3);
        //clock_gettime(CLOCK_REALTIME, &time_end);
        print(*start);
       // int diff = diff_in_ns(time_start, time_end);
        //fprintf(fp, "3 %d\n" ,diff);
        delete_list(*start);
   // }
    return 0;
}