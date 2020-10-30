#include <stdio.h>
int main(){
    __int64 a=0xFFFFFFFE;
    int b=0xFFFF;
    printf("a size is %d\nb size is %d\n",sizeof(a),sizeof(b));
    return 0;
}