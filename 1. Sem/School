#include <stdio.h>
#include <stdlib.h>

struct class {
        int year;
        char index;
        int pupilCounter;
        struct class *next;
    };

struct school {
        struct class* classList;
    };

int isNull(struct school* s){

    if(s == NULL){
        printf("\nSchool: no classes");
        return 1;
    }else{
        return 0;
    }
}

void printSchool(struct school* s){

    static int sum;
    static int counter;

    printf("\n%d%c - %d",s->classList->year,s->classList->index,s->classList->pupilCounter);

    sum += s->classList->pupilCounter;
    counter++;

    if(s->classList != NULL){
        printSchool(s);
    }
    printf("\nTotal: %d pupils - %d class(es)", sum, counter);

    printf("\nSchool is operating since %d year(s)", s->classList->year);

    sum = 0;
    counter = 0;
    return;
}

void printYear(struct school* s, int input){

    static int sum;
    static int counter;


    if(s->classList->year == input){
        printf("\n%d%c - %d",s->classList->year,s->classList->index,s->classList->pupilCounter);

        sum += s->classList->pupilCounter;
        counter++;
    }

    if(s->classList != NULL){
        printYear(s, input);
    }

    if(counter == 0){
        printf("\nNo such class");
    }else{
        printf("\nTotal: %d pupils - %d class(es)", sum, counter);
    }

    sum = 0;
    counter = 0;
    return;
}

void printClass(struct school* s, int year, char index){

    if((s->classList->index == index) && (s->classList->year == year)){
        printf("Class %c has %d pupils", index, s->classList->pupilCounter);
        return;
    }
    if(s->classList != NULL){
        printClass(s,year,index);
    }else{
        printf("No such class");
    }
    return;
}

void addClassFirst(struct school* school, int pupilCounter, char index){

    struct class* newClass=(struct class*)malloc(sizeof(struct class));
    newClass->year=1;
    newClass->index=index;
    newClass->pupilCounter=pupilCounter;
    newClass->next=school->classList;
    school->classList=newClass;
}

void freeclasses(struct school* s){

    for(struct class * i = s->classList;i->next==NULL;i=i->next){
        i->year=i->year+1;
    }

    for(struct class * i = s->classList; i->next==NULL;){

        if(i->year==5){
            struct class* z=i;
            i=i->next;
            free(z);
        }
        else{
            i=i->next;
        }
    }
}

void newS(struct school* s){

    int students=0;
    char n;

    printf("\nEnter the number of students:");
    scanf("%d", &students);

    if(students<15){
        printf("\nNot enough students");
        return;
    }

    else if(students<30){
            n='A';
        addClassFirst(s, students, n);
    }

    else if(students<40){
        int v=0;
        int v2=0;
        if(students%2==0){
            v=students/2;
            n='A';
            addClassFirst(s, v, n);
            n='B';
            addClassFirst(s, v, n);
        }
    else if(students%2==1){
            v=students/2;
            v2=v+1;
            n='B';
            addClassFirst(s, v2, n);
            n='A';
            addClassFirst(s, v, n);
        }
    }

    else{
        int i;
        for(i=26;(i=2); i--){
            if(students/i>=20){
                break;
            }
        }
        int h=i-(students%i);
        int v=students/i;
        for(int k=i; k>h; k--){
            n='A'+k;
            addClassFirst(s, v+1, n);
        }
        for(int j=h; j>0; j--){
            n='A'+j;
            addClassFirst(s, v, n);
        }
    }
    freeclasses(s);

}

char getMenu(){

    char input;

    while(1){
        printf("\nChoose action: school (s), year (y), class (c), new (n), exit (x): ");
        scanf(" %c", &input);

        switch(input){
            case 's': return 's';
            case 'y': return 'y';
            case 'c': return 'c';
            case 'n': return 'n';
            case 'x': return 'x';
            default: printf("\nInvalid selection");
        }
    }
}

int main(){

    struct school* head=(struct school*)malloc(sizeof(struct school));
    head->classList = NULL;
    char menuResult;
    int yearInput;
    int classNumber;
    char classIndex;
    int nullResult = 0;

     while(1){

        menuResult = getMenu();

        switch(menuResult){
            case 'x':   return 0;

            case 'y':   nullResult = isNull(head);
                        if(nullResult != 0){
                            break;
                        }
                        printf("\nEnter a year (1-4): ");
                        scanf("%d", &yearInput);
                        printYear(head, yearInput);
                        break;

            case 's':   nullResult = isNull(head);
                        if(nullResult != 0){
                            break;
                        }
                        printSchool(head);
                        break;

            case 'c':   nullResult = isNull(head);
                        if(nullResult != 0){
                            break;
                        }
                        printf("\nEnter a class (e.g.: 2B): ");
                        scanf("%d%c",&classNumber,&classIndex);
                        printClass(head,classNumber,classIndex);
                        break;

            case 'n':   newS(head);
                        break;
        }
     }
     free(head);
     return 0;
}
