#include <stdio.h>

void f(double *x, double *y){
    if(*y < *x){
        *y = *x;
    }
}

int main(){
    double x = 0.0;
    double y = 0.0;

    while(1){
        printf(": ");
        scanf("%lf", &x);

        if(x <= 0) break;
        else{
            f(&x, &y);
        }
    }
    if(y <= 0){
        printf("no numbers entered\n");
    }
    else{
        printf("largest number: %.2f", y);
    }
    return 0;
}
