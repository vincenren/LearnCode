#include <stdio.h>

int main(){
	
	int a =3,b=4,c=5;
	printf("a+b>c&&b==c     %d\n",a+b>c&&b==c);
	printf("a||b&&b-c  %d\n",a||b&&b-c);
	printf("!(a>b)&&!c||1  %d\n", !(a>b)&&!c||1);
}
