#include <stdio.h>

int main() {
	int a = 8;
	int b = 7;

	a += 5;

	printf("%d %d\n", a, a && b);


	b %= 3;

	printf("%d %d\n", b, a || b);

	return 0;
}
