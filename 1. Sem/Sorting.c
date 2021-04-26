#include <stdio.h>
#include <stdlib.h>

void selection_sort(int a[], int N)
{
    int i, j, min, t;
    int noc=0;
    int nos=0;
    for(i = 0; i < N-1; i++)
    {
        min = i;
        for (j = i+1; j < N; j++) // suche kleinstes El.
        {
            noc++;
            if (a[j] < a[min])
                min = j; // merke Position des kleinsten El.
        }
        t = a[min]; // Tausch
        nos++;
        printf("\nStep %d: ", nos);
        for(int i=0; i<N; i++){
            if(i==min && i==nos-1){
                printf("[(%d)] ", a[i]);
            }
            else if(i==min){
                printf("[%d] ", a[i]);
            }
            else if(i==nos-1){
                printf("(%d) ", a[i]);
            }
            else{
            printf("%d ", a[i]);
            }
        }
        a[min] = a[i];
        a[i] = t;
    }
    printf("\nResult:");
    for(int i=0; i<N; i++){
        printf(" %d", a[i]);
    }
    printf("\n\nNumber of comparisons: %d\n", noc);
    printf("Number of swaps: %d", nos);
}

int main(){
    int a[1024]={0};
    printf(":");
    for(int i=0; ; i++){
        scanf("%d", &a[i]);
        if(a[i]==0){
            selection_sort(a, i);
            break;
        }
    }

    return 0;


}
