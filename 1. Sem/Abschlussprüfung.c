#include <stdio.h>
#include <stdlib.h>

//struct from assignment
typedef struct Exam{
  char* name;
  int points;
  struct Exam* next;
}Exam;

//Free the memory
void freeList(Exam* head) {

    Exam* current = head;           //start at head
    while(current != NULL) {        //traverse entire list
        Exam* toDelete = current;   //save the "current" pointer
        current = current->next;    //advance to next
        free(toDelete);             //free the saved one
    }
}

//PrintList
void printList(Exam* head) {

    Exam* current = head;                                       //start at head
    while(current != NULL) {                                    //traverse entire list
        printf("%d->%s ", current->points, current->name);      //print the current node
        current = current->next;                                //advance to next
    }
}

//printStatistics
void printResult(Exam* head) {

    Exam* current = head;            //start at head
    int counterP = 0;                //counter for positive exams
    int counterN = 0;                //counter for negative exams

    while(current != NULL) {
            if(current->points < 50){                                               //traverse entire list
                    counterN++;                                                     //increment counter for negative exams
                printf("\nNEG list:%d->%s ", current->points, current->name);       //print negative exams
            }else{
                counterP++;                                                         //increment counter for positive exams
                printf("\nPOS list:%d->%s ", current->points, current->name);        //print positive exams
        }

        current = current->next;     //advance to next
    }
    printf("\nPOS:%d", counterP);    //print number of positive exams
    printf("\nNEG:%d", counterN);    //print number of negative exams
}

//PrintAverage
void printAvg(Exam* head) {

    Exam* current = head;                       //start at head
    double avg;                                 //variable for average
    double valueCounter, nodeCounter;           //variables for calculating average

    while(current != NULL) {                    //traverse entire list
        valueCounter += current->points;        //summing up the the values
        ++nodeCounter;                          //increment the counter
        current = current->next;                //advance to next

    }

    avg = valueCounter/nodeCounter;             //calculating the average
    printf("\nAVG Points: %.2lf", avg);         //printing average
}

//Function to insert the node at the right place
Exam* add(int points, char* name, Exam* head) {

    Exam* newHead = malloc(sizeof(Exam));       //allocate node

    newHead->points = points;                   //putting in the points
    newHead->name = name;                       //putting in the name


    if(head == NULL){                           //we return the allocated node if there is nothing there
        return newHead;
    }

    if(head->next == NULL){                     //if there is one there
        if(head->points < newHead->points){     //if that whats there is smaller than whats new

            head->next = newHead;               //insert after the existing one
            return head;
        }else{
            newHead->next = head;               //else insert before the existing one
            return newHead;
        }
    }

    if(head->points >= newHead->points){        //there is more than one - if that what is there is bigger than whats new

            newHead->next = head;               //let the new one be the first one and the old one the next of the new one
            return newHead;
    }

    Exam* currentNode = head;                   //allocate new node
    while(currentNode != NULL){                 //while the current node is not empty

        if(currentNode->next == NULL){          //if I am at the last one
            currentNode->next = newHead;        //insert after the last one
            break;
        }
        else if((newHead->points >= currentNode->points) && (newHead->points <= currentNode->next->points)){

            newHead->next = currentNode->next;      //if my node is bigger than the current one and smaller than the next one I insert at the current position
            currentNode->next = newHead;            //insert after the current Node
            break;
        }

       currentNode = currentNode->next;             //advance to next
    }
    return head;
}

//Main
int main(){

    Exam* head = NULL;
    char name[20];
    int points;

    while(1){

        printf("\nnew exam: ");
        scanf("%d,%20s", &points, name);

        if(points < 0){
            printList(head);
            printf("\n");
            printResult(head);
            printAvg(head);
            break;
        }

        head = add(points, name, head);
        printList(head);

    }
    freeList(head);

    return 0;
}
