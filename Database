#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum msgtag {

  NoTag = 0, Important, Work, Personal, ToDo, Later

} msgtag;

typedef struct MsgID{

  char* id;

} MsgID;

typedef struct MsgDetails{

  char* id;
  msgtag tag;
  int year;
  int month;
  int day;

} MsgDetails;

typedef struct Node{

  void* item;
  struct Node* next;
} Node;

Node* addMsgDetails(Node* head, MsgDetails* type){

    Node* newNode = (Node*)(malloc(sizeof(Node)));
    newNode->item=type;
    newNode->next=NULL;
    if(head == NULL){
        return newNode;
    }
    else{
        Node* previous = head;
        Node* temporary = head;
        while(temporary != NULL){
            previous = temporary;
            temporary = temporary->next;
        }
        previous->next = newNode;
        return head;
    }
}

Node* deleteNode(Node* node, void(*deleteMessage)()){

    if(node == NULL){
        return NULL;
    }
    (*deleteMessage)();
    free(node);
    return NULL;
}

Node* deleteList(Node* start, void(*deleteMessage)){

    if(start != NULL){
        deleteList(start->next, deleteMessage);
    }
    return deleteNode(start, deleteMessage);
}

void freeMsgDetails(Node* node){

    MsgDetails* message = node->item;
    free(message->id);
    free(message);
}

void freeMsgIDs(Node* node){

    MsgID* message = node->item;
    free(message);
}

Node* read(Node* Database){

    int tag, year, month, day;
    char* id = malloc(40*sizeof(char));

    printf("\nenter msg metadata (tag,year,month,day,id):");
    scanf("%d,%d,%d,%d,", &tag, &year, &month, &day);
    fgets(id, 40, stdin);
    id = strtok(id,"\n");

    MsgDetails* node = (MsgDetails*)(malloc(sizeof(MsgDetails)));
    node->day = day;
    node->month = month;
    node->year = year;
    node->tag = tag;
    node->id = id;

    return addMsgDetails(Database, node);
}

Node* reverseList (Node* head){

    if((head = NULL) && (head->next != NULL)){
        Node* lastone = head;
        Node* temporary;
        while(lastone->next != NULL){
            lastone = lastone->next;
        }
        while(head != lastone) {
            temporary = head->next;
            head->next = lastone->next;
            lastone->next = head;
            head = temporary;
        }
    }
    return head;
}

Node* addMsgId(Node* head, MsgID* type){

    Node* newHead = (Node*)(malloc(sizeof(Node)));
    newHead->item = type;
    newHead->next = head;
    return newHead;
}

Node* filterList(Node* Database, int(*cmpFunc)(int, MsgDetails*), int rv, int match){

    Node* results = NULL;
    Node* op = Database;
    while(op != NULL){
        MsgDetails* Detail = op->item;
        if((*cmpFunc)(rv, Detail) == match){
            MsgID* msgID = (MsgID*)(malloc(sizeof(MsgID)));
            msgID->id = Detail->id;
            results = addMsgId(results, msgID);
        }
        op = op->next;
    }
    return results;
}

void printResults(Node* results){

    Node* temporary = results;
    while(temporary != NULL){
        MsgID* node = temporary->item;
        printf("\nID: %s", node->id);
        temporary = temporary->next;
    }
    results = deleteList(results, &freeMsgIDs);
}

void printDatabase(Node* Database){

    Node* temporary = Database;
    while(temporary != NULL){
        MsgDetails* node = temporary->item;
        printf("\nID: %s\n  %d-%.2d-%.2d Tag: %d", node->id, node->year, node->month, node->day, node->tag);
        temporary = temporary->next;
    }
}

int matchTag(int tag, MsgDetails* message){

    if (message->tag == tag){
        return 1;
    }
    else{
        return 0;
    }
}

int cmpDate(int value, MsgDetails* message){

    int validated = message->year*10000 + message->month*100 + message->day;
    if(validated == value){
       return 0;
    }
    else if(value > validated){
       return -1;
    }
    else{
        return 1;
    }
}

int cmpYear(int value, MsgDetails* message){

    int validated = message->year;
    if(validated == value){
       return 0;
    }
    else if (value > validated){
        return -1;
    }
    else{
        return 1;
    }
}

void filterTag(Node* Database){

    int input;
    printf("\nwhich tag (0-5)?");
    scanf("%d", &input);
    printResults(filterList(Database, &matchTag, input,1));
}

void filterYear(Node* Database){

    int input;
    printf("\nwhich year?");
    scanf(" %d", &input);
    printResults(filterList(Database, &cmpYear, input, -1));
}

void filterDate(Node* Database, int treffer){

    int input;
    printf("\nwhich date (YYYYMMDD)?");
    scanf("%d", &input);
    printResults(filterList(Database, &cmpDate, input, treffer));
}

char getMenu(){

    char input;

    while(1){
        printf("\ncmd:");
        scanf(" %c", &input);

        switch(input){
            case 'r':   return 'r';
            case 'R':   return 'R';
            case 'p':   return 'p';
            case 't':   return 't';
            case 'y':   return 'y';
            case 'd':   return 'd';
            case 'e':   return 'e';
            case 'q':   return 'q';
        }
    }
}

int main (){

    Node* head = NULL;
    char menuResult;

    printf("\nMsgDB -- Testprogramm");

    while(1){

        menuResult = getMenu();

        switch(menuResult){

            case 'r':   head = read(head);
                        break;
            case 'R':   head = reverseList(head);
                        break;
            case 'p':   printDatabase(head);
                        break;
            case 't':   filterTag(head);
                        break;
            case 'y':   filterYear(head);
                        break;
            case 'd':   filterDate(head,-1);
                        break;
            case 'e':   filterDate(head,0);
                        break;
            case 'q':   deleteList(head, &freeMsgDetails);
                        return 0;
        }
    }
   return 0;
}
