#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//###################################################
//#  Programmer: Keshav Subramaniyam
//#  Date: October 23, 2021
//#  Assignment: 2, Machine Learning Algorithm
//###################################################

// populating and scanning an array with a train word
void scanTrainMatrix(int d1, int d2, FILE *file, double* XMatrix, double* YMatrix) { 
    for(int i = 0; i < d2; i++) { 
        int index = i * d1; 
        *(XMatrix + index) = 1; 
    } 
    for(int i = 0; i < d2; i++) { 
        for(int j = 1; j <= d1; j++) { 
            double value; 
            int index = (i * d1) + j; 
            fscanf(file, "%lf", &value); 
            if(index % d1 == 0) { 
                *(YMatrix + ((index / d1) - 1)) = value; 
            } else { 
                *(XMatrix + index) = value; 
            } 
        }
    }
}
// populating and scanning an array with a data word
void scanDataMatrix(int d1, int d2, FILE* file, double* XMatrix, double* YMatrix) { 
    for(int i = 0; i < d2; i++) { 
        int index = i * d1; 
        *(XMatrix + index) = 1; 
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

void initializeMatrix(int rows, int columns, double* initializedMatrix) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            int index = (i * columns) + j;
            *(initializedMatrix + index) = 0;
        }
    }
}

void fillIdentityMatrix(int squareDimension, double *inMatrix) { 
    for(int i = 0; i < squareDimension; i++) { 
      for(int j = 0; j < squareDimension; j++) { 
         int index = (i * squareDimension) + j; 
         if(i == j) { 
            *(inMatrix + index) = 1; 
         } else {
             *(inMatrix + index) = 0;
         }
       } 
    }
}

void printMatrix(int dimension1, int dimension2, double *inMatrix) { 
    for(int i=0; i< dimension1; i++) { 
        for(int j=0; j< dimension2; j++){ 
            double value; 
            int index = i*dimension2 + j; 
            value = *(inMatrix + index); 
            printf( "%.0lf", value ); 
            if ( j < dimension2-1 ) { 
                printf(" "); 
            } 
        } 
        printf("\n"); 
    }
}

// Assuming that startMatrix is XTX, I am doing this in Java.
// Gauss Jordan Elimination
/*
procedure invert(M : n × n matrix)
    N ← n × n identity matrix
    for p ← 0, 1, · · · , n − 1 do
        f ← Mp,p
        divide Mp by f
        divide Np by f
        for i ← p + 1, · · · , n − 1 do
            f ← Mi,p
            subtract Mp × f from Mi
            subtract Np × f from Ni
        end for
    end for

    for p ← n − 1, · · · , 0 do
        for i ← p − 1, · · · , 0 do
            f ← Mi,p
            subtract Mp × f from Mi
            subtract Np × f from Ni
        end for
    end for
    return N
end procedur
*/
void inverseMatrix(int sqDim, double *startMatrix, double *invertedMatrix) { 
    fillIdentityMatrix(sqDim, invertedMatrix); 
    //printf("--------------------------------Inside inverseMat (1) \n");  printMatrix(sqDim, sqDim, startMatrix);    
    for(int p = 0; p < sqDim; p++) { 
        double f = *(startMatrix + p*sqDim + p);
        for(int j = 0; j < sqDim; j++) {
            if ( f != 0) {
                *(startMatrix + (p*sqDim) + j) /= f;
                *(invertedMatrix + (p*sqDim) + j) /= f; 
            }
        } 

        for(int i = p + 1; i < sqDim; i++) { 
            double f = *(startMatrix + (i*sqDim) + p);
            for(int j = 0; j < sqDim; j++) {
                *(startMatrix    + (i*sqDim) + j)     -=   ( *(startMatrix    + (p*sqDim) + j) * f );
                *(invertedMatrix + (i*sqDim) + j)     -=   ( *(invertedMatrix + (p*sqDim) + j) * f );
            }
        }
    }
    //printf("--------------------------------Inside inverseMat (2) \n");  printMatrix(sqDim, sqDim, startMatrix);    

    for(int p = sqDim - 1; p >= 0; p--) {
        for(int i = p - 1; i >= 0; i--) {
            double f = *(startMatrix + (i * sqDim) + p);
            for(int k = 0; k < sqDim; k++) {
                *(startMatrix    + (i*sqDim) + k )    -=    ( *(startMatrix    + (p*sqDim) + k) * f);
                *(invertedMatrix + (i*sqDim) + k )    -=    ( *(invertedMatrix + (p*sqDim) + k) * f);
            }
        }
    }
    //printf("--------------------------------Inside inverseMat (3) \n");  printMatrix(sqDim, sqDim, startMatrix);    
}

// transposing matrix
void transposeMatrix(int rows, int columns, double* inMatrix, double* transposedMatrix) { 
   for(int i = 0; i < rows; i++) { 
        for(int j = 0; j < columns; j++) { 
            int index = (i * columns) + j; 
            int transposeIndex = (j * rows) + i; 
            *(transposedMatrix + transposeIndex) = *(inMatrix + index); 
        } 
    }

}
// multiplying matrix

void multiplyMatrix(int R1, int C1_R2, int C2, double* matrix_1, double* matrix_2, double* matrixProduct ) { 
    for(int i = 0; i < R1; i++) { 
        for(int j = 0; j < C2; j++) { 
            int index = (i*C2) + j; 
            double value = 0; 
            for(int k = 0; k < C1_R2; k++) { 
                value += *(matrix_1 + (i*C1_R2) + k) * *(matrix_2 + (k*C2) + j ) ; 
            } 
            *(matrixProduct + index) = value;
        }
    }
}

int main(int argc, char** argv) { 
    if(argc != 3) { 
        printf("Error. Please enter only two matrix arguments.\n");
        return 1;
    }
    // Initializes text to test whether train or data and then simply just scans matrix // in a certain way 
    char* trainText = argv[1]; char* dataText = argv[2];
    // Opens two files 
    FILE* trainFile = fopen(trainText, "r"); 
    FILE* dataFile = fopen(dataText, "r"); 
    char text1[100]; char text2[100]; 
    fscanf(trainFile, "%s", text1); 
    fscanf(dataFile, "%s", text2); 
    // Find Attributes And Houses And Read 
    if ( strcmp(text1, "train") != 0  ||  strcmp(text2, "data") !=0  ){
        printf("#### ERROR: The Train and Data file do not have the right words!!\n");
        return 1;
    }
    int k1; int k2; 
    fscanf(trainFile, "%d", &k1); 
    fscanf(dataFile, "%d", &k2); 
    //printf("# of Attributes:  Train: %d    Data: %d\n", k1, k2); 
    if(k1 != k2) { 
        printf("Error. K needs to be the same. \n"); 
    } 
    int houseNumTrain; int houseNumData; 
    fscanf(trainFile, "%d", &houseNumTrain); 
    fscanf(dataFile, "%d", &houseNumData);
    //printf("# of Houses:      Train: %d    Data: %d\n", houseNumTrain, houseNumData); 

    // Malloc everything 
    k1 += 1; 
    k2 += 1; 
    double *TrainXMatrix = malloc(houseNumTrain * k1 * sizeof(double)); 
    double *TrainYMatrix = malloc(houseNumTrain * 1 * sizeof(double)); 
    double *dataXMatrix = malloc(houseNumData * k2 * sizeof(double));
    double *dataYMatrix = malloc(houseNumData * 1 * sizeof(double)); 
    double *WeightWMatrix = malloc(k1 * 1 * sizeof(double)); 

    // Perform necessary operations based on words 
    scanTrainMatrix(k1, houseNumTrain, trainFile, TrainXMatrix, TrainYMatrix); 
    scanDataMatrix(k2, houseNumData, dataFile, dataXMatrix, dataYMatrix); 
    // Printing Matrices 
    //printf("x_train>>>>>\n");          printMatrix(houseNumTrain, k1, TrainXMatrix);
    //printf("y_train>>>>>\n");          printMatrix(houseNumTrain, 1, TrainYMatrix); 
    //printf("x_data>>>>>>>\n");         printMatrix(houseNumData, k2, dataXMatrix); 
    //printf("y_data>>>>>>> BEFORE\n");  printMatrix(houseNumData, 1, dataYMatrix); 
    //printf("weights>>>>>> BEFORE\n");  printMatrix(k1, 1, WeightWMatrix);
    // Actual Logic 
    double *transposedXMatrix = malloc(k1 * houseNumTrain * sizeof(double)); 
    double *p1_XTX = malloc(k1 * k1 * sizeof(double)); 
    double *inverse_XTX = malloc(k1 * k1 * sizeof(double)); 
    double *p2_XTY = malloc(k1 * 1 * sizeof(double));
    
    initializeMatrix(k1, houseNumTrain, transposedXMatrix);
    initializeMatrix(k1, k1, p1_XTX);
    initializeMatrix(k1, k1, inverse_XTX);
    initializeMatrix(k1, 1, p2_XTY);

    transposeMatrix(houseNumTrain, k1, TrainXMatrix, transposedXMatrix);
    //printf("TRANSPOSE>>>>>\n");  printMatrix(k1, houseNumTrain, transposedXMatrix);

    //W = (XT.X)−1  XT.Y
    multiplyMatrix(k1, houseNumTrain, k1, transposedXMatrix, TrainXMatrix, p1_XTX);
    //printf("MULTIPLIED p1_XTX>>>>>>>>>>>\n");  printMatrix(k1, k1, p1_XTX);    
    
    //W = (p1_XTX)−1 . XT.Y
    inverseMatrix(k1, p1_XTX, inverse_XTX); 
    
    //W = inverse_XTX . XT.Y
    //printf("is p1_XTX Identity>>>>>>>>>>>\n");  printMatrix(k1, k1, p1_XTX);    
    //printf("inverse_XTX>>>>>>>>>>>\n");  printMatrix(k1, k1, inverse_XTX);    

    multiplyMatrix(k1, houseNumTrain, 1, transposedXMatrix, TrainYMatrix, p2_XTY); 
    //printf("MULTIPLIED p2_XTY>>>>>>>>>>>\n");  printMatrix(k1, 1, p2_XTY);    

    //W = inverse_XTX . p2_XTY

    multiplyMatrix(k1, k1, 1, inverse_XTX, p2_XTY, WeightWMatrix);
    //printf("MULTIPLIED WEIGHTS>>>>>>>>>>>\n");  printMatrix(k1, 1, WeightWMatrix);

    multiplyMatrix(houseNumData, k2, 1, dataXMatrix, WeightWMatrix, dataYMatrix);
    //printf("-----------------------MULTIPLIED DATA PRICE>>>>>>>>>>>\n");  
    printMatrix(houseNumData, 1, dataYMatrix);
 
    free(p2_XTY); 
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
/*
    //------------------------------------------Inverse Tesing BEGIS
    int dim = 3;
    double *mat1 = malloc(dim * dim * sizeof(double));
    double *invMat = malloc(dim * dim * sizeof(double));
    double *mat2 = malloc(dim * dim * sizeof(double));
    double *checkMat = malloc(dim * dim * sizeof(double));
    initializeMatrix(dim, dim, mat1);
    initializeMatrix(dim, dim, invMat);
    initializeMatrix(dim, dim, mat2);
    initializeMatrix(dim, dim, checkMat);

    *(mat1 + 0) = 4.0;    *(mat2 + 0) = 4.0;
    *(mat1 + 1) = 3.0;    *(mat2 + 1) = 3.0;
    *(mat1 + 2) = 3.0;    *(mat2 + 2) = 3.0;
    *(mat1 + 3) = 2.0;    *(mat2 + 3) = 2.0;
    *(mat1 + 4) = 4.0;    *(mat2 + 4) = 4.0;
    *(mat1 + 5) = 3.0;    *(mat2 + 5) = 3.0;
    *(mat1 + 6) = 3.0;    *(mat2 + 6) = 3.0;
    *(mat1 + 7) = 2.0;    *(mat2 + 7) = 2.0;
    *(mat1 + 8) = 2.0;    *(mat2 + 8) = 2.0;

    printMatrix(dim, dim, mat1);
    inverseMatrix(dim, mat1, invMat);
    printf("--------------------invMat\n"); printMatrix(dim, dim, invMat);
    multiplyMatrix(dim, dim, dim, invMat, mat2, checkMat);
    printf("--------------------CheckMat\n"); printMatrix(dim, dim, checkMat);

    free(checkMat);
    free(mat2);
    free(invMat);
    free(mat1);
    //------------------------------------------Inverse Tesing ENDS
*/
/*
   ///Check Invese begin
    //Test
    double *xtx_2 = malloc(k1 * k1 * sizeof(double)); 
    for(int i=0; i<k1; i++)  {
        for(int j = 0; j < k1; j++) {
            int index = (i*k1) + j;
            *(xtx_2 + index) = *(p1_XTX + index);
        }
    }
    //

    double *checkMat = malloc(k1 * k1 * sizeof(double)); 
    multiplyMatrix(k1, k1, k1, inverse_XTX, xtx_2, checkMat);
    printf("CHECK MAT          >>>>>>>>>>>\n"); printMatrix(k1, k1, checkMat);
    free(xtx_2);
    free(checkMat);
    //Check Invers End
*/