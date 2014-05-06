#include<stdio.h>

void main()
{
  int a[5] = {1,2,3,4,5};
  int *ptr = (int *)(&a+1);
  printf("%d,%d\n",*(a+1),*(ptr-1));
  printf("%p,%p,%p\n",&a,(a),&a[1]);
  printf("%p,%p,%p,%p,%p\n",&a[1],&a[2],&a[3],&a[4],&a[5]);
  printf("%p,%p,%p\n",ptr-1,ptr,&a+1);
}
