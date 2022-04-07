#include "dataGen.h"

/**
 * Function for simple initialization of the matrix and the vector elements 
 * @param pMatrix
 * @param pVector
 * @param Size
 * @return 
 */
int dataGen::dummyDataInitialization(double** pMatrix, double* pVector, int Size) {
    int i, j; // Loop variables Отформатировано: русский
    for (i = 0; i < Size; i++) {
        pVector[i] = i + 1;
//        for (j = 0; j < Size; j++) {
//            if (j <= i) {
//                pMatrix[i][j] = 1;
//            } else {
//                pMatrix[i][j] = 0;
//            }
//        }
        for (j = 0; j < Size; j++) 
        {
            if (j == i) 
            {
                pMatrix[i][j] = (double) rand() / RAND_MAX * 1000;
            } 
            else 
            {
                pMatrix[i][j] = 0;
            }
        }

    }
    return 0;
}

/**
 * Function for random initialization of the matrix and the vector elements
 * 
 * @param pMatrix
 * @param pVector
 * @param Size
 * @return 
 */
int dataGen::randomDataInitialization(double** pMatrix, double* pVector, int Size) {
    int i, j; // Loop variables
    srand(unsigned(clock()));
    for (i = 0; i < Size; i++) 
    {
        pVector[i] = rand() / double(1000);
         for (j = 0; j < Size; j++) 
         {
             pMatrix[i][j] = pMatrix[j][i] = rand() / double(1000);
         }
    }
    return 0;
}

int dataGen::matrix_generation(double** pMatrix, double* pVector, int Size)
{
    int i, j; // Loop variables
    for (i = 0; i < Size; i++) 
    {
        pVector[i] = rand() / double(1000);
        for (j = 0; j < Size; j++)
        {
            if (i != j)
            {
                if (rand() % 10 == 9)
                {
                    pMatrix[i][j] = rand() / double(1000);
                    //pMatrix[i][j] = 0.0;
                }
                else
                {
                    pMatrix[i][j] = 0.0;
                }
            }
            else
            {
                pMatrix[i][j] = rand() / double(1000);
                if (fabs(pMatrix[i][j]) < 1.e-9)
                {
                    pMatrix[i][j] += 1.0;
                }
            }
        }
    }
    return 0;
}
