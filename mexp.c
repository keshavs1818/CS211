#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 7, 2021
//###################################################

void printMatrix(int dimension, int *inMatrix) {
  for(int i=0; i< dimension; i++){
      for(int j=0; j< dimension; j++){
        int value;
        int index = i*dimension + j;
        value = *(inMatrix + index);
        printf( "%d", value );
        if ( j < dimension-1 ) {
            printf(" ");
        }
      }
      printf("\n");
  }
}

void copyMatrix( int dimension, int *inMatrix, int *outMatrix ){
  for(int i=0; i< dimension; i++){
      for(int j=0; j< dimension; j++){
        int index = i*dimension + j;
        *(outMatrix + index) = *(inMatrix + index);
      }
  }
}

void multiplyMatrix( int dimension, int *inMatrix, int *matrixTemp, int *matrixProduct ) {
  for(int i=0; i< dimension; i++){
      for(int j=0; j< dimension; j++){
        int row   = i*dimension;
        int index = i*dimension + j;
        int value = 0;
        for( int innerInd = 0; innerInd < dimension; innerInd++) {
            value += *(inMatrix + row + innerInd) *  *(matrixTemp + j + innerInd*dimension);
        }
        *(matrixProduct + index) = value;
      }
  }
}
//out[i][j] = Left[Row-i] * Right[Column-j]  

int main(int argc, char *argv[]) {
  if ( argc != 2 ) {
      printf("Error: Please enter name of file to act on!\n");
      return EXIT_FAILURE;
  } 

  char *fileName;;
  fileName = argv[1];
  FILE *fptr = fopen( fileName,"r");

  if ( fptr == NULL )  {
      printf("Error!");   
      return EXIT_FAILURE;             
  }

  int dimension;
  fscanf(fptr,"%d", &dimension);

  int *inMatrix = malloc( dimension * dimension * sizeof(int));
  for(int i=0; i< dimension; i++){
      for(int j=0; j< dimension; j++){
        int value;
        int index = i*dimension + j;
        fscanf(fptr,"%d", &value);
        *(inMatrix + index) = value;
      }
  }
  
  //printMatrix(dimension, inMatrix);

  int power;
  fscanf(fptr,"%d", &power);
  //printf( "Power: %d\n", power);

  int *matrixTemp = malloc( dimension * dimension * sizeof(int));
  int *matrixProduct = malloc( dimension * dimension * sizeof(int));

  if ( power == 0) {
    //Identity Matrix
    int value = 1;
    for(int i=0; i< dimension; i++){
        for(int j=0; j< dimension; j++){
            int index = i*dimension + j;
            *(matrixProduct + index) = value;
        }
    }
  } else if ( power == 1 ) {
      copyMatrix( dimension, inMatrix, matrixProduct );
  } else {
    // Multiply
    copyMatrix( dimension, inMatrix, matrixProduct );
    for( int i=2; i <= power; i++ ) {
        copyMatrix( dimension, matrixProduct, matrixTemp );
        multiplyMatrix( dimension, inMatrix, matrixTemp, matrixProduct );
        //printf("Multiplied to Power: %d\n", i);
        //printMatrix(dimension, matrixProduct);
    }
  }

  printMatrix(dimension, matrixProduct);

  free( inMatrix );
  free( matrixTemp );
  free( matrixProduct );
  fclose( fptr );

  return EXIT_SUCCESS;
}