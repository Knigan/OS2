#pragma once
#include <ctime>
#include <cstdlib>

struct dataGen {
    dataGen() {}
    dataGen(const dataGen& orig) {}
    virtual ~dataGen() {}
    static int dummyDataInitialization(double** pMatrix, double* pVector, int Size);
    static int randomDataInitialization(double** pMatrix, double* pVector, int Size);
    static int matrix_generation(double** pMatrix, double* pVector, int Size);
};

