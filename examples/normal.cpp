#include "../nashmatrix.h"
#include <iostream>

int main() {
    // Example payoff matrices (modify as needed)
    std::vector<std::vector<int>> payoffA = {{4, 2}, {1, 4}};
    std::vector<std::vector<int>> payoffB = {{4, 1}, {2, 4}};

    // Create NashMatrix object
    NashMatrix game(payoffA, payoffB);

    game.printPayoffMatrices();

    // Find Nash equilibria
    game.findNashEquilibria();

    // Example: Compute and print payoff for specific strategies
    int strategyA = 0;
    int strategyB = 1;

    game.computePayoffPure(strategyA, strategyB);

    // Example: Compute and print payoff for mixed strategies
    std::vector<double> mixedStrategyA = {0.5, 0.5};
    std::vector<double> mixedStrategyB = {0.5, 0.5};

    game.computePayoffMix(mixedStrategyA, mixedStrategyB);

    // Find Pareto optimal strategies
    game.sociallyOptimal();

    return 0;
}
