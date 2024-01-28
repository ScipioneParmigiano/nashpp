#include <iostream>
#include <cassert>
#include "../nashmatrix.h"
#include "../nashmatrix.cpp"

void testConstructor() {
    // Test constructor initialization
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    auto matrices = game.payoffMatrices();
    assert(matrices == std::make_pair(payoffA, payoffB));
}

void testComputePayoffPure() {
    // Test computing payoff for pure strategies
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    auto payoffs = game.computePayoffPure(0, 1);
    assert(payoffs == std::make_pair(2, 2));
}

void testComputePayoffMix() {
    // Test computing payoff for mixed strategies
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    std::vector<double> mixedStrategyA = {0.5, 0.5};
    std::vector<double> mixedStrategyB = {0.5, 0.5};

    auto payoffs_m = game.computePayoffMix(mixedStrategyA, mixedStrategyB);
    assert(payoffs_m == std::make_pair(2.5, 2.5));
}

void testSociallyOptimal() {
    // Test finding socially optimal strategies
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    // No need to assert output, just checking for any runtime errors
    game.sociallyOptimal();
}

void testIsNashEquilibrium() {
    // Test checking Nash equilibrium
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    assert(game.isNashEquilibrium(1, 1) == true);  // Nash equilibrium exists
    assert(game.isNashEquilibrium(0, 1) == false); // Not a Nash equilibrium
}

void testFindNashEquilibria() {
    // Test finding Nash equilibria
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    // No need to assert output, just checking for any runtime errors
    game.findNashEquilibria();
}

void testIsBestResponse() {
    // Test checking if a strategy is a best response
    std::vector<std::vector<int>> payoffA = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> payoffB = {{1, 2}, {3, 4}};

    NashMatrix game(payoffA, payoffB);

    assert(game.isBestResponse(0, 1) == false); 
    assert(game.isBestResponse(1, 1) == false);  
}

void testAll() {
    testConstructor();
    testComputePayoffPure();
    testComputePayoffMix();
    testSociallyOptimal();
    testIsNashEquilibrium();
    testFindNashEquilibria();
    testIsBestResponse();

    std::cout << "All tests passed successfully!\n";
}

int main() {
    testAll();
    return 0;
}
