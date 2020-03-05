#include <stdio.h>
#include <stdlib.h>
typedef int (*calculate)(int, int);

int add(int a, int b)
{
	return a + b;
}

int minus(int a, int b)
{
	return a - b;
}

int multiply(int a, int b)
{
	return a * b;
}

int divide(int a, int b)
{
	return a / b;
}

//int operation(int a, int b, int (*operation)(int, int))
//{
//	return operation(a, b);
//}

int operation(int a, int b, calculate calc)
{
	return calc(a, b);
}

int main(){
	int a = 8;
	int b = 2;

	printf("op is add, result is %d\n", operation(a, b, add));
	printf("op is minus, result is %d\n", operation(a, b, minus));
	printf("op is multiply, result is %d\n", operation(a, b, multiply));
	printf("op is divide, result is %d\n", operation(a, b, divide));


}
