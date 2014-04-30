#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
	int ret;
	ret=alarm(50);
        sleep(30);
	printf("%d\n",ret);
        ret=alarm(10);
	printf("%d\n",ret);
	pause();
	return 0;	
}
