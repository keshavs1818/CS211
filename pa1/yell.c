#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 2, 2021
//###################################################

int main(int argc, char *argv[]) {
    if ( argc == 1  || argc > 2 ) {
        printf("Error: Please enter One argument to act on!\n");
        return EXIT_FAILURE;
    } 
    
    char *inputStr = argv[1];
    int length = strlen( inputStr );
    if ( length >= 1 ) {
        for(int i=0; i < length; i++ ) {
            printf( "%c", toupper( inputStr[i] ) );
        }
        printf("!!\n");
    }
    return EXIT_SUCCESS;
}
