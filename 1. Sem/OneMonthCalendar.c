#include <stdio.h>

int main(){

    int nod = 0;
    int sd = 0;

    printf("number of days in month: ");
    scanf("%d", &nod);

    printf("starting day of week (1=Monday, 7=Sunday):\n");
    scanf("%d", &sd);
    for (int j = 1; j < sd; j++){
        printf("   ");
    }

    for(int i = 1; i <= nod; i++){
        if((i+sd-2)%7 == 0 && i+sd != 2){
            printf("\n");
        }
        if(i<10) printf(" ");
        printf("%d ", i);
    }
    return 0;
}
