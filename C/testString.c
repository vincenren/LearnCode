#include <stdio.h>
#include <string.h>

int main(){
	char *s="Hello world";
        puts(s);
	printf("the size of s is %d\n", sizeof(s));
	printf("the lenght of s is %d\n", strlen(s));
	return 0;
}
