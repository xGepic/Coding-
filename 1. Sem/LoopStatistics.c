#include <stdio.h>

void maxi(double *x, double *y){
    if(*y < *x){
        *y = *x;
    }
}

void mini(double *x, double *z){
    if(*x < *z){
        *z = *x;
    }
}

int main(){
    double x = 0.0;
    double y = 0.0;
    double z = 1000000;
    int count = 0;
    double sum = 0.0;

    while(1){
        printf(": ");
        scanf("%lf", &x);

        if(x <= 0)
            break;
        else{
            maxi(&x, &y);
            mini(&x, &z);
            count++;
            sum = x + sum;
        }
    }
    if(y <= 0){
        printf("no number entered\n");
    }
    else{
        printf("cnt: %d\n", count);
        printf("min: %.2f\n", z);
        printf("max: %.2f\n", y);
        printf("avg: %.2f\n", sum/count);
    }
    return 0;
}
