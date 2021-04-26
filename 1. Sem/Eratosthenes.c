#include <stdio.h>

int main()
{
    int number,i,j;
    printf(": ");
    scanf("%d",&number);

    int primes[number+1];

    for(i = 2; i<=number; i++)
        primes[i] = i;

    i = 2;
    while ((i*i) <= number)
    {
        if (primes[i] != 0)
        {
            for(j=2; j<number; j++)
            {
                if (primes[i]*j > number)
                    break;
                else
                    primes[primes[i]*j]=0;
            }
        }
        i++;
    }

    for(i = 2; i<=number; i++){

        if((i==30) || (i==72) || (i==114) || (i==174) || (i==230) || (i==282) || (i==350) || (i==410) || (i==464) || (i==542) || (i==602) || (i==660) || (i==734) || (i==810) || (i==864) || (i==942)){
            printf("\n");
        }

         if (primes[i]!=0)
            printf("%d ",primes[i]);
    }

    return 0;
}
