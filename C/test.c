#include <stdio.h>
int main(){
   int a[] = {1,2,3,4,5}, b[5];
   int i,*j;
   
   for(i=0;i<5;i++)
       b[i]=a[i];
   
   for(i=0;i<5;i++)
      printf("%d ",b[i]);
   printf("\n");

   for(i=0;i<5;i++)
      printf("%d ",*(a+i));
   printf("\n");
  
   for(j=a,i=0;i<5;i++)
      printf("%d ",*j+i);
   printf("\n");
   
   for(j=a; j<a+5;)
      printf("%d ",*j++);
   printf("\n");
   return 0;
}
