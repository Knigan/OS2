#include "string.h"
#include "dataGen.h"
#include "matrixHelpers.h"
#include "CGParallel.h"

#define NUMBER_OF_THREADS 4
#define ACCURACY 1.e-19

int main() {
    //Размер матрицы
    int mSize;
    printf("Enter the matrix size\n");
    scanf_s("%d", &mSize);
    printf("Matrix size is %d\n", mSize);
    int count = 0;
    double average_time = 0;

    do 
    {
        double** pMatrix; //Матрица коэффициентов (двумерная)
        double* pVector; //Правая часть линейной системы
        double* pResult; //Результирующий вектор

        //Инициализация массивов для адекватной работы с памятью (N+1 элементов)
        pVector = new double[mSize];
        pResult = new double[mSize];
        pMatrix = new double* [mSize];
        for (int i = 0; i < mSize; i++) 
        {
            pMatrix[i] = new double[mSize];
        }

        //Генерация данных
        dataGen::matrix_generation(pMatrix, pVector, mSize);

        //Создаём все объекты
        CGParallel* CGParallelSolver = new CGParallel();

        //Замер времени
        double startTime = omp_get_wtime();

        CGParallelSolver->resultCalculation(pMatrix, pVector, pResult, mSize, ACCURACY, NUMBER_OF_THREADS);
        matrixHelpers::printMatrix(pMatrix, mSize);
        matrixHelpers::printVector(pVector, mSize);
        matrixHelpers::printVector(pResult, mSize);
        //Потраченное время
        double finishTime = omp_get_wtime();

        //Проверяем результат
        int check = matrixHelpers::testSolvingResult(pMatrix, pVector, pResult, mSize, std::sqrt(ACCURACY*10));

        if (check) {
            printf("\nCalculation time: %lf seconds, dimension: %d ", finishTime - startTime, mSize);
            //Если это один из итерационных методов, то нужно вывести количество итераций
            printf("iterations_count: %d\n", CGParallelSolver->get_iterationsCount());

            average_time += finishTime - startTime;
        }

        ++count;

        /*if (count == 100) {
            if (mSize < 17) {
                printf("\n");
                matrixHelpers::printMatrix(pMatrix, mSize);
                printf("\n");
                matrixHelpers::printVector(pVector, mSize);
            }
        }*/

    } while (count < 100);

    printf("\nAverage time: %lf seconds\n", average_time / count);

    return 0;
}