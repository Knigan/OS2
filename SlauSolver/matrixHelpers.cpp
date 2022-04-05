#include "matrixHelpers.h"

void matrixHelpers::printVector(double * matrix, int size) {

    for (int i = 0; i < size; i++) {
        printf("%.4f ", matrix[i]);
    }
    printf("\n");
}

void matrixHelpers::printMatrix(double **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Функция проверяет результат:
 * умножает матрицу на вектор и сравнивает с результатом
 * 
 * @param pMatrix
 * @param pVector
 * @param pResult
 * @param Size
 * @return 
 */

bool matrixHelpers::testSolvingResult(double** pMatrix, double* pVector, double* pResult, int Size, double Accuracy) {
    
    /* Buffer for storing the vector, that is a result of multiplication
    of the linear system matrix by the vector of unknowns */

    double* pRightPartVector;

    // Flag, that shows wheather the right parts vectors are identical or not

    int equal = 0;

    //double Accuracy = 1.e-4; // Comparison accuracy

    pRightPartVector = new double [Size];
    for (int i = 0; i < Size; i++) {
        pRightPartVector[i] = 0;
        for (int j = 0; j < Size; j++) {
            pRightPartVector[i] += pMatrix[i][j] * pResult[j];
        }
    }
    for (int i = 0; i < Size; i++) {
        if (fabs(pRightPartVector[i] - pVector[i]) - Accuracy >= std::numeric_limits<double>::epsilon()) {
            equal = 1;
        }
    }
    if (equal == 1) {
        printf("The result of the algorithm is NOT correct."
                " Check your code.\n");
        return false;
    } else {
        printf("The result of the algorithm is correct.\n");
        return true;
    }
    
    delete [] pRightPartVector;
    
}