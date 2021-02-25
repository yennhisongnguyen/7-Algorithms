#include <stdio.h>

int main () {
	int i = 0;

	unsigned long j = 0;

	while (j<1000000000) {
		printf("%d\n", i);
		i++;
		j++;
	}

	return 0;
}