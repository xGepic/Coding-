#include <stdio.h>

int power(int base,int exp){

   if(exp<0){

        return-1;
   }
   else if (exp ==0){
        return 1;
   }
int result = 1;

while(exp >0){
    result *= base;
    exp--;
}

return result;
}

double octtodec(int oct){

    int dec1 = 0;
    int temp = 0;

    while(oct != 0){

        dec1 = dec1 + (oct%10) * power(8,temp);
        temp++;
        oct = oct / 10;

    }

    return dec1;

}

int main () {

   int octal;
   int zs;

   printf(": ");
   scanf("%d", &octal);

   printf("dec.: %.0lf\n", octtodec(octal));

   int temp1, temp2, temp3, temp22,temp33;

   temp1=octtodec(octal)/100;
   temp22=((octtodec(octal))/10);
   temp2 = temp22%10;
   temp33=octtodec(octal);
   temp3=temp33%10;

   zs = temp1+temp2+temp3;

   printf("ZS: %d",zs);

   return 0;

}
