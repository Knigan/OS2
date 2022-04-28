#pragma once
#include "matrixHelpers.h"

class CGParallel {
public:
    CGParallel() : iterationsCount(0) {}
    CGParallel(const CGParallel& orig) : iterationsCount(orig.iterationsCount) {}
    virtual ~CGParallel() {}
    void resultCalculation(CSRMatrix& matrix, double* pVector, double* pResult, int Size, double Accuracy, int NUMBER_OF_THREADS = 0);
    int get_iterationsCount();
private:
    double diff(double *vector1, double* vector2, int Size);
    int iterationsCount;
};

