#include <stdio.h>

int main(){

    int p = 0;
    int sn1 = 1;
    int s = 1;

    for(int i = 2;;i++){

        scanf("%d", &p);
        printf(": ");

        if(p == 0){
            break;
        }
        if(p <= sn1){
            sn1++;
            printf("position #1: %d\n", sn1);
        }
        if(p == 1){
            s = i;
            printf("new leader: #%d\n", s);
        }
    }

    printf("final position #1: %d\n", sn1);
    printf("winner: #%d", s);

    return 0;
    }
