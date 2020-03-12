#define BASE 100000000
#define bit_per part 8
#define part_num 14

typedef struct BigN {
	unsigned long long  part[part_num];
	unsigned int kernel_t;
	unsigned int user_t;
} bigN;
