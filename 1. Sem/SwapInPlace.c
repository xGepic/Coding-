#include <stdio.h>
#include <stdlib.h>

int main(){
    int a = 0;
    int b = 0;

    scanf("%d",&a);
    scanf("%d",&b);

    printf(": Before:\n");
    printf(" a= %d\n",a);
    printf(" b: %d\n",b);

    a = a + b;
    b = a - b;
    a = a - b;

    printf("After:\n");
    printf(" a= %d\n",a);
    printf(" b: %d\n",b);

    return 0;
}
