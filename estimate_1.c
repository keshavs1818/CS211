#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// populating and scanning an array with a train word
void scanTrainMatrix(int d1, int d2, FILE *file, double* XMatrix, double* YMatrix) {
    for(int i = 0; i < d2; i++) {
      int index = i * d1;
      *(XMatrix + index) = 1; 
      //printf("%d", one);
    }
    for(int i = 0; i < d2; i++) {
      for(int j = 1; j <= d1; j++) {
        double value;
        int index = (i * d1) + j;
        fscanf(file, "%lf", &value);
        if(index % d1 == 0) {
          //printf("%d\n", index / d1 - 1);
          *(YMatrix + ((index / d1) - 1)) = value;
        } else {
          *(XMatrix + index) = value;
        }
       // *(TrainXMatrix + index) = value;
        //printf("%lf\n", value);
      }
      //*(YMatrix + i) = value;
    }
}

// populating and scanning an array with a data word
void scanDataMatrix(int d1, int d2, double* XMatrix, FILE* file, double* YMatrix) {
   for(int i = 0; i < d2; i++) {
      int index = i * d1;
      *(XMatrix + index) = 1; 
      //printf("%d", one);
    }
    for(int i = 0; i < d2; i++) {
      for(int j = 1; j < d1; j++) {
        double value;
        int index = (i * d1) + j;
        fscanf(file, "%lf", &value);
        *(XMatrix + index) = value;
      }
    }
}

/*void fillIdentity(int squareDimension, double *inMatrix, double *identityMatrix) {
   for(int i = 0; i < squareDimension; i++) {
     for(int j = 0; j < squareDimension; j++) {
       double value;
       int index = (i * squareDimension) + j;
       if(i == j) {
          *(inMatrix + index) = value;
       }
     }
   }
}*/

// Assuming that startMatrix is XTX, I am doing this in Java.
/*public static double[][] inverseMatrix(int squareDimension, double[][] startMatrix) {
  double[][] invertedMatrix = new double[squareDimension][squareDimension];
  double[][] identityMatrix = new double[squareDimension][squareDimension];
  fillIdentityMatrix(identityMatrix);
  for(int i = 0; i < squareDimension - 1; i++) {
    double a = startMatrix[i][i];
    for(int j = 0; j < squareDimension - 1; j++) {
      startMatrix[i][j] /= a;
      identityMatrix[i][j] /= a;
    }
    for(int k = i + 1; k < squareDimension - 1; k++) {
       a = startMatrix[k][i];
       for(int l = 0; l < squareDimension - 1; l++) {
          startMatrix[k][l] - (startMatrix[i][l] * a);
          identityMatrix[k][l] - (identityMatrix[i][l] * a);
       }
    }
  }
  for(int i = squareDimension - 1; i >= 0; i--) {
    for(int k = i - 1; k >= 0; k--) {
       a = startMatrix[k][i];
       for(int l = 0; l < squareDimension - 1; l++) {
          startMatrix[k][l] - (startMatrix[i][l] * a);
          identityMatrix[k][l] - (identityMatrix[i][l] * a);
       }
    }
  }
  return identityMatrix;
}*/
// inversing matrix, Gauss Jordan Elimination
void inverseMatrix(int squareDimension, double *inMatrix, double *inverseMatrix) {
    
}

// transposing matrix
void transposeMatrix(int a, int b, double* inMatrix, double* transposedMatrix) {
  for(int i = 0; i < a; i++) {
    for(int j = 0; j < b; j++) {
      int index = (i * b) + j;
      int transposeIndex = (j * a) + i;
      *(transposedMatrix + transposeIndex) = *(inMatrix + index);
    }
  }
}

// multiplying matrix
void multiplyMatrix(int x, int y, int z, double* inMatrix, double* matrixTemp, double* matrixProduct ) {
    //double value = 0;
    for(int i = 0; i < x; i++) {
      for(int j = 0; j < y; j++) {
        int row = (i*y);
        int index = (i*y) + j;
        double value = 0;
        for(int k = 0; k < z; k++) {
          value += *(inMatrix + row + k) * *(matrixTemp + j + k*y);
          printf("START ITERATION \n");
          printf("%lf %s %lf\n", *(inMatrix + row + k), " * ", *(matrixTemp + j + k*y));
          //printf("%lf\n", value);
          //printf("END ITERATION\n");
        }
        printf("%lf\n", value);
        printf("END ITERATION\n");
        *(matrixProduct + index) = value;
      }
    }
}

void printMatrix(int dimension1, int dimension2, double *inMatrix) {
    for(int i=0; i< dimension1; i++){
      for(int j=0; j< dimension2; j++){
        double value;
        int index = i*dimension2 + j;
        value = *(inMatrix + index);
        printf( "%lf", value );
        if ( j < dimension2-1 ) {
          printf(" ");
        }
        //printf("\n");
      }
      printf("\n");
    }
}

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Error. Please enter only two matrix arguments.\n");
        return 1;
    }

    // Initializes text to test whether train or data and then simply just scans matrix
    // in a certain way
    char* trainText = argv[1];
    char* dataText = argv[2];

    // Opens two files
    FILE* trainFile = fopen(trainText, "r");
    FILE* dataFile = fopen(dataText, "r");
    char text1[100];
    char text2[100];
    fscanf(trainFile, "%s", text1);
    fscanf(dataFile, "%s", text2);
    // Find Attributes And Houses And Read
    int k1;
    int k2;
    fscanf(trainFile, "%d", &k1);
    fscanf(dataFile, "%d", &k2);
    printf("%d %d\n", k1, k2);
    if(k1 != k2) {
        printf("Error. K needs to be the same. \n");
    }
    int houseNumTrain;
    int houseNumData;
    fscanf(trainFile, "%d", &houseNumTrain);
    fscanf(dataFile, "%d", &houseNumData);

    // Malloc everything
    k1 += 1;
    k2 += 1;
    double *TrainXMatrix = malloc(houseNumTrain * k1 * sizeof(double)); 
    double *TrainYMatrix = malloc(houseNumTrain * 1 * sizeof(double));
    double *WeightWMatrix = malloc(k1 * 1 * sizeof(double));
    double *dataYMatrix = malloc(houseNumData * 1 * sizeof(double));
    double *dataXMatrix = malloc(houseNumData * k2 * sizeof(double));

    // Perform necessary operations based on words
    //if(fgets(trainText, 100, trainFile) == "train") {
      scanTrainMatrix(k1, houseNumTrain, trainFile, TrainXMatrix, TrainYMatrix);
    //} else if(fgets(text, 100, trainFile) == "data") {
      scanDataMatrix(k2, houseNumData, dataXMatrix, dataFile, dataYMatrix);
    //}

    // Printing Matrices
    //printf("x_train>>>>>\n");
    //printMatrix(houseNumTrain, k1, TrainXMatrix);
    /*printf("y_train>>>>>\n");
    printMatrix(houseNumTrain, 1, TrainYMatrix);
    printf("y_data>>>>>>> BEFORE\n");
    printMatrix(houseNumData, 1, dataYMatrix);
    printf("x_data>>>>>>>\n");
    printMatrix(houseNumData, k2, dataXMatrix);
    printf("weights>>>>>> BEFORE\n");
    printMatrix(k1, 1, WeightWMatrix);*/

    // Actual Logic
    double *transposedXMatrix = malloc(k1 * houseNumTrain * sizeof(double));
    double *p1_XTX = malloc(k1 * k1 * sizeof(double));
    double *inverse_XTX = malloc(k1 * k1 * sizeof(double));
    double *p2_XTX = malloc(k1 * houseNumTrain * sizeof(double));

    transposeMatrix(houseNumTrain, k1, TrainXMatrix, transposedXMatrix);
    printf("TRANSPOSE>>>>>\n");
    printMatrix(k1, houseNumTrain, transposedXMatrix);

    //multiplyMatrix(k1, k1, houseNumTrain, transposedXMatrix, TrainXMatrix, p1_XTX);
    printf("MULTIPLIED p1_XTX>>>>>>>>>>>\n");
    printMatrix(k1, k1, p1_XTX);
    //inverseMatrix((k1 + 1), p1_XTX, inverse_XTX);
    //multiplyMatrix(k1, k1, houseNumTrain, inverse_XTX, transposedXMatrix, p2_XTX);
    //multiplyMatrix(k1, houseNumTrain, 1, p2_XTX, TrainYMatrix, WeightWMatrix);
    //multiplyMatrix(houseNumData, k2, 1, dataXMatrix, WeightWMatrix, dataYMatrix);*/

    /*printf("DATAY>>>>>>> AFTER\n");
    printMatrix(houseNumData, 1, dataYMatrix);
    printf("WEIGHTS>>>>>> AFTER\n");
    printMatrix(k1, 1, WeightWMatrix);*/


    //fscanf(trainFile1, trainWord);
    //fscanf(dataFile2, dataWord);

    /*int k1;
    int k2;
    fscanf(trainFile, "%d", &k1);
    fscanf(dataFile, "%d", &k2);
    printf("%d %d\n", k1, k2);
    if(k1 != k2) {
        printf("Error. K needs to be the same. \n");
    }
    int houseNumTrain;
    int houseNumData;
    fscanf(trainFile1, "%d", &houseNumTrain);
    fscanf(dataFile2, "%d", &houseNumData);*/
    //printf("%d\n", houseNumData);
    /*double *TrainXMatrix = malloc(houseNumTrain * (k1 + 1) * sizeof(double));
    double *TrainYMatrix = malloc(houseNumTrain * 1 * sizeof(double));
    double *WeightWMatrix = malloc((k1 + 1) * 1 );
    double *dataYMatrix = malloc(houseNumData * 1 * sizeof(double));
    double *dataXMatrix = malloc(houseNumData * k2 * sizeof(double));*/
    /*for(int i = 0; i < (k1 + 1); i++) {
        int one = 1;
        int index = i * (k1 + 1);
        *(TrainXMatrix + index) = one; 
        printf("%d", one);
    }
    for(int i = 0; i < houseNumTrain; i++) {
      for(int j = 1; j <= (k1 + 1); j++) {
        double value;
        int index = (i * (k1 + 1)) + j;
        fscanf(trainFile, "%lf", &value);
        if(index % 5 == 0) {
          *(TrainYMatrix + (index / 5)) = value;
        } else {
          *(TrainXMatrix + index) = value;
        }
       // *(TrainXMatrix + index) = value;
        //printf("%lf\n", value);
      }
    }*/
    /*for(int i = 0; i < (k1 + 1); i++) {
      for(int j = 0; j < houseNumTrain; j++) {
        double value;
        int index = (i * houseNumTrain) + j;
        fscanf(trainFile1, "%lf", &value);
        *(TrainXMatrix + index) = value;
        //printf("%lf\n", value);
      }
    }

    for(int i = 0; i < (k2 + 1); i++) {
      for(int j = 0; j < houseNumData; j++) {
        double value;
        int index = (i * houseNumData) + j;
        fscanf(dataFile2, "%lf", &value);
        *(dataXMatrix + index) = value;
      }
    }

    for(int i = 0; i < (k1 + 1); i++) {
      for(int j = 0; j < houseNumTrain; j++) {
        double value;
        int index = (i * houseNumTrain) + j;
        fscanf(trainFile1, "%lf", &value);
        if((index + 1) % 5 == 0) {
          *(TrainYMatrix + j) = value;
          printf("%lf\n", value);
        }
        //*(TrainXMatrix + index) = value;
        //printf("%lf\n", value);
      }
    }*/
    

    //printMatrix(houseNumTrain, (k1 + 1), TrainXMatrix);
    //printMatrix(houseNumData, k2, dataXMatrix);
    
    
    /*for(int i = 0; i < (k2 + 1); i++) {
      for(int j = 0; j < houseNumData; j++) {
        double value;
        int index = (i * houseNumData) + j;
        fscanf(dataFile2, "%lf", &value);
        *(dataXMatrix + index) = value;
      }
    }*/
    free(p2_XTX);
    free(inverse_XTX);
    free(p1_XTX);
    free(transposedXMatrix);
    free(TrainXMatrix);
    free(TrainYMatrix);
    free(WeightWMatrix);
    free(dataYMatrix);
    free(dataXMatrix);
    fclose(trainFile);
    fclose(dataFile);

    return 0;
}

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 14, 2021
//###################################################

/*#include <stdio.h>
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

void copyMatrix(int dimension, int *inMatrix, int *outMatrix) {
  for(int i = 0; i < dimension; i++) {
    for(int j = 0; j < dimension; j++) {
      int index = (dimension * i) + j;
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
  
  int *inMatrix = malloc(dimension * dimension * sizeof(int));
  for(int i = 0; i < dimension; i++) {
    for(int j = 0; j < dimension; j++) {
      int value;
      int index = (i * dimension) + j;
      fscanf(fptr, "%d", &value);
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
} */
