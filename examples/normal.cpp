#include "../src/nashmatrix.h"
#include <iostream>
#include <tuple>
#include "../src/nashmatrix.cpp"


int main() {
    // Example payoff matrices (modify as needed)
    std::vector<std::vector<int>> payoffA = {{4, 2}, {1, 4}};
    std::vector<std::vector<int>> payoffB = {{4, 1}, {2, 4}};

    // Create NashMatrix object
    NashMatrix game(payoffA, payoffB);

    // Return the defined matrices
    auto matrices = game.payoffMatrices();

    // Print the matrices
    std::cout << "Matrix A:\n";
    for (const auto& row : std::get<0>(matrices)) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }


    std::cout << "\nMatrix B:\n";
    for (const auto& row : std::get<1>(matrices)) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // Find Nash equilibria
    game.findNashEquilibria();

    // Check if a strategy is a best response
    int player = 0; // Player A
    int strategy = 0; // Strategy to check

    if (game.isBestResponse(player, strategy)) {
        std::cout << "\nStrategy " << strategy << " for Player " << player << " is a best response.\n";
    } else {
        std::cout << "\nStrategy " << strategy << " for Player " << player << " is not a best response.\n";
    }

    // Example: Compute and print payoff for specific strategies
    int strategyA = 0;
    int strategyB = 1;

    auto payoffs = game.computePayoffPure(strategyA, strategyB);
    int p1 = std::get<0>(payoffs);
    int p2 = std::get<1>(payoffs);
    
    std::cout << std::endl;
    std::cout << "Payoff for Player A: " << p1 << std::endl;
    std::cout << "Payoff for Player B: " << p2 << std::endl;

    // Example: Compute and print payoff for mixed strategies
    std::vector<double> mixedStrategyA = {0.5, 0.5};
    std::vector<double> mixedStrategyB = {0.5, 0.5};

    auto payoffs_m = game.computePayoffMix(mixedStrategyA, mixedStrategyB);
    double pm1 = std::get<0>(payoffs_m);
    double pm2 = std::get<1>(payoffs_m);
    
    std::cout << std::endl;
    std::cout << "Payoff for Player A: " << pm1 << std::endl;
    std::cout << "Payoff for Player B: " << pm2 << std::endl;
    std::cout << std::endl;

    // Find Pareto optimal strategies
    game.sociallyOptimal();

    return 0;
}
