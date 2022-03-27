#pragma once
#include "SlauSolver.h"

constexpr double EPS = 0.000000001;

class SlauSolverTests {

private:

	CSlauSolver solver;

	template <class T>
	bool isInfinite(const T& value) {
		T max_value = std::numeric_limits<T>::max();
		T min_value = -max_value;
		return !(min_value <= value && value <= max_value);
	}
	//bool isInfiniteInt(const int& value);

	template <class T>
	bool AreEqual(T* a, T* b, int n = 0, double eps = EPS) {
		bool res = true;
		for (int i = 0; i < n; i++) {
			if (fabs(a[i] - b[i]) > eps || isInfinite<T>(a[i]) || isInfinite<T>(b[i])) {
				res = false;
				break;
			}
		}
		return res;
	}
	//bool AreEqualInt(int* a, int* b, int n = 0);

public:

	bool DotTest();

	bool SumVectorsTest();
	bool SumVectorsTest2();

	bool DiffVectorsTest();

	bool MultCSRMatrixOnVectorTest();
	bool MultCSRMatrixWithZeroRowOnVectorTest();

	bool SolveRTest();
	bool SolveRTest2();
	bool SolveRTranspTest();
	bool SolveRTranspTest2();

	bool SLE_Solver_CSR_BICG_Test();
	bool SLE_Solver_CSR_BICG_Test2();

	bool GetRowIndexTest();

	bool FinalTest();
};