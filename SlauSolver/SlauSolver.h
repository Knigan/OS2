#pragma once
#include <vector>

struct CRSMatrix
{
	int n;
	int m;
	int nz;
	std::vector<double> val;
	std::vector<int> colIndex; 
	std::vector<int> rowPtr;
};

class CSlauSolver {
public:
	CSlauSolver(void);

	void SLE_Solver_CRS_BICG(CRSMatrix& A, double* b, double eps, int max_iter, double* x, int& count);

	double Dot(double* a, double* b, int n);

	void Sum(double* a, double* b, int n, double alfa = 1);

	void Sum(double* a, double* b, double* res, int n, double alfa = 1);

	void Diff(double* a, double* b, int n);

	void Mult(CRSMatrix& A, double* b, double* res);

	void SolveR(CRSMatrix& A, double* z, double* b, double* r, double alfa = 1);

	void SolveRWithResolveX(CRSMatrix& A, double* z, double* b, double* r, double* x, double* p, double alfa = 1);

	void SolveRT(CRSMatrix& A, double* z, double* b, double* r, double alfa = 1);

	int GetRowIndex(CRSMatrix& A, int index);

	double GetAlfaAndCopyPredArrays(CRSMatrix& A, double* r, double* r_sop, double* p, double* p_sop, double* temp, double* predR, double* predR_sop, int n);

	double GetBetta(double* r, double* r_sop, double* predR, double* predR_sop, int n);

	void ResolvePandPSop(double* p, double* p_sop, double* r, double* r_sop, int n, double betta);

private:
	void GenerateSolution(double* x, int n);
	void Copy(double* a, double* copyA, int n);
	bool IsEnd(double* x0, double* x, int n, double eps);
	bool IsEnd(double* x, int n, double eps);
};
