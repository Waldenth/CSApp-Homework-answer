#include <stdio.h>
int func4(int edi, int esi, int edx) {
    int temp = (edx - esi);
    int ecx=(temp>>31)&(0x0001);
    temp+=ecx;
    temp=temp>>1;
    int mid = temp + esi;
    if (mid > edi) {
        edx = mid - 1;
        int ret1 = func4(edi, esi, edx);
        return 2 * ret1;
    } else {
        if (mid >= edi) {
            return 0;
        } else {
            esi = mid + 1;
            int ret2 = func4(edi, esi, edx);
            return (2 * ret2 + 1);
        }
    }
}
int main() {
    for (int edi = 0; edi < 10; edi++) {
        int res = func4(edi, 0, 14);
        printf("edi=%d, res=%d\n", edi, res);
    }
    return 0;
}
