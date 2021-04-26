#include <stdio.h>

void int_array(char A[10][10]){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            A[i][j]='.';
        }
    }
    A[0][0]='A';
}

void print_array(char A[10][10]){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            printf("%c",A[i][j]);
        }
        printf("\n");
    }
}

void n(char A[10][10], int *i, int *j, char *rob){
    if(*i-1 < 0){
        printf("not possible\n");
    }
    else if(A[*i-1][*j]!='.'){
        printf("not possible\n");
    }
    else{
        *i=*i-1;
        A[*i][*j]=(*rob)++;

        print_array(A);
    }
}
void e(char A[10][10], int *i, int *j, char *rob){
    if(*j+1 > 9){
        printf("not possible\n");
    }
    else if(A[*i][*j+1]!='.'){
        printf("not possible\n");
    }
    else{
        *j=*j+1;
        A[*i][*j]=(*rob)++;

        print_array(A);
    }
}
void s(char A[10][10], int *i, int *j, char *rob){
    if(*i+1 > 9){
        printf("not possible\n");
    }
    else if(A[*i+1][*j]!='.'){
        printf("not possible\n");
    }
    else{
        *i=*i+1;
        A[*i][*j]=(*rob)++;

        print_array(A);
    }
}
void w(char A[10][10], int *i, int *j, char *rob){
    if(*j-1 < 0){
        printf("not possible\n");
    }
    else if(A[*i][*j-1]!='.'){
        printf("not possible\n");
    }
    else{
        *j=*j-1;
        A[*i][*j]=(*rob)++;

        print_array(A);
    }
}

int main(){
    char A[10][10];
    int_array(A);
    char b;
    char rob= 'B';
    int i=0;
    int j=0;
    print_array(A);

    while(b!='x'){
        if(rob>'Z'){
            rob='A';
        }

        printf("walk to:\n");
        scanf(" %c", &b);
        if(b=='n'){
            n(A, &i, &j, &rob);
        }
        else if(b=='e'){
            e(A, &i, &j, &rob);
        }
        else if(b=='s'){
            s(A, &i, &j, &rob);
        }
        else if(b=='w'){
            w(A, &i, &j, &rob);
        }
    }
    return 0;
}
