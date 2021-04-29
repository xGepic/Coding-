#include <stdio.h>
#include <stdlib.h>

int main(){

    int s1 = 0;
    int s2 = 0;
    int s3 = 0;
    int m1 = 0;
    int m2 = 0;
    int m3 = 0;
    int d = 0;

    printf(": ");
    scanf("%d%*c%d", &s1, &m1);

    printf(": ");
    scanf("%d%*c%d", &s2, &m2);

    if(s1 > 23 || s2 > 23 || s1 < 0 || s2 < 0 || m1 < 0 || m2 < 0 || m1 > 59 || m2 > 59){
        printf("FORMAT ERROR");
    }else {
        d = (s2*60 + m2) - (s1*60 + m1);
        if (d<0){
            printf("NOT VALID");
        }else{
            s3 = d/60;
            m3 = d%60;
            printf("%2d:%02d", s3,m3);
        }
    }
    return 0;
}
