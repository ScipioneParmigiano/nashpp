#include "../src/linearProgramming.h"
#include "../src/linearProgramming.cpp"
#include <iostream>

int main() {
    std::vector<std::vector<double>> A = {{2, 1}, {1, 1}, {0, 1}};
    std::vector<double> b = {20, 10, 5};
    std::vector<double> c = {5, 4};

    Simplex::Problem problem{A, b, c};
    
    Simplex simplex(A, b, c);
    simplex.CalculateSimplex();

    std::cout << "\nSolving with simplex algorithm:\n";
    std::vector<double> solution = simplex.solveWithSimplex(problem);

    std::cout << "\nSolution:\n";
    for (size_t i = 0; i < solution.size(); ++i) {
        std::cout << "x[" << i << "] = " << solution[i] << std::endl;
    }

    return 0;
}
