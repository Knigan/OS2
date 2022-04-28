#pragma once

struct CSRMatrix {
    int count;
    double* values;
    int* columns;
    int* rows;

    CSRMatrix() : count(0), values(nullptr), columns(nullptr), rows(nullptr) {}
    CSRMatrix(const CSRMatrix& orig) : count(orig.count), values(orig.values), columns(orig.columns), rows(orig.rows) {}
    virtual ~CSRMatrix() {
        delete[] values;
        delete[] columns;
        delete[] rows;
    }

    double at (const int i, const int j) {
        for (int k = 0; k < count; ++k) {
            if (rows[k] == i && columns[k] == j) {
                return values[k];
            }
        }
        return 0.0;
    }
};

struct matrixHelpers {
    matrixHelpers() {}
    matrixHelpers(const matrixHelpers& orig) {}
    virtual ~matrixHelpers() {}
    
    static void printVector(double* vector, int size);
    static void printMatrix(CSRMatrix& matrix, int size);
    static bool testSolvingResult(CSRMatrix& matrix, double* pVector, double* pResult, int Size, double Accuracy);
    static void matrix_generation(double** pMatrix, double* pVector, int Size, CSRMatrix& matrix, int degree);
};

