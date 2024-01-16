#include "nashmatrix.h"
#include <iostream>
#include <vector>

NashMatrix::NashMatrix(const std::vector<std::vector<int>>& payoffA, const std::vector<std::vector<int>>& payoffB)
    : payoffA(payoffA), payoffB(payoffB), numStrategiesA(payoffA.size()), numStrategiesB(payoffA[0].size()) {}

void NashMatrix::printPayoffMatrices() const {
    std::cout << "Payoff Bimatrix for Player A, B:\n";
    for (int i = 0; i < numStrategiesA; ++i) {
        for (int j = 0; j < numStrategiesB; ++j) {
            std::cout << payoffA[i][j] << ",";
        }
        std::cout << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < numStrategiesA; ++i) {
        for (int j = 0; j < numStrategiesB; ++j) {
            std::cout << payoffB[i][j] << ",";
        }
        std::cout << " ";
    }
    std::cout << std::endl << std::endl;
}

void NashMatrix::computePayoffPure(int strategyA, int strategyB) const {
    std::cout << "Payoff for (Player A: " << strategyA << ", Player B: " << strategyB << ") is ";
    std::cout << "Player A: " << payoffA[strategyA][strategyB] << ", Player B: " << payoffB[strategyA][strategyB] << std::endl << std::endl;
}

void NashMatrix::computePayoffMix(const std::vector<double>& mixedStrategyA, const std::vector<double>& mixedStrategyB) const {
    if (mixedStrategyA.size() != payoffA.size() || mixedStrategyB.size() != payoffA[0].size()) {
        std::cerr << "Error: Mixed strategy vector sizes do not match the game dimensions.\n";
        return;
    }

    double expectedPayoffA = 0.0;
    double expectedPayoffB = 0.0;

    for (int i = 0; i < mixedStrategyA.size(); ++i) {
        for (int j = 0; j < mixedStrategyB.size(); ++j) {
            expectedPayoffA += mixedStrategyA[i] * mixedStrategyB[j] * payoffA[i][j];
            expectedPayoffB += mixedStrategyA[i] * mixedStrategyB[j] * payoffB[i][j];
        }
    }

    std::cout << "Expected Payoff for Mixed Strategies:\n";
    std::cout << "Player A: " << expectedPayoffA << ", Player B: " << expectedPayoffB << std::endl << std::endl;
}

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
