#include <stdio.h>
#include <stdlib.h>

int main(){

    int checkZahl=0;
    int zahl=0;
    int i=0;
    int sumOfEingaben=0;
    int min=10;
    int max=0;

    while (i<5){
        scanf("%d",&zahl);

        sumOfEingaben+=zahl;

        checkZahl=zahl;
            if(checkZahl<min){
                min=zahl;
                }

            if(checkZahl>max){
                max=zahl;
                }
    i++;
    }
    printf(": minimum sum: %d\n",sumOfEingaben-max);
    printf("maximum sum: %d",sumOfEingaben-min);

}
