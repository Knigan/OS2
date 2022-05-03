#include "matrixHelpers.h"
#include <cstdio>
#include <cmath>
#include <limits>
#include <ctime>

void matrixHelpers::printVector(double* matrix, int size) {

    for (int i = 0; i < size; i++) {
        if (i == 0)
            printf("[");
        if (i < size - 1)
            printf("%.9f, ", matrix[i]);
        else
            printf("%.9f]", matrix[i]);
        if (i % 10 == 9)
            printf("\n");
    }
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

    pRightPartVector = new double[Size];
    for (int i = 0; i < Size; i++) {
        pRightPartVector[i] = 0;
        for (int j = 0; j < Size; j++) {
            pRightPartVector[i] += pMatrix[i][j] * pResult[j];
        }
    }

    double sum = 0.0;
    for (int i = 0; i < Size; i++)
    {
        sum += (pRightPartVector[i] - pVector[i]) * (pRightPartVector[i] - pVector[i]);
    }

    if (Size < 10000) //для маленьких размеров матрицы // евклидова норма
    {
        if (sum - Accuracy * Accuracy >= std::numeric_limits<double>::epsilon()) { //remember
            equal = 1;
        }
    }
    else//для больших размеров матрицы
    {
        int sum2 = 0;
        for (int i = 0; i < Size; i++)
        {
            sum2 += pVector[i] * pVector[i];
        }
        if (sum - Accuracy * Accuracy * sum2 >= std::numeric_limits<double>::epsilon()) {
            equal = 1;
        }
    }

    delete[] pRightPartVector;
    return (equal == 0);
}

void matrixHelpers::matrix_generation(double** pMatrix, double* pVector, int Size)
{
    srand(unsigned(clock()));
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = rand() / double(1000);
        for (int j = 0; j <= i; j++)
        {
            if (i != j)
            {
                if (rand() % 10 == 0)
                {
                    //pMatrix[i][j] = pMatrix[j][i] = rand() / double(1000);
                    pMatrix[i][j] = pMatrix[j][i] = 0.0;
                }
                else
                {
                    pMatrix[i][j] = pMatrix[j][i] = 0.0;
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
}