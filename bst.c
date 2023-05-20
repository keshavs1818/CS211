
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 10, 2021
//###################################################

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

struct Node *bstHead;
struct Node *bstPtr1;
struct Node *bstPtr2;
int bstCount = 0;

void insertValue(int value) {
    if ( bstHead == NULL ){
        struct Node *newNode = malloc( sizeof(struct Node) );
        newNode->value = value;
        newNode->left  = NULL;
        newNode->right  = NULL;
        bstHead = newNode;
        bstCount++;
        printf("inserted\n");
        return;
    } 
    
    bstPtr1 = bstHead;
    bstPtr2 = bstHead;
    int found = 0;
    while ( bstPtr2 != NULL && found != 1 ) {
        if ( value < bstPtr2->value ) {
            bstPtr1 = bstPtr2;
            bstPtr2 = bstPtr2->left;
        } else if ( value > bstPtr2->value ) {
            bstPtr1 = bstPtr2;
            bstPtr2 = bstPtr2->right; 
        } else if ( value == bstPtr2->value ) {
            found = 1;
            printf("not inserted\n");
            return;
        }
    }
    if ( bstPtr2 == NULL ) {
        struct Node *newNode = malloc( sizeof(struct Node) );
        newNode->value = value;
        newNode->left  = NULL;
        newNode->right  = NULL;
        if ( value < bstPtr1->value ) {
            bstPtr1->left = newNode;
        } else if ( value > bstPtr1->value ) {
            bstPtr1->right = newNode;
        }     
        printf("inserted\n");
        bstCount++;
    }
}

void searchValue( int value ) {
    bstPtr2 = bstHead;
    int found = 0;
    while ( bstPtr2 != NULL && found != 1 ) {
        if ( value < bstPtr2->value ) {
            bstPtr2 = bstPtr2->left;
        } else if ( value > bstPtr2->value ) {
            bstPtr2 = bstPtr2->right; 
        } else if ( value == bstPtr2->value ) {
            found = 1;
        }
    }
    if ( found ) {
        printf("present\n");
    } else {
        printf("absent\n");        
    }

}

void printBST(struct Node *bstPtr) {
    if ( bstPtr == NULL ) {
        return;
    }

    printf( "(" );
    printBST( bstPtr->left );

    printf( "%d", bstPtr->value);

    printBST( bstPtr->right );
    printf( ")" );
}

int findLargestValue(struct Node *bstPtr) {
    while( bstPtr->right != NULL ) {
        bstPtr = bstPtr->right;
    }
    int value = bstPtr->value;
    return value;
}


void deleteValue(int value) {
    
    if ( bstHead == NULL ) {printf("absent\n"); return;} 
    bstPtr2 = bstHead;
    if ( bstHead->value == value ){
        if ( bstHead->left == NULL  &&  bstHead->right == NULL ){
            bstHead = NULL;
        } else if ( bstHead->left == NULL ) {
            bstHead = bstHead->right;
        } else if ( bstHead->right == NULL ) {
            bstHead = bstHead->left;
        } else {
            int value = findLargestValue( bstHead->left );
            deleteValue( value );
            bstHead->value = value;
            return;
        }
        printf("deleted\n");
        free(bstPtr2);
        bstCount--;
        return;
    } 

    bstPtr1 = bstHead;
    bstPtr2 = bstHead;
    int found = 0;
    int leftOrRight = 0;

    while ( bstPtr2 != NULL && found != 1 ) {
        if ( value < bstPtr2->value ) {
            bstPtr1 = bstPtr2;
            bstPtr2 = bstPtr2->left;
            leftOrRight = -1;
        } else if ( value > bstPtr2->value ) {
            bstPtr1 = bstPtr2;
            bstPtr2 = bstPtr2->right;
            leftOrRight = 1; 
        } else if ( value == bstPtr2->value ) {
            found = 1;
        }
    }
    if ( found == 1 ) {
        if ( bstPtr2->left == NULL  &&  bstPtr2->right == NULL ){
            if ( leftOrRight == -1 ) {
                bstPtr1->left = NULL;
            } else if ( leftOrRight == 1 ) {
                bstPtr1->right = NULL;
            }
        } else if ( bstPtr2->left == NULL ) {
            if ( leftOrRight == -1 ) {
                bstPtr1->left = bstPtr2->right;
            } else if ( leftOrRight == 1 ) {
                bstPtr1->right = bstPtr2->right;
            }
        } else if ( bstPtr2->right == NULL ) {
            if ( leftOrRight == -1 ) {
                bstPtr1->left = bstPtr2->left;
            } else if ( leftOrRight == 1 ) {
                bstPtr1->right = bstPtr2->left;
            }
        } else {
            int value = findLargestValue( bstPtr2->left );
            deleteValue( value );
            bstPtr1->value = value;
            return;
        }
        printf("deleted\n");
        free(bstPtr2 );
        bstCount--;
    } else {
        printf("absent\n");
    }

}


int main(int argc, char *argv[]) {
   char action = 'i';   //initial value

   char in1[1000];
   char in2[1000];
    while (fgets(in1, 1000, stdin )) {
        int value;
        sscanf( in1, "%s %d", in2, &value );
        action = in2[0];
        if ( action != 'i' && action != 's' && action != 'p' && action != 'd' ){
            break;
        }
//   while ( action == 'i' || action == 's' || action == 'p' || action == 'd' ){
    //  char inputStr[1000];
    //  char inputValueStr[1000];
    //  scanf("%s", inputStr);
    //  if (inputStr == NULL ){ return EXIT_FAILURE; }
    //  action = inputStr[0]; 

      if ( action == 'i' ){
 //         scanf("%s", inputValueStr);
 //         value = atoi( inputValueStr );;
          insertValue( value );
      } else if ( action == 's' ) {
        //  scanf("%s", inputValueStr);
        //  value = atoi( inputValueStr );
          searchValue( value);
      } else if ( action == 'p' ) {
            printBST( bstHead );
            printf("\n");
      } else if ( action == 'd' ) {
         // scanf("%s", inputValueStr);
         // value = atoi( inputValueStr );;
          deleteValue( value);
      }     

     //scanf("%s", inputStr);
     //action = inputStr[0];
  }
 
  return EXIT_SUCCESS;
}