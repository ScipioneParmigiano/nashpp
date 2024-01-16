#include "../nashmatrix.h"
#include <iostream>
#include <cassert>
#include <sstream>

void testNashMatrix() {
    // Test Case 1: Initialization and Printing
    std::vector<std::vector<int>> payoffA = {{4, 2}, {1, 4}};
    std::vector<std::vector<int>> payoffB = {{4, 1}, {2, 4}};
    NashMatrix game1(payoffA, payoffB);
    assert(game1.getNumStrategiesA() == 2);
    assert(game1.getNumStrategiesB() == 2);

    // Test Case 2: Pure Strategy Payoff Computation
    std::stringstream buffer1;
    std::streambuf* oldCout1 = std::cout.rdbuf(buffer1.rdbuf());
    game1.computePayoffPure(0, 1);
    std::cout.rdbuf(oldCout1);
    assert(buffer1.str() == "Payoff for (Player A: 0, Player B: 1) is Player A: 2, Player B: 1\n\n");

    // Test Case 3: Mixed Strategy Payoff Computation
    std::vector<double> mixedStrategyA = {0.5, 0.5};
    std::vector<double> mixedStrategyB = {0.5, 0.5};
    std::stringstream buffer2;
    std::streambuf* oldCout2 = std::cout.rdbuf(buffer2.rdbuf());
    game1.computePayoffMix(mixedStrategyA, mixedStrategyB);
    std::cout.rdbuf(oldCout2);
    assert(buffer2.str() == "Expected Payoff for Mixed Strategies:\nPlayer A: 2.75, Player B: 2.75\n\n");

    // Test Case 4: Socially Optimal Strategies
    std::stringstream buffer3;
    std::streambuf* oldCout3 = std::cout.rdbuf(buffer3.rdbuf());
    game1.sociallyOptimal();
    std::cout.rdbuf(oldCout3);
    assert(buffer3.str() == "Socially optimal Strategies:\n(Player A: 0, Player B: 0)\n(Player A: 1, Player B: 1)\n");

    // Test Case 5: Nash Equilibrium Check
    assert(game1.isNashEquilibrium(1, 1));

    // Test Case 6: Finding Nash Equilibria
    std::stringstream buffer4;
    std::streambuf* oldCout4 = std::cout.rdbuf(buffer4.rdbuf());
    game1.findNashEquilibria();
    std::cout.rdbuf(oldCout4);
    assert(buffer4.str() == "Nash Equilibrium found: (Player A: 0, Player B: 0)\nNash Equilibrium found: (Player A: 1, Player B: 1)\n\n");

    // Test Case 7: Change Payoff Matrices and Test Again
    std::vector<std::vector<int>> payoffA2 = {{3, 1}, {2, 5}};
    std::vector<std::vector<int>> payoffB2 = {{3, 2}, {1, 4}};
    NashMatrix game2(payoffA2, payoffB2);
    assert(game2.getNumStrategiesA() == 2);
    assert(game2.getNumStrategiesB() == 2);

    // Test Case 8: Pure Strategy Payoff Computation with New Matrices
    std::stringstream buffer5;
    std::streambuf* oldCout5 = std::cout.rdbuf(buffer5.rdbuf());
    game2.computePayoffPure(1, 0);
    std::cout.rdbuf(oldCout5);
    assert(buffer5.str() == "Payoff for (Player A: 1, Player B: 0) is Player A: 2, Player B: 1\n\n");

    // Test Case 9: Mixed Strategy Payoff Computation with New Matrices
    std::vector<double> mixedStrategyA2 = {1, 0};
    std::vector<double> mixedStrategyB2 = {0.5, 0.5};
    std::stringstream buffer6;
    std::streambuf* oldCout6 = std::cout.rdbuf(buffer6.rdbuf());
    game2.computePayoffMix(mixedStrategyA2, mixedStrategyB2);
    std::cout.rdbuf(oldCout6);
    assert(buffer6.str() == "Expected Payoff for Mixed Strategies:\nPlayer A: 2, Player B: 2.5\n\n");

    // Test Case 10: Socially Optimal Strategies with New Matrices
    std::stringstream buffer7;
    std::streambuf* oldCout7 = std::cout.rdbuf(buffer7.rdbuf());
    game2.sociallyOptimal();
    std::cout.rdbuf(oldCout7);
    assert(buffer7.str() == "Socially optimal Strategies:\n(Player A: 1, Player B: 1)\n");
}

int test() {
    testNashMatrix();
    std::cout << std::endl << "All test passed" << std::endl;

    return 0;
}
