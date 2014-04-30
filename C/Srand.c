#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int randVal, number;
	srand(time(NULL));
	number = rand() % 100 + 1;
	printf("srand is %d\n", number);
	return 0;
}
