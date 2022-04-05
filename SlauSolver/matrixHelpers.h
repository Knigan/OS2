#pragma once
#include <cstdio>
#include <cmath>
#include <limits>

struct matrixHelpers {
    matrixHelpers(){}
    matrixHelpers(const matrixHelpers& orig) {}
    virtual ~matrixHelpers() {}
    
    static void printVector(double * matrix, int size);
    static void printMatrix(double **matrix, int size);
    static bool testSolvingResult(double** pMatrix, double* pVector, double* pResult, int Size, double Accuracy);
};

