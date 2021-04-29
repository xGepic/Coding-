#include <stdio.h>
#include <stdlib.h>

int main(){

    char usdate[15];
    scanf("%15s",&usdate[0]);

    //Monat einstellig
if ((usdate [1]=='/') && (usdate[4]=='/')){

    printf(": %c%c.0%c.",usdate[2], usdate[3], usdate[0]);
    printf("%c%c%c%c",usdate[5], usdate[6], usdate[7],usdate[8]);
}

else if ((usdate [2]=='/') && (usdate[4]=='/')){

    printf(": 0%c.%c%c.",usdate[3], usdate[0],usdate[1]);
    printf("%c%c%c%c",usdate[5], usdate[6], usdate[7],usdate[8]);
}

else if ((usdate [1]=='/') && (usdate[3]=='/')){

    printf(": 0%c.0%c.",usdate[2], usdate[0]);
    printf("%c%c%c%c",usdate[4], usdate[5], usdate[6],usdate[7]);

        }

else {
printf(": %c%c.%c%c.",usdate[3], usdate[4],usdate[0],usdate[1]);
printf("%c%c%c%c", usdate[6], usdate[7],usdate[8],usdate[9]);
}
return 0;
}
