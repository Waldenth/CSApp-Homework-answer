/* CSApp P31 exapmple c code */
#include <stdio.h>
 
typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start,size_t len){
    size_t i;
    for(i=0;i<len;i++)
        printf(" %.2x",start[i]);
    printf("\n");
}

void show_int(int x){
    show_bytes((byte_pointer)&x,sizeof(int));
}

void show_float(float x){
    show_bytes((byte_pointer)&x,sizeof(int));
}

void show_poniter(void *x){
    show_bytes((byte_pointer)&x,sizeof(void*));
}

int main(){
    int numInt=0xFFFFFFFE;
    float numFloat=3.1;
    void *point=NULL;
    printf("sizeof int is %d\nsizeof float is %d\nsizeof pointer is %d\n",sizeof(int),sizeof(float),sizeof(void*));
    show_int(numInt);
    show_float(numFloat);
    show_poniter(point);
    return 0;
}
/**
 * gcc .\show_bytes.c -o test
 * sizeof int is 4
 * sizeof float is 4
 * sizeof pointer is 8
 * fe ff ff ff
 * 66 66 46 40
 * 00 00 00 00 00 00 00 00
 */