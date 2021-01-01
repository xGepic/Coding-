#include <stdio.h>
#include <stdlib.h>

//Detail Struct
typedef struct intDetails{

    int wert;
    int limit;
}intDetails;

//Linked List
typedef struct Node{

    struct intDetails* detailsList;
    struct Node* next;
}Node;

//Delete Node
Node* deleteNode(Node* node){

    if(node == NULL){
        return NULL;
    }
    free(node);
    return NULL;
}

//Delete List
Node* deleteList(Node* start){

    if(start != NULL){
        deleteList(start->next);
    }
    return deleteNode(start);
}

//Einfügen von Elementen
Node* addIntDetails(Node* head, intDetails* content, int* deleted){

    Node* newNode = (Node*)(malloc(sizeof(Node)));
    newNode->detailsList=content;
    newNode->next=head;

    Node* temp = head;
    Node* previous = newNode;

    while(temp != NULL){
        temp->detailsList->wert += newNode->detailsList->wert;
        if(temp->detailsList->wert > temp->detailsList->limit){
            previous->next = temp->next;
            ++*deleted;
        }
        previous = temp;
        temp = temp->next;
    }
    return newNode;
}

//Durchlaufen einer Liste: Länge einer Liste bestimmen
int sizeOfList(Node* head){

    int size = 0;
    Node* temp = head;
    while(temp != NULL){
        ++size;
        temp = temp->next;
    }
    return size;
}

//Liste ausgeben
void printDatabase(Node* Database, int* deleted){

    Node* temporary = Database;
    while(temporary != NULL){
        intDetails* node = temporary->detailsList;
        printf("%d/%d ", node->wert, node->limit);
        temporary = temporary->next;
    }
}

//Liste ausgeben
void printResult(Node* Database, int* deleted){

    double size = sizeOfList(Database);
    double sum = 0;
    double avg = 0;

    Node* temporary = Database;
    while(temporary != NULL){
        intDetails* node = temporary->detailsList;
        printf("%d/%d ", node->wert, node->limit);
        temporary = temporary->next;
        sum += node->wert;
    }
    avg = sum/size;
    printf("\nDeleted: %d", *deleted);
    printf("\nAVG    : %.2lf",avg);
}

//Einlesen von Elementen
Node* read(Node* Database, int wert, int limit, int* deleted){

    intDetails* node = (intDetails*)(malloc(sizeof(intDetails)));
    node->wert = wert;
    node->limit = limit;

    return addIntDetails(Database, node, deleted);
}

int main(){

    struct Node* head = NULL;
    int wert, limit;
    int* deleted = malloc(sizeof(int));
    *deleted = 0;

    printf("Enter value and limit X/Y:\n");

    while(1){

        scanf("%d/%d", &wert, &limit);
        if(limit < wert){
            continue;
        }

        if(wert == 0){
            printResult(head, deleted);
            deleteList(head);
            break;
        }else{
            head = read(head, wert, limit, deleted);
            printDatabase(head, deleted);
        }
        printf("\nEnter value and limit X/Y:\n");
    }
    return 0;
}
