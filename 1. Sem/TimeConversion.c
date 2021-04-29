#include <stdio.h>
#include <stdlib.h>

int main()
{
    int s = 0;
    int m = 0;

    scanf("%2d:%2d",&s, &m);

    if(s>12){
        printf("24h time: 12h time:  %d:%02d PM", s-12, m);
    }
    else if(s==12){
        printf("24h time: 12h time: %d:%02d PM", s,m);
    }
    else if(s==0){
             printf("24h time: 12h time: %d:%02d AM", s+12,m);
    }
    else if(s<12){
        printf("24h time: 12h time: %0d:%02d AM", s,m);
    }
return 0;
}
