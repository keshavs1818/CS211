#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 3, 2021
//###################################################

int main(int argc, char *argv[]) {
    
    if ( argc == 1 || argc > 2 ) {
        printf("Error: Please enter One argument to act on!\n");
        return EXIT_FAILURE;
    } 
    char *inputStr = argv[1];

    char ch;
    char chStack;
    
    int stackLimit = strlen(inputStr);
    char* stack = malloc( stackLimit*sizeof(char) );
    int counter = 0;
    //bool outBounds = false;

    for (int i=0; i<strlen(inputStr); i++) {
        ch = inputStr[i];

        if ( ch == '{' || ch == '(' || ch == '[' ) {
            stack[counter] = ch;
            counter++;
            //printf(">>>>>OPEN \n");   
        } else if ( ch == '}' || ch == ')' || ch == ']' ) {
            //printf(">>>>>>CLOSE \n");
            if ( counter > 0 ) {
                counter--; 
                chStack = stack[counter];
            } else if(counter == 0) {
                chStack = ' ';
            }
            bool hasSameParantheses = (chStack == '(' && ch == ')');
            bool hasSameBraces = (chStack == '{' && ch == '}');
            bool hasSameBrackets = (chStack == '[' && ch == ']');
            if(!hasSameParantheses && !hasSameBraces && !hasSameBrackets) {
                printf("%d: %c\n", i, ch);
                //chStack = ' ';
                free(stack);
                return EXIT_FAILURE;
            }
            /*if ( chStack == '{' && ch == '}' ) {
            } else if ( chStack == '(' && ch == ')' ) {
            } else if ( chStack == '[' && ch == ']' ) {
            } else {
                printf("%d: %c", i, ch);
                free( stack );
                return EXIT_FAILURE;
            }*/
        } else {
            //Ignore character
        }
    }
    if ( counter > 0 ) {
        printf( "open: " );

        while ( counter > 0 ) {
            counter--; 
            chStack = stack[counter];
            if ( chStack == '{' ) {
                printf( "}");
            } else if ( chStack == '(' ) {
                printf(")");
            } else if ( chStack == '[' ) {
                printf("]");
            } 
        }
        printf("\n");
        free( stack );
        return EXIT_FAILURE;
    }
    
    free( stack );
    return EXIT_SUCCESS;
}
