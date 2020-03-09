#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long fib_fast_doubling(long long k)
{
    unsigned int digit = 0;
    int saved = k;
    while (k) {
        digit++;
        k /= 2;
    }
    k = saved;
    unsigned long long a, b;
    a = 0;
    b = 1;
    for (unsigned int i = digit; i > 0; i--) {
        unsigned long long t1, t2;
        t1 = a * (2 * b - a);
        t2 = b * b + a * a;
        a = t1;
        b = t2;
        if (k & (1 << (i - 1))) {
            t1 = a + b;
            a = b;
            b = t1;
            // k &= ~(1 << (i - 1));
        }
    }
    return a;
}

unsigned long long fib_sequence(long long k)
{
    unsigned long long f[k + 2];

    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= k; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[k];
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

	unsigned long long result = 0;
    int offset = 92; /* TODO: try test something bigger than the limit */

	printf("use fib_fast_doubling now\n");
    for (int i = 0; i <= offset; i++) {
        struct timespec start, end;
        
		clock_gettime(CLOCK_REALTIME, &start);
		result = fib_fast_doubling((long long)i);
        clock_gettime(CLOCK_REALTIME, &end);
        fprintf(fd, "%d %u\n", i, diff_in_ns(start, end));
		
		printf("offset: %d, fib is %llu\n", i, result);
    }

	printf("use fib_seq now\n");
    for (int i = 0; i <= offset; i++) {
        struct timespec start, end;
        
		clock_gettime(CLOCK_REALTIME, &start);
		result = fib_sequence((long long)i);
        clock_gettime(CLOCK_REALTIME, &end);
        fprintf(fseq, "%d %u\n", i, diff_in_ns(start, end));
		
		printf("offset: %d, fib is %llu\n", i, result);
    }

    fclose(fd);
    fclose(fseq);
    return 0;
}

