#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node* next;
};

struct Node *listHead;
struct Node *listPtr1;
struct Node *listPtr2;
int listCount = 0;

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 8, 2021
//###################################################

void insertValue(int inputValue) {
    struct Node *newNode = malloc( sizeof(struct Node) );
    newNode->value = inputValue;
    newNode->next  = NULL;
    if ( listHead == NULL ){
        listHead = newNode;
        listCount++;
        return;
    } 
    
    listPtr2 = listHead;
    listPtr1 = listHead;
    int count = 0;

    while ( listPtr2 != NULL && listPtr2->value < inputValue ) {
        listPtr1 = listPtr2;
        listPtr2 = listPtr2->next;
        count++;
    }
    
    if ( listPtr2 == NULL ) {
        listPtr1->next = newNode;    
         listCount++;
    } else if( listPtr2->value != inputValue ) {
        newNode->next = listPtr2;
        if ( count == 0 ) {
            listHead = newNode;
        } else {
            listPtr1->next = newNode;
        }
        listCount++;
    } else {
        //Do nothing
        free( newNode );
    }
}

void deleteValue(int inputValue) {
    
    if ( listHead == NULL ) {return;} 
    if ( listHead->value == inputValue ){
        listPtr1 = listHead;
        listHead = listHead->next;
        listCount--;
        free( listPtr1 );
        return;
    } 

    listPtr2 = listHead;
    listPtr1 = listHead;
    int count = 0;
    while ( listPtr2 != NULL && listPtr2->value < inputValue ) {
        listPtr1 = listPtr2;
        listPtr2 = listPtr2->next;
        count++;
    }
    if( listPtr2 != NULL && listPtr2->value == inputValue ) {
        if ( count == 0 ) {
            listHead = listPtr2->next;
        } else {
            listPtr1->next = listPtr2->next;
        }
        free( listPtr2 );
        listCount--;
    }
}

void displayList() {
    listPtr2 = listHead;
    printf("%d :", listCount );
    while ( listPtr2 != NULL ) {
        printf( " %d", listPtr2->value);
        listPtr2 = listPtr2->next;
    }
    printf("\n");
}



int main(int argc, char *argv[]) {
  char action = 'i';//initial value
   char in1[1000];
   char in2[1000];
    while (fgets(in1, 1000, stdin )) {
        int value;
        sscanf( in1, "%s %d", in2, &value );
        action = in2[0];
        if ( action != 'i' && action != 'd' ){
            break;
        }

//  while ( action == 'i' || action == 'd' ){
 //     int value = 0;
 //     char inputStr[1000];
 //     char inputValueStr[1000];
 //     scanf("%s", inputStr);
 //     if (inputStr == NULL ){ return EXIT_FAILURE; }
  //    action = inputStr[0];
  //    if ( action != 'i' && action != 'd' ){
  //        return EXIT_FAILURE;
  //    }
      
  //    scanf("%s", inputValueStr);
  //    value = atoi( inputValueStr );
    
      if ( action == 'i' ){
          insertValue( value );
      } else if ( action == 'd' ) {
          deleteValue( value);
      } 
      
      displayList();
  }

  return EXIT_SUCCESS;
}