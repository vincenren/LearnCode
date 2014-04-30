#include <stdio.h>
#define GET_MAX 1
#define GET_MIN 0

int get_max(int i,int j)
{
	return i>j?i:j;
}
int get_min(int i,int j)
{
	return i>j?j:i;
}


int compare(int i,int j,int flag)
{
	int ret;
	int (*p)(int,int);
	if(flag == GET_MAX)
	   p=get_max;
	else
	   p=get_min;
	ret = p(i,j);
	return ret;
}
int main(){

	int i=5,j=10,ret;
	ret=compare(i,j,GET_MAX);
	printf("the max is %d\n",ret);
	
	return 0;
}
