#include "SlauSolverTests.h"

/*bool SlauSolverTests::isInfinite(const double& value) {
	double max_value = std::numeric_limits<double>::max();
	double min_value = -max_value;
	return !(min_value <= value && value <= max_value);
}

bool SlauSolverTests::AreEqual<double>(double* a, double* b, int n = 0, double eps = EPS) {
	bool res = true;
	for (int i = 0; i < n; i++)
	{
		if (fabs(a[i] - b[i]) > eps || isInfinite(a[i]) || isInfinite(b[i]))
		{
			res = false;
			break;
		}
	}

	return res;
}*/

bool SlauSolverTests::DotTest() {
	double expected = 10;

	double a[]{ 1, 2, 3 };
	double b[]{ 3, 2, 1 };

	double res = solver.Dot(a, b, 3);

	return AreEqual<double>(&expected, &res);
}

bool SlauSolverTests::SumVectorsTest() {
	double expected[]{ 4, 4, 4 };

	double a[]{ 1, 2, 3 };
	double b[]{ 3, 2, 1 };

	solver.Sum(a, b, 3);

	return AreEqual<double>(a, expected, 3);
}

bool SlauSolverTests::SumVectorsTest2() {
	double expected[]{ 7, 6, 5 };

	double a[]{ 1, 2, 3 };
	double b[]{ 3, 2, 1 };

	double* resVector = new double[3];

	solver.Sum(a, b, resVector, 3, 2);

	return AreEqual<double>(resVector, expected, 3);
}

bool SlauSolverTests::DiffVectorsTest() {
	double expected[]{ -2, 0, 2 };

	double a[]{ 1, 2, 3 };
	double b[]{ 3, 2, 1 };

	solver.Diff(a, b, 3);

	return AreEqual<double>(a, expected, 3);
}

bool SlauSolverTests::MultCSRMatrixOnVectorTest() {
	/*
	10, 0, 0, -2, 0, 0
	3, 9, 0, 0, 0, 3,
	0, 7, 8, 7, 0, 0,
	3, 0, 8, 7, 5, 0,
	0, 8, 0, 9, 9, 13,
	0, 4, 0, 0, 2, -1
	*/
	std::vector<double> val =
	{
		10, -2, 3, 9, 3, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1
	};
	std::vector<int> colIndex =
	{
		0, 3, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5
	};
	std::vector<int> rowPtr =
	{
		0, 2, 5, 8, 12, 16, 19
	};

	CSRMatrix matrix = {};
	matrix.n = 6;
	matrix.m = 6;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] =
	{
		1, 1, 1, 1, 1, 1
	};

	double expectedResult[] =
	{
		8, 15, 22, 23, 39, 5
	};

	double* res = new double[6];

	solver.Mult(matrix, b, res);

	return AreEqual<double>(res, expectedResult, 6);
}

bool SlauSolverTests::MultCSRMatrixWithZeroRowOnVectorTest() {
	/*
	10, 0, 0, -2, 0, 0
	0, 0, 0, 0, 0, 0,
	0, 7, 8, 7, 0, 0,
	3, 0, 8, 7, 5, 0,
	0, 8, 0, 9, 9, 13,
	0, 4, 0, 0, 2, -1
	*/
	std::vector<double> val =
	{
		10, -2, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1
	};
	std::vector<int> colIndex =
	{
		0, 3, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5
	};
	std::vector<int> rowPtr =
	{
		0, 2, 2, 5, 9, 13, 16
	};

	CSRMatrix matrix = {};
	matrix.n = 6;
	matrix.m = 6;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] =
	{
		1, 1, 1, 1, 1, 1
	};

	double expectedResult[] =
	{
		8, 0, 22, 23, 39, 5
	};

	double* res = new double[6];

	solver.Mult(matrix, b, res);
	
	return AreEqual<double>(res, expectedResult, 6);
}

bool SlauSolverTests::SolveRTest() {
	/*
	10, 0, 0, -2, 0, 0
	3, 9, 0, 0, 0, 3,
	0, 7, 8, 7, 0, 0,
	3, 0, 8, 7, 5, 0,
	0, 8, 0, 9, 9, 13,
	0, 4, 0, 0, 2, -1
	*/
	std::vector<double> val =
	{
		10, -2, 3, 9, 3, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1
	};
	std::vector<int> colIndex =
	{
		0, 3, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5
	};
	std::vector<int> rowPtr =
	{
		0, 2, 5, 8, 12, 16, 19
	};

	CSRMatrix matrix = {};
	matrix.n = 6;
	matrix.m = 6;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] =
	{
		1, 1, 1, 1, 1, 1
	};

	double expectedResult[] =
	{
		-7, -14, -21, -22, -38, -4
	};

	double alfa = -1;

	double r[] =
	{
		1, 1, 1, 1, 1, 1
	};

	solver.SolveR(matrix, b, r, r, alfa);

	return AreEqual<double>(r, expectedResult, 6);
}

bool SlauSolverTests::SolveRTest2() {
	/*
	2, 3, -4, 1
	1, 0, 0, 4
	-1, -1, 2, -1
	2, -1, -1, 2
	*/

	std::vector<double> val =
	{
		2, 3, -4, 1, 1, 4, -1, -1, 2, -1, 2, -1, -1, 2
	};
	std::vector<int> colIndex =
	{
		0, 1, 2, 3, 0, 3, 0, 1, 2, 3, 0, 1, 2, 3
	};
	std::vector<int> rowPtr =
	{
		0, 4, 6, 10, 14
	};

	CSRMatrix matrix = {};
	matrix.n = 4;
	matrix.m = 4;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] =
	{
		1, 1, 1, 1
	};

	double expectedResult[] =
	{
		-1, -4, 2, -1
	};

	double alfa = -1;

	double r[] =
	{
		1, 1, 1, 1
	};

	solver.SolveR(matrix, b, r, r, alfa);

	return AreEqual<double>(r, expectedResult, 4);
}

bool SlauSolverTests::SolveRTranspTest() {
	/*
	10, 0, 0, -2, 0, 0
	3, 9, 0, 0, 0, 3,
	0, 7, 8, 7, 0, 0,
	3, 0, 8, 7, 5, 0,
	0, 8, 0, 9, 9, 13,
	0, 4, 0, 0, 2, -1
	*/
	std::vector<double> val =
	{
		10, -2, 3, 9, 3, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1
	};
	std::vector<int> colIndex =
	{
		0, 3, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5
	};
	std::vector<int> rowPtr =
	{
		0, 2, 5, 8, 12, 16, 19
	};

	CSRMatrix matrix = {};
	matrix.n = 6;
	matrix.m = 6;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] =
	{
		1, 1, 1, 1, 1, 1
	};

	double expectedResult[] =
	{
		//-7, -14, -21, -22, -38, -4
		-15, -27, -15, -20, -15, -14
	};

	double alfa = -1;

	double r[] =
	{
		1, 1, 1, 1, 1, 1
	};

	solver.SolveRT(matrix, b, r, r, alfa);

	return AreEqual<double>(r, expectedResult, 6);
}

bool SlauSolverTests::SolveRTranspTest2() {
	/*
	2, 3, -4, 1
	1, 0, 0, 4
	-1, -1, 2, -1
	2, -1, -1, 2
	*/

	std::vector<double> val =
	{
		2, 3, -4, 1, 1, 4, -1, -1, 2, -1, 2, -1, -1, 2
	};
	std::vector<int> colIndex =
	{
		0, 1, 2, 3, 0, 3, 0, 1, 2, 3, 0, 1, 2, 3
	};
	std::vector<int> rowPtr =
	{
		0, 4, 6, 10, 14
	};

	CSRMatrix matrix = {};
	matrix.n = 4;
	matrix.m = 4;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] =
	{
		1, 1, 1, 1
	};

	double expectedResult[] =
	{
		-3, 0, 4, -5
	};

	double alfa = -1;

	double r[] =
	{
		1, 1, 1, 1
	};

	solver.SolveRT(matrix, b, r, r, alfa);

	return AreEqual<double>(r, expectedResult, 4);
}

bool SlauSolverTests::SLE_Solver_CSR_BICG_Test() {
	/*
	2, 1, 1
	1, -1, 0,
	3, -1, 2
	*/

	std::vector<double> val =
	{
		2, 1,  1, 1, -1, 3, -1, 2
	};
	std::vector<int> colIndex =
	{
		0, 1, 2, 0, 1, 0, 1, 2
	};
	std::vector<int> rowPtr =
	{
		0, 3, 5, 8
	};

	CSRMatrix matrix = {};
	matrix.n = 3;
	matrix.m = 3;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] = {
		2, -2, 2
	};

	double expectedX[] = {
		-1, 1, 3
	};

	double* x = new double[3];

	int count = 0;

	solver.SLE_Solver_CSR_BICG(matrix, b, 0.001, 100, x, count);

	return AreEqual<double>(x, expectedX, 3, 0.001);
}

bool SlauSolverTests::SLE_Solver_CSR_BICG_Test2() {
	/*
	2, 3, -4, 1
	1, 0, 0, 1
	-1, -1, 2, -1
	2, -1, -1, 2
	*/

	std::vector<double> val =
	{
		2, 3, -4, 1, 1, 1, -1, -1, 2, -1, 2, -1, -1, 2
	};
	std::vector<int> colIndex =
	{
		0, 1, 2, 3, 0, 3, 0, 1, 2, 3, 0, 1, 2, 3
	};
	std::vector<int> rowPtr =
	{
		0, 4, 6, 10, 14
	};

	CSRMatrix matrix = {};
	matrix.n = 4;
	matrix.m = 4;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	double b[] = {
		0, -1, 1, -2
	};

	double expectedX[] = {
		1, 0, 0, -2
	};

	double* x = new double[4];

	int count = 0;

	solver.SLE_Solver_CSR_BICG(matrix, b, 0.001, 100, x, count);

	return AreEqual<double>(x, expectedX, 4, 0.001);
}

/*bool SlauSolverTests::isInfiniteInt(const int& value) {
	int max_value = std::numeric_limits<int>::max();
	int min_value = -max_value;
	return !(min_value <= value && value <= max_value);
}

bool SlauSolverTests::AreEqual<double>Int(int* a, int* b, int n = 0) {
	bool res = true;
	for (int i = 0; i < n; i++)
	{
		if (abs(a[i] - b[i]) > 0 || isInfinite(a[i]) || isInfinite(b[i]))
		{
			res = false;
			break;
		}
	}

	return res;
}*/

bool SlauSolverTests::GetRowIndexTest() {
	/*
	10, 0, 0, -2, 0,
	3, 9, 0, 0, 0, 3,
	0, 7, 8, 7, 0, 0,
	3, 0, 8, 7, 5, 0,
	0, 8, 0, 9, 9, 13,
	0, 4, 0, 0, 2, -1
	*/
	std::vector<double> val =
	{
		10, -2, 3, 9, 3, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1
	};
	std::vector<int> colIndex =
	{
		0, 4, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5
	};
	std::vector<int> rowPtr =
	{
		0, 2, 5, 8, 12, 16, 19
	};

	CSRMatrix matrix = {};
	matrix.n = 6;
	matrix.m = 6;
	matrix.val = val;
	matrix.rowPtr = rowPtr;
	matrix.colIndex = colIndex;

	int res1 = solver.GetRowIndex(matrix, 0);
	int res2 = solver.GetRowIndex(matrix, 2);
	int res3 = solver.GetRowIndex(matrix, 9);
	int res4 = solver.GetRowIndex(matrix, 14);

	int expectedRes1 = 0;
	int expectedRes2 = 1;
	int expectedRes3 = 3;
	int expectedRes4 = 4;

	return
		AreEqual<int>(&expectedRes1, &res1) &&
		AreEqual<int>(&expectedRes2, &res2) &&
		AreEqual<int>(&expectedRes3, &res3) &&
		AreEqual<int>(&expectedRes4, &res4);
}

bool SlauSolverTests::FinalTest() {
	if (DotTest())
		std::cout << "DotTest has been finished succesfully" << std::endl;
	else
		std::cerr << "DotTest has been failed" << std::endl;

	if (SumVectorsTest())
		std::cout << "SumVectorsTest has been finished succesfully" << std::endl;
	else
		std::cerr << "SumVectorsTest has been failed" << std::endl;

	if (SumVectorsTest2())
		std::cout << "SumVectorsTest2 has been finished succesfully" << std::endl;
	else
		std::cerr << "SumVectorsTest2 has been failed" << std::endl;

	if (DiffVectorsTest())
		std::cout << "DiffVectorsTest has been finished succesfully" << std::endl;
	else
		std::cerr << "DiffVectorsTest has been failed" << std::endl;

	if (MultCSRMatrixOnVectorTest())
		std::cout << "MultCSRMatrixOnVectorTest has been finished succesfully" << std::endl;
	else
		std::cerr << "MultCSRMatrixOnVectorTest has been failed" << std::endl;

	if (MultCSRMatrixWithZeroRowOnVectorTest())
		std::cout << "MultCSRMatrixWithZeroRowOnVectorTest has been finished succesfully" << std::endl;
	else
		std::cerr << "MultCSRMatrixWithZeroRowOnVectorTest has been failed" << std::endl;

	if (SolveRTest())
		std::cout << "SolveRTest has been finished succesfully" << std::endl;
	else
		std::cerr << "SolveRTest has been failed" << std::endl;

	if (SolveRTest2())
		std::cout << "SolveRTest2 has been finished succesfully" << std::endl;
	else
		std::cerr << "SolveRTest2 has been failed" << std::endl;

	if (SolveRTranspTest())
		std::cout << "SolveRTranspTest has been finished succesfully" << std::endl;
	else
		std::cerr << "SolveRTranspTest has been failed" << std::endl;

	if (SolveRTranspTest2())
		std::cout << "SolveRTranspTest2 has been finished succesfully" << std::endl;
	else
		std::cerr << "SolveRTranspTest2 has been failed" << std::endl;

	if (SLE_Solver_CSR_BICG_Test())
		std::cout << "SLE_Solver_CSR_BICG_Test has been finished succesfully" << std::endl;
	else
		std::cerr << "SLE_Solver_CSR_BICG_Test has been failed" << std::endl;

	if (SLE_Solver_CSR_BICG_Test2())
		std::cout << "SLE_Solver_CSR_BICG_Test2 has been finished succesfully" << std::endl;
	else
		std::cerr << "SLE_Solver_CSR_BICG_Test2 has been failed" << std::endl;

	if (GetRowIndexTest())
		std::cout << "GetRowIndexTest has been finished succesfully" << std::endl;
	else
		std::cerr << "GetRowIndexTest has been failed" << std::endl;

	return
		DotTest() &&
		SumVectorsTest() &&
		SumVectorsTest2() &&
		DiffVectorsTest() &&
		MultCSRMatrixOnVectorTest() &&
		MultCSRMatrixWithZeroRowOnVectorTest() &&
		SolveRTest() &&
		SolveRTest2() &&
		SolveRTranspTest() &&
		SolveRTranspTest2() &&
		SLE_Solver_CSR_BICG_Test() &&
		SLE_Solver_CSR_BICG_Test2() &&
		GetRowIndexTest();
}