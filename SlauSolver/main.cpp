#include "SlauSolverTests.h"
#include <chrono>

int main() {
	auto begin = std::chrono::steady_clock::now();

	SlauSolverTests tests;
//#pragma omp parallel num_threads(2)
	tests.FinalTest();

	auto end = std::chrono::steady_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "mcs" << std::endl;

	return 0;
}