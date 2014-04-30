#include <stdio.h>

int main(){

	int i,j;
	long sum = 0;

	for(i=1;i<=10;i++)
	{
		int total =1;
		for(j=1;j<=i;j++){
			
			total=total*j;
			printf("i=%d, j=%d, total=%d\n", i, j , total);
		}		
		sum=sum+total;
		printf("sum is %ld\n",sum);
	}
	printf("1!+2!+3!+..+10!=%ld\n",sum);
	return 0;

}
