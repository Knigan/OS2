#include "string.h"
#include "matrixHelpers.h"
#include "CGParallel.h"
#include <cstdio>
#include <omp.h>
#include <cmath>

#define NUMBER_OF_THREADS 8
#define ACCURACY 1e-19
#define COUNT 10

int main() {
    //Размер матрицы
    int mSize;
    printf("Enter the matrix size\n");
    scanf_s("%d", &mSize);
    double total_time = 0.0;
    int count = 0;
    
    double** pMatrix; //Матрица коэффициентов (двумерная)
    double* pVector; //Правая часть линейной системы
    double* pResult; //Результирующий вектор

    //Инициализация массивов для адекватной работы с памятью (N+1 элементов)
    pVector = new double[mSize];
    pResult = new double[mSize];
    pMatrix = new double* [mSize];
    for (int j = 0; j < mSize; j++)
    {
        pMatrix[j] = new double[mSize];
    }

    //Генерация данных
    matrixHelpers::matrix_generation(pMatrix, pVector, mSize);

    //Создаём все объекты
    CGParallel* CGParallelSolver = new CGParallel();

    for (int i = 0; i < COUNT; ++i) 
    {
        //Замер времени
        double startTime = omp_get_wtime();

        CGParallelSolver->resultCalculation(pMatrix, pVector, pResult, mSize, ACCURACY, NUMBER_OF_THREADS);
        //Потраченное время
        double finishTime = omp_get_wtime();

        //Проверяем результат
        bool check = matrixHelpers::testSolvingResult(pMatrix, pVector, pResult, mSize, std::sqrt(ACCURACY*10));

        if (check) {
            printf("\n%d. Calculation time: %lf seconds, dimension: %d, ", i + 1, finishTime - startTime, mSize);
            //Если это один из итерационных методов, то нужно вывести количество итераций
            printf("iterations count: %d\n", CGParallelSolver->get_iterationsCount());

            total_time += finishTime - startTime;
            ++count;
        }
    }

    FILE* file;
    fopen_s(&file, "Solution.txt", "w+t");

    if (file != nullptr) {

        fprintf(file, "Solution: [");

        for (int i = 0; i < mSize; ++i) {
            if (i < mSize - 1) {
                fprintf(file, "%.9lf, ", pResult[i]);
                if (i % 10 == 9)
                    fprintf(file, "\n");
            }
            else
                fprintf(file, "%.9lf]\n", pResult[i]);
        }

        fclose(file);
    }

    if (mSize < 257) {
        printf("\nSolution: ");
        matrixHelpers::printVector(pResult, mSize);
        printf("\n");
    }

    printf("\nAverage time: %lf seconds\n", total_time / count);

    return 0;
}