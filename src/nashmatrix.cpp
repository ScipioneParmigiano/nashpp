#include "nashmatrix.h"
#include <iostream>
#include <vector>

// Constructor: Initializes NashMatrix with given payoff matrices
NashMatrix::NashMatrix(const std::vector<std::vector<int>>& payoffA, const std::vector<std::vector<int>>& payoffB)
    : payoffA(payoffA), payoffB(payoffB), numStrategiesA(payoffA.size()), numStrategiesB(payoffA[0].size()) {}

// Returns the payoff matrices
std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> NashMatrix::payoffMatrices() const {
    return std::make_pair(payoffA, payoffB);
}

// Computes the payoff for a pure strategy profile (no randomness involved)
// It calculates the payoff for both players when they choose specific pure strategies.
std::pair<int, int> NashMatrix::computePayoffPure(int strategyA, int strategyB) const {
    int payoffPlayerA = payoffA[strategyA][strategyB];
    int payoffPlayerB = payoffB[strategyA][strategyB];
    
    return std::make_pair(payoffPlayerA, payoffPlayerB);
}

// Computes the expected payoff for mixed strategies (strategies with probabilities)
// It calculates the expected payoff for both players when they use mixed strategies.
std::pair<double, double> NashMatrix::computePayoffMix(const std::vector<double>& mixedStrategyA, const std::vector<double>& mixedStrategyB) const {
    if (mixedStrategyA.size() != payoffA.size() || mixedStrategyB.size() != payoffA[0].size()) {
        std::cerr << "Error: Mixed strategy vector sizes do not match the game dimensions.\n";
        // Return a pair of zeros in case of error
        return std::make_pair(0.0, 0.0);
    }

    double expectedPayoffA = 0.0;
    double expectedPayoffB = 0.0;

    for (int i = 0; i < mixedStrategyA.size(); ++i) {
        for (int j = 0; j < mixedStrategyB.size(); ++j) {
            expectedPayoffA += mixedStrategyA[i] * mixedStrategyB[j] * payoffA[i][j];
            expectedPayoffB += mixedStrategyA[i] * mixedStrategyB[j] * payoffB[i][j];
        }
    }

    return std::make_pair(expectedPayoffA, expectedPayoffB);
}

// Finds socially optimal strategies (maximizing the sum of payoffs)
// It identifies the strategy profiles where the sum of payoffs is maximized for both players.
void NashMatrix::sociallyOptimal() const {
    std::cout << "Socially optimal Strategies:\n";

    std::vector<std::pair<int, int>> optimalStrategies;
    double maxAggregatedValue = -1e6;

    for (int i = 0; i < numStrategiesA; ++i) {
        for (int j = 0; j < numStrategiesB; ++j) {
            double aggregatedValue = static_cast<double>(payoffA[i][j] + payoffB[i][j]);

            if (aggregatedValue > maxAggregatedValue) {
                maxAggregatedValue = aggregatedValue;
                optimalStrategies.clear();
            }

            if (aggregatedValue == maxAggregatedValue) {
                optimalStrategies.emplace_back(i, j);
            }
        }
    }

    if (!optimalStrategies.empty()) {
        for (const auto& strategy : optimalStrategies) {
            std::cout << "(Player A: " << strategy.first << ", Player B: " << strategy.second << ")\n";
        }
    }
}

// Checks if a strategy profile is a Nash equilibrium
// It determines if a strategy profile is a Nash equilibrium, where no player can unilaterally deviate to improve their own payoff.
bool NashMatrix::isNashEquilibrium(int strategyA, int strategyB) const {
    int utilityA = payoffA[strategyA][strategyB];
    int utilityB = payoffB[strategyA][strategyB];

    for (int i = 0; i < payoffA.size(); ++i) {
        if (payoffA[i][strategyB] > utilityA || payoffB[strategyA][i] > utilityB) {
            return false;
        }
    }

    return true;
}

// Finds all Nash equilibria in the game
// It identifies all strategy profiles that constitute Nash equilibria in the game.
void NashMatrix::findNashEquilibria() const {
    for (int strategyA = 0; strategyA < numStrategiesA; ++strategyA) {
        for (int strategyB = 0; strategyB < numStrategiesB; ++strategyB) {
            if (isNashEquilibrium(strategyA, strategyB)) {
                std::cout << "Nash Equilibrium found: (Player A: " << strategyA << ", Player B: " << strategyB << ")" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

// Checks if a given strategy is a best response for a player
// It determines if a given strategy is the best response for a player against the opponent's strategy.
bool NashMatrix::isBestResponse(int player, int strategy) const {
    if (player != 0 && player != 1) {
        std::cerr << "Error: Invalid player index.\n";
        return false;
    }

    // Determine the opponent's strategies based on the player index
    int opponentStrategies = (player == 0) ? numStrategiesB : numStrategiesA;

    // Calculate the payoff for the given strategy against each of the opponent's strategies
    int currentPayoff = (player == 0) ? payoffA[strategy][0] : payoffB[0][strategy];
    for (int i = 1; i < opponentStrategies; ++i) {
        int opponentPayoff = (player == 0) ? payoffA[strategy][i] : payoffB[i][strategy];
        
        // If there exists an opponent's strategy that gives a higher payoff, return false
        if (opponentPayoff > currentPayoff) {
            return false;
        }
    }
    // If no other strategy yields a higher payoff, return true
    return true;
}
