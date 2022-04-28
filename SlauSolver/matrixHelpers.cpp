#include "matrixHelpers.h"
#include <cstdio>
#include <cmath>
#include <limits>
#include <ctime>

void matrixHelpers::printVector(double* vector, int size) {

    for (int i = 0; i < size; i++) {
        if (i == 0)
            printf("[");
        if (i < size - 1)
            printf("%.9f, ", vector[i]);
        else
            printf("%.9f]", vector[i]);
        if (i % 10 == 9)
            printf("\n");
    }
}

void matrixHelpers::printMatrix(CSRMatrix& matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.4f ", matrix.at(i, j));
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

bool matrixHelpers::testSolvingResult(CSRMatrix& matrix, double* pVector, double* pResult, int Size, double Accuracy) {
    
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
            pRightPartVector[i] += matrix.at(i, j) * pResult[j];
        }
    }
    if (Size < 10000) //для маленьких размеров матрицы
    {
        for (int i = 0; i < Size; i++) 
        {
            if (fabs(pRightPartVector[i] - pVector[i]) - Accuracy >= std::numeric_limits<double>::epsilon()) 
            {
                equal = 1;
            }
        }
    }
    else//для больших размеров матрицы
    {
        int sum = 0;
        for (int i = 0; i < Size; i++)
        {
            sum += pVector[i] * pVector[i];
        }
        for (int i = 0; i < Size; i++)
        {
            if ((fabs(pRightPartVector[i] - pVector[i])) / std::sqrt(sum) - Accuracy >= std::numeric_limits<double>::epsilon())
            {
                equal = 1;
            }
        }
    }
    
    
    delete [] pRightPartVector;
    return (equal == 0);
}

void matrixHelpers::matrix_generation(double** pMatrix, double* pVector, int Size, CSRMatrix& matrix, int degree)
{
    //srand(unsigned(clock()));
    srand(2314069263278);
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = rand() / double(1000);
        for (int j = 0; j <= i; j++)
        {
            if (i != j)
            {
                if (rand() % degree == 0)
                {
                    pMatrix[i][j] = pMatrix[j][i] = rand() / double(1000);
                    //pMatrix[i][j] = pMatrix[j][i] = 0.0;
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

    double** pMatrix2 = new double* [Size];
    for (int i = 0; i < Size; ++i) {
        pMatrix2[i] = new double[Size];
    }


    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            /*pMatrix2[i][j] = 0;
            for (int k = 0; k < Size; ++k) {
                pMatrix2[i][j] += pMatrix[i][k] * pMatrix[k][j];
            }*/
            if (i == j) {
                pMatrix2[i][j] = pMatrix[i][j] * pMatrix[i][j];
            }
            else {
                pMatrix2[i][j] = 0.0;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            if (pMatrix2[i][j] >= 1.e-9) {
                ++count;
            }
        }
    }

    matrix.count = count;
    matrix.values = new double[count];
    matrix.columns = new int[count];
    matrix.rows = new int[count];

    int k = 0;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            if (fabs(pMatrix2[i][j]) >= 1.e-9) {
                matrix.values[k] = pMatrix2[i][j];
                matrix.columns[k] = j;
                matrix.rows[k] = i;
                ++k;
                if (k == count) {
                    break;
                }
            }
        }
        if (k == count) {
            break;
        }
    }

    /*for (int i = 0; i < Size; ++i) {
        delete[] pMatrix2[i];
    }
    delete[] pMatrix2;*/
}