#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 2, 2021
//###################################################

int main(int argc, char *argv[]) {
    if ( argc == 1 || argc > 2 ) {
        printf("Error: Please enter One argument to act on!\n");
        return EXIT_FAILURE;
    } 

    char *str = argv[1];
    int arrLength = 2*strlen(str) * sizeof( char);
    char *encodedStr = malloc( arrLength + 1 );
    sprintf(encodedStr, "%s", "" );

    char tempChar=str[0];
    int count = 1;
    char tempStr[1000];

    for(int i=1; i < strlen(str); i++){
        char newChar = str[i];
        if(newChar >= 48 && newChar <= 57) {
            printf("error\n");
            free( encodedStr );
            return EXIT_SUCCESS;
        }
        if( newChar == tempChar ){
            count++;
        } else {
	        //sprintf(encodedStr, "%s%c%d", encodedStr, tempChar, count );
	        sprintf(tempStr, "%s%c%d", encodedStr, tempChar, count );
	        sprintf(encodedStr, "%s", tempStr );

	        tempChar = newChar;
            count = 1;
        }
    }
	//sprintf(encodedStr,  "%s%c%d", encodedStr, tempChar, count );
	sprintf(tempStr, "%s%c%d", encodedStr, tempChar, count );
	sprintf(encodedStr, "%s", tempStr );

    if ( strlen(encodedStr) > strlen(str) ) {
        printf( "%s", str);
    } else {
        printf( "%s", encodedStr);
    }
    printf("\n");

    free( encodedStr );
    return EXIT_SUCCESS;
}
