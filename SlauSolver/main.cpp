#include "string.h"
#include "matrixHelpers.h"
#include "CGParallel.h"
#include <cstdio>
#include <omp.h>
#include <cmath>
#include <string>

#define ACCURACY 1e-9
#define COUNT 20

double testing(int mSize, FILE* TestFile, int number_of_threads = 0) {
    double* pVector = new double[mSize];
    double* pResult = new double[mSize];

    double** pMatrix = new double* [mSize];
    for (int j = 0; j < mSize; j++)
    {
        pMatrix[j] = new double[mSize];
    }

    double total_time = 0.0;
    int count = 0;

    //Генерация данных
    matrixHelpers::matrix_generation(pMatrix, pVector, mSize);

    //Создаём все объекты
    CGParallel* CGParallelSolver = new CGParallel();

    for (int i = 0; i < COUNT; ++i)
    {
        //Замер времени
        double startTime = omp_get_wtime();

        CGParallelSolver->resultCalculation(pMatrix, pVector, pResult, mSize, ACCURACY, number_of_threads);
        //Потраченное время
        double finishTime = omp_get_wtime();

        //Проверяем результат
        bool check = matrixHelpers::testSolvingResult(pMatrix, pVector, pResult, mSize, ACCURACY);

        if (check) {
            printf("\n%d. Calculation time: %.7lf seconds, dimension: %d, ", i + 1, finishTime - startTime, mSize);
            printf("iterations count: %d, number of threads: %d\n", CGParallelSolver->get_iterationsCount(), number_of_threads);
            
            fprintf(TestFile, "\n%d. Calculation time: %.7lf seconds, dimension: %d, ", i + 1, finishTime - startTime, mSize);
            fprintf(TestFile, "iterations count: %d, number of threads: %d\n", CGParallelSolver->get_iterationsCount(), number_of_threads);

            total_time += finishTime - startTime;
            ++count;
        }
    }

    std::string filepath = "Solutions/Solution";
    filepath += std::to_string(number_of_threads) + ".txt";

    FILE* file;
    fopen_s(&file, filepath.c_str(), "w+t");

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

    double average_time = total_time / count;

    printf("\n\nAverage time for %d threads: %.7lf seconds\n\n", number_of_threads, average_time);
    fprintf(TestFile, "\n\nAverage time for %d threads: %.7lf seconds\n\n", number_of_threads, average_time);

    return average_time;
}

int main() {
    //Размер матрицы
    int mSize;
    printf("Enter the matrix size\n");
    scanf_s("%d", &mSize);
    
    double** pMatrix; //Матрица коэффициентов (двумерная)
    double* pVector; //Правая часть линейной системы
    double* pResult; //Результирующий вектор

    FILE* TestFile;
    fopen_s(&TestFile, "Tests.txt", "w+t");

    for (int k = 0; k < 12; ++k) {
        if (k == 0) {
            testing(mSize, TestFile, 1);
        }
        else {
            if (k == 3) {
                testing(mSize, TestFile, 6);
            }

            if (k == 4) {
                testing(mSize, TestFile, 12);
            }

            testing(mSize, TestFile, 1 << k);
        }
    }

    return 0;
}