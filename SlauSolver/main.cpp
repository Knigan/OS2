#include "string.h"
#include "matrixHelpers.h"
#include "CGParallel.h"
#include <cstdio>
#include <omp.h>
#include <cmath>
#include <string>

#define ACCURACY 1e-9
#define COUNT 10

double testing(int mSize, int number_of_threads = 0) {
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
            //Если это один из итерационных методов, то нужно вывести количество итераций
            printf("iterations count: %d, number of threads: %d\n", CGParallelSolver->get_iterationsCount(), number_of_threads);

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

    if (mSize < 257) {
        printf("\nSolution: ");
        matrixHelpers::printVector(pResult, mSize);
        printf("\n");
    }

    double average_time = total_time / count;

    printf("\nAverage time for %d threads: %.7lf seconds\n", number_of_threads, average_time);
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

    //Инициализация массивов для адекватной работы с памятью (N+1 элементов)

    FILE* file;
    fopen_s(&file, "Tests.txt", "w+t");

    if (file != nullptr) {
        for (int i = 0; i < 14; ++i) {
            int k;
            if (i == 3) {
                k = 6;
            }
            else {
                if (i == 5) {
                    k = 12;
                }
                else {
                    if (i == 0) {
                        k = 1;
                    }
                    else {
                        k = 2 << (i - 1);
                    }
                }
            }

            fprintf(file, "Average time for %d threads is equal to %.7lf seconds\n", k, testing(mSize, k));
        }
        fclose(file);
    }

    return 0;
}