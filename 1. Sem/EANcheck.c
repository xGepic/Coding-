#include <stdio.h>
#include <stdlib.h>

int main(){

    int hv;
    int zsg = 0;
    int zsug = 0;
    char ean_full[13];
    scanf("%s", &ean_full[0]);

    for(int i = 1; i < 12; i+=2){

        int x = (int)ean_full[i];
        x -= 48;
        zsg += x;
        }

    for(int i = 0; i < 12; i += 2){

        int x = (int)ean_full[i];
        x -= 48;
        zsug+= x;
        }

    hv = ((zsg * 3) + zsug)-1;
    hv = hv % 10;
    hv = 9 - hv;

    if((hv) == ((int)ean_full[12]-48)){

        printf(": VALID");
    }

    else{

        printf(": INVALID");
    }

}
