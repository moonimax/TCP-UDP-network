#include <stdio.h>

//#pragma pack (4)

typedef struct c05_01
{
	int a;
	int b;
	double c;
} C05_01;

typedef struct c05_02
{
	int a;
	double c;
	int b;
} C05_02;

#pragma pack (push, 4)

typedef struct c05_03
{
	int a;
	double c;
	int b;
} C05_03;

#pragma pack (pop)

typedef struct c05_04
{
	int a;
	double c;
	int b;
} C05_04;

typedef struct c05_05
{
	int a;
	char b;
} C05_05;

typedef struct c05_06
{
	int a;
	char b;
	char c;
} C05_06;


int main(int argc, char* argv[])
{
	C05_01 test1;
	C05_02 test2;
	C05_03 test3;
	C05_04 test4;
	C05_05 test5;
	C05_06 test6;

	printf("test1: %d\n", sizeof(test1));
	printf("test2: %d\n", sizeof(test2));
	printf("test3: %d\n", sizeof(test3));
	printf("test4: %d\n", sizeof(test4));
	printf("test5: %d\n", sizeof(test5));
	printf("test6: %d\n", sizeof(test6));

	return 0;
}

