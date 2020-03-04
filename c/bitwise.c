#include <stdio.h>
#include <stdbool.h>

bool getBit(int n, int index)
{
	return n & (1 << index);
}

int setBit(int n, int index, bool b)
{
	if (b)
		return n |= (1 << index);
	int mask = ~(1 << index);
	return n &= mask;
}

int main()
{
	int num = 17;
	for (int i = 7; i>=0; i--){
		printf("%d", getBit(num, i));
	}
	printf("\n");

	int index = 6;
	printf("# Setting %d-th bit\n", index);
	num = setBit(num, index, true);
	for (int i = 7; i>=0; i--){
		printf("%d", getBit(num, i));
	}
	printf("\n");
	index = 4;
	printf("Clear %d-th bit\n", index);
	num = setBit(num, index, false);
	for (int i = 7; i>=0; i--){
		printf("%d", getBit(num, i));
	}
	printf("\n");

}
