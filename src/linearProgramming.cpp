#include "linearProgramming.h"
#include <iostream>
#include <limits>

Simplex::Simplex(std::vector<std::vector<double>> matrix, std::vector<double> b, std::vector<double> c) {
    this->A = matrix; // Initialize the coefficients matrix
    this->B = b; // Initialize the constraints vector
    this->C = c; // Initialize the objective function coefficients
    this->rows = matrix.size(); // Get the number of rows in the coefficients matrix
    this->cols = matrix[0].size(); // Get the number of columns in the coefficients matrix
    this->maximum = 0; // Initialize the maximum value of the objective function
    this->isUnbounded = false; // Initialize the unbounded flag
}

bool Simplex::checkOptimality() {
    for (double coeff : C) {
        if (coeff < 0)
            return false; // If any coefficient in the objective function is negative, the solution is not optimal
    }
    return true; // If all coefficients in the objective function are non-negative, the solution is optimal
}

void Simplex::doPivotting(int pivotRow, int pivotColumn) {
    // Perform pivotting operation to make the pivot element 1 and other elements in the pivot column 0
    // Update the coefficients matrix, constraints vector, and objective function coefficients accordingly
    double pivotValue = A[pivotRow][pivotColumn];
    for (int j = 0; j < cols; j++) {
        A[pivotRow][j] /= pivotValue;
    }
    B[pivotRow] /= pivotValue;
    for (int i = 0; i < rows; i++) {
        if (i != pivotRow) {
            double factor = A[i][pivotColumn];
            for (int j = 0; j < cols; j++) {
                A[i][j] -= factor * A[pivotRow][j];
            }
            B[i] -= factor * B[pivotRow];
        }
    }
    double pivotCoeff = C[pivotColumn];
    for (int j = 0; j < cols; j++) {
        C[j] -= pivotCoeff * A[pivotRow][j];
    }
    maximum -= pivotCoeff * B[pivotRow];
}

bool Simplex::simplexAlgorithmCalculation() {
    // Implement the simplex algorithm to find the optimal solution
    while (!checkOptimality()) {
        int pivotColumn = findPivotColumn();
        if (pivotColumn == -1) {
            throw std::runtime_error("Linear programming problem is unbounded.");
        }
        int pivotRow = findPivotRow(pivotColumn);
        doPivotting(pivotRow, pivotColumn);
    }
    return true;
}

int Simplex::findPivotColumn() {
    // Find the pivot column with the most negative coefficient in the objective function
    int pivotColumn = -1;
    double minCoefficient = 0;
    for (int j = 0; j < cols; j++) {
        if (C[j] < minCoefficient) {
            minCoefficient = C[j];
            pivotColumn = j;
        }
    }
    return pivotColumn;
}

int Simplex::findPivotRow(int pivotColumn) {
    // Find the pivot row by selecting the minimum ratio of the constraints to the coefficients in the pivot column
    int pivotRow = -1;
    double minRatio = std::numeric_limits<double>::infinity();
    for (int i = 0; i < rows; i++) {
        if (A[i][pivotColumn] > 0) {
            double ratio = B[i] / A[i][pivotColumn];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }
    return pivotRow;
}

void Simplex::CalculateSimplex() {
    // Perform the simplex algorithm calculation and print the results
    std::cout << "Initial array (Not optimal):" << std::endl;
    print();

    std::cout << std::endl;

    std::cout << "Final array (Optimal solution):" << std::endl;

    simplexAlgorithmCalculation();

    std::cout << "Answers for the Constraints of variables:" << std::endl;
    for (int i = 0; i < A.size(); i++) {
        int count0 = 0;
        int index = 0;
        for (int j = 0; j < rows; j++) {
            if (A[j][i] == 0.0) {
                count0 += 1;
            }
            else if (A[j][i] == 1) {
                index = j;
            }
        }

        if (count0 == rows - 1) {
            std::cout << "variable" << index + 1 << ": " << B[index] << std::endl;
        }
        else {
            std::cout << "variable" << index + 1 << ": " << 0 << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Maximum value: " << maximum << std::endl;
}

void Simplex::print() {
    // Print the coefficients matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << "" << std::endl;
    }
}

std::vector<double> Simplex::solveWithSimplex(const Problem& problem, int max_iterations) {
    // Solve the linear programming problem using the simplex algorithm and return the solution
    Simplex simplex(problem.A, problem.b, problem.c);
    simplex.simplexAlgorithmCalculation();
    std::vector<double> solution = simplex.getSolution();
    return solution;
}

std::vector<double> Simplex::getSolution() {
    // Extract the solution from the basic variables and return it
    std::vector<double> solution(cols, 0); // Initialize solution vector with zeros

    for (const auto& pair : basicVariables) {
        int colIndex = pair.first;
        int rowIndex = pair.second;
        solution[colIndex] = B[rowIndex]; // Assign the value of the basic variable to the corresponding column index
    }

    return solution;
}
