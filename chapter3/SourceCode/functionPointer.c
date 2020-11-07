#include <stdio.h>
void fun(int x,int *p){
    *p=*p+x;
}
int main(){
    int (*fp)(int,int *);
    fp=fun;
    int x=1;
    fp(10,&x);
    printf("x=%d\n",x);
}
