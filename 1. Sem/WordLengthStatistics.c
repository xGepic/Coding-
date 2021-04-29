#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void invalid(void){
    puts("NOT VALID");
    exit(EXIT_FAILURE);
}

int main(void){
    int length[80]={0};
    int i, ch, word_len=0;

    printf(": ");
    while(1){
        ch=getchar();
        if(isalpha(ch)){
            ++word_len;
        } else if(ch == ' ' || ch == '.'){
            if(word_len>79)
                invalid();
            if(word_len)
                length[word_len-1]++;//-1: to 0 origin
            if(ch == '.')
                break;
            word_len = 0;
        } else {
            invalid();
        }
    }
    for(i=0;i<sizeof(length)/sizeof(*length);++i){
        if(length[i])
            printf("Length %d: %d\n", i+1, length[i]);
    }
    return 0;
}
