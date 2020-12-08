#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct carriage {

    char waggon;
    int capacity;

};

struct train {

    struct carriage c[11];
    int length;

};

void printCarriage(struct carriage c){

    if((c.waggon == 'p') || (c.waggon == 's') || (c.waggon == 'd')){
        printf("[%c:%03d]", toupper(c.waggon), c.capacity);
    }else{
        printf("\nInput invalid! Try again: ");
    }
}

void printTrain(struct train* t){

    printf("\nTrain: ");

    if(t -> length == 0){
        printf("No Carriages!");
        return;
    }

    for(int i = 0; i < t ->length; i++){
        if(i != 0){
           printf("-");
        }
        printf("%d:", i);
        printCarriage(t -> c[i]);
    }
    printf(" Length: %d", t -> length);
}

char getMenu(){

    char input;

    while(1){
        printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x): ");
        scanf(" %c", &input);

        switch(input){
            case 'p': return 'p';
            case 'n': return 'n';
            case 's': return 's';
            case 'x': return 'x';
            default: printf("\nInput invalid! Try again: ");
        }
    }
}

struct carriage getCarriage(){

    struct carriage c;

    while(1){
    printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d): ");
    scanf(" %c", &c.waggon);

    if((c.waggon == 'p') || (c.waggon == 's') || (c.waggon == 'd')){

        while (1){
            printf("\nChoose capacity (20 - 130): ");
            scanf("%d", &c.capacity);
            if((c.capacity <= 130) && (c.capacity >= 20)){
                return c;
                }else{
                    printf("\nInput invalid! Try again: ");
                }
            }
        }else{
            printf("\nInput invalid! Try again: ");
        }
    }
}

int getPosition(int length){

    unsigned int position = 0;

    while(1){

        printf("\nChoose position for the new carriage (0-%d):", length);
        scanf("%d",&position);

        if(position <= length){

            return position;

        }else {
            printf("\nInput invalid! Try again: ");
        }
    }
}

int insertCarriage(struct train* t, int position, struct carriage c){

    if(t -> length >= 10) return -1;

    if(position > t -> length) return -2;

    if((c.waggon == 'd') && (position != 0)) return -3;

    for(int i = t ->length; i >= position; i--){

       t -> c[i+1] = t -> c[i];
    }
    t -> c[position] = c;

    t->length++;

    return 0;
}

int sumCapacity(struct train* t, char waggon){

    int sum = 0;

    for(int i = 0; i <= t -> length;i++){
        if((t -> c[i].waggon) == waggon){
            sum += t -> c[i].capacity;
        }
    }
    return sum;
}

  void printTrainStats(struct train* t){

    printTrain(t);

    printf("\nCapacities:");

    printf("\n  Passenger: %d", sumCapacity(t, 'p'));
    printf("\n  Sleeper: %d", sumCapacity(t, 's'));
    if((sumCapacity(t, 'd')) < 20){
        printf("\n  Diner: %d - invalid", sumCapacity(t, 'd'));
    }else{
        printf("\n  Diner: %d", sumCapacity(t, 'd'));
    }
}

int main(){

    char menuResult;
    int insertResult = 0;
    struct train t;
    t.length = 0;

    while(1){

        menuResult = getMenu();

        switch(menuResult){
            case 'x':   return 0;
            case 'p':   printTrain(&t);
                        break;
            case 'n':   insertResult = insertCarriage(&t,getPosition(t.length),getCarriage());
                        break;
            case 's':   printTrainStats(&t);
                        break;
        }
        switch(insertResult){
            case -1:    printf("\nError: Train too long!");
                        break;
            case -2:    printf("\nError: Position not possible!");
                        break;
            case -3:    printf("Error: Diner only possible in first position!");
        }
        insertResult = 0;
    }
    return 0;
}
