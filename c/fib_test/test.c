#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bigN.h"

static void bigN_add(bigN a, bigN b, bigN *result)
{
    memset(result, 0, sizeof(bigN));
    long long carry = 0;
    for (int i = 0; i < part_num; i++) {
        long long tmp = carry + a.part[i] + b.part[i];
        result->part[i] = tmp % BASE;
        carry = tmp / BASE;
    }
}

static void bigN_print(bigN buf)
{
    int i = part_num - 1;
    while ((i >= 0) && (buf.part[i] == 0))
        i--;
    if (i  < 0) {
        printf("0");
        return;
    }
    printf("%llu", buf.part[i--]);
    while(i >=0) {
        printf("%08llu", buf.part[i]);
        i--;
    }
}

static void bigN_assign(bigN *a, bigN *b)
{
    for(int i = 0; i < part_num; i++) {
        a->part[i] = b->part[i];
    }
    return;
}


static void fib_sequence(long long k, bigN *result)
{
   {
    if (k == 0) {
        memset(result, 0, sizeof(bigN));
        return ;
    }
    bigN *f0, *f1, *tmp;
    f0 = malloc(sizeof(bigN));
    f1 = malloc(sizeof(bigN));
    memset(f0, 0, sizeof(bigN));
    memset(f1, 0, sizeof(bigN));
    f1->part[0] = 1;
    for (int i = 2; i <= k; i++) {
        bigN_add(*f0, *f1, f0);
        tmp = f0;
        f0 = f1;
        f1 = tmp;
    }

    bigN_assign(result, f1);
    return;
}
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

int main()
{
    FILE *fd = fopen("test_fd.txt", "wb+");
	FILE *fseq = fopen("test_fseq.txt", "wb+");
	FILE *fd_clz = fopen("test_fd_clz.txt", "wb+");

	unsigned long long result = 0;
    int offset = 100; /* TODO: try test something bigger than the limit */

    for (long long i = 0; i <= offset; i++) {
        bigN output;
        struct timespec start, end;
        
        //printf("offset is %d\n", i);
		clock_gettime(CLOCK_REALTIME, &start);
		fib_sequence(i, &output);
        clock_gettime(CLOCK_REALTIME, &end);
        //fprintf(fseq, "%d %u\n", i, diff_in_ns(start, end));
		
		printf("offset: %lld, ",i);
        
        
        bigN_print(output);
        printf("\n");
        
    }

	fclose(fd_clz);
    fclose(fd);
    fclose(fseq);
    return 0;
}

