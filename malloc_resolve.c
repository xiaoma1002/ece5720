// You must _return_ arr after malloc arr 
#include <stdio.h> 
#include <stdlib.h> 

int* func(int* arr){
  arr = (int *)malloc(sizeof(int));
  return arr;
}  

int main() 
{ 
     int *a = (int *)malloc(sizeof(int)); 
    // int *b = (int *)malloc(sizeof(int));     
    //int *a; 
    int *b; 
    int *c;
    int *d;
    //func(a);
    b= func(b);
    c = func(c);
    d= func(d);
    
    printf("%p\n",&a);
    printf("%p\n",&b);
    printf("%p\n",&c);
    printf("%p\n",&d);
    
    printf("test");
    //*(a) = 1;
    printf("%d ", *a); 
    printf("%d ", *b); 
    printf("%d ", *c); 
    printf("%d ", *d); 

    // free(a);
    // free(b);
    // free(c);
    // free(d);
    
   return 0; 
} 
