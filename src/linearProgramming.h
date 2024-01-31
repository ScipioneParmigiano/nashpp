#ifndef LINEAR_PROGRAMMING_H
#define LINEAR_PROGRAMMING_H

#include <vector>
#include <stdexcept>
#include <unordered_map>

class Simplex {
private:
    std::vector<std::vector<double>> A; // Coefficents matrix
    std::vector<double> B; // Constraints vector
    std::vector<double> C; // Objective function coefficients
    int rows; // Number of rows in the coefficients matrix
    int cols; // Number of columns in the coefficients matrix
    double maximum; // Maximum value of the objective function
    bool isUnbounded; // Flag indicating if the linear programming problem is unbounded
    std::unordered_map<int, int> basicVariables; // Map to store basic variable indices and their corresponding row indices
    bool checkOptimality(); // Function to check if the current solution is optimal
    void doPivotting(int pivotRow, int pivotColumn); // Function to perform pivotting operation
    bool simplexAlgorithmCalculation(); // Function to perform the simplex algorithm calculation
    int findPivotColumn(); // Function to find the pivot column
    int findPivotRow(int pivotColumn); // Function to find the pivot row
    std::vector<double> getSolution(); // Function to extract the solution

public:
    struct Problem {
        std::vector<std::vector<double>> A; // Coefficients matrix
        std::vector<double> b; // Constraints vector
        std::vector<double> c; // Objective function coefficients
    };

    Simplex(std::vector<std::vector<double>> matrix, std::vector<double> b, std::vector<double> c); // Constructor
    void CalculateSimplex(); // Function to perform the simplex algorithm and print the results
    void print(); // Function to print the coefficients matrix
    std::vector<double> solveWithSimplex(const Problem& problem, int max_iterations = 1000); // Function to solve the linear programming problem
};

#endif // LINEAR_PROGRAMMING_H
