#include<stdio.h>
#include<stdlib.h>

int main(){

    int increment = 0;
    int increment2 = 0;
    int first_input = 0;
    char op = 0;
    scanf("%d", &first_input);
    int ergebnis = 0;
    ergebnis = first_input;

    do {
        int x_input = 0;
        scanf(" %c", &op);
        switch(op){
            case '+':
                scanf("%d", &x_input);
                ergebnis = ergebnis + x_input;
                printf("Ergebnis: %d\n", ergebnis);
                increment++;
                break;
            case '-':
                scanf("%d", &x_input);
                if(((ergebnis-x_input)==1) || (x_input-ergebnis)==1) {
                    printf("Einer der Operanden ist um 1 kleiner oder groesser als der andere\n");
                    printf("Ergebnis: %d\n", ergebnis);
                    increment2++;
                    break;
                }else{
                ergebnis = ergebnis - x_input;
                printf("Ergebnis: %d\n", ergebnis);
                increment++;
                break;
                }
            case '*':
                scanf("%d", &x_input);
                ergebnis = ergebnis * x_input;
                printf("Ergebnis: %d\n", ergebnis);
                increment++;
                break;
            case '/':
                scanf("%d", &x_input);
                if(x_input == 0){
                    printf("Operation ist ungueltig!\n");
                    printf("Keine Divisionen durch 0!\n");
                    printf("Ergebnis: %d\n", ergebnis);
                    increment2++;
                    break;
                }
                int rest = ergebnis % x_input;
                if (rest != 0){
                    char choice = 0;
                    printf("Operation ist ungueltig!\n");
                    printf("Ergebnis ist %d mit %d Rest. Soll gerundet (r), abgeschnitten (c) oder verworfen (x) werden?\n", ergebnis / x_input, rest);
                    scanf(" %c", &choice);
                    if (choice == 'r'){
                        ergebnis = rest > x_input / 2
                            ? (ergebnis / x_input) + 1
                            : ergebnis / x_input;
                        printf("Ergebnis: %d\n", ergebnis);
                        increment++;
                    }
                    else if(choice == 'c'){
                            ergebnis = ergebnis / x_input;
                            printf("Ergebnis: %d\n", ergebnis);
                            increment++;
                    }
                    else if(choice == 'x'){
                        printf("Ergebnis: %d\n", ergebnis);
                        increment2++;
                    }
                }else{
                    ergebnis = ergebnis / x_input;
                    printf("Ergebnis: %d\n", ergebnis);
                    increment++;
                }
                break;
        }
    }while(op != 'x');
    printf("Programm wird beendet. Es wurden %d gueltige Operationen und %d ungueltige Operationen durchgefuehrt.", increment, increment2);
}
