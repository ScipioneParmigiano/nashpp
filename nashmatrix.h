#ifndef NASHMATRIX_H
#define NASHMATRIX_H

#include <vector>

class NashMatrix {
private:
    std::vector<std::vector<int>> payoffA;
    std::vector<std::vector<int>> payoffB;
    int numStrategiesA;
    int numStrategiesB;

public:
    // Constructor
    NashMatrix(const std::vector<std::vector<int>>& payoffA, const std::vector<std::vector<int>>& payoffB);

    // Public member functions
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> payoffMatrices() const;
    int getNumStrategiesA() const { return numStrategiesA; }
    int getNumStrategiesB() const { return numStrategiesB; }
    std::pair<int, int> computePayoffPure(int strategyA, int strategyB) const;
    std::pair<double, double> computePayoffMix(const std::vector<double>& mixedStrategyA, const std::vector<double>& mixedStrategyB) const;
    void sociallyOptimal() const;
    bool isNashEquilibrium(int strategyA, int strategyB) const;
    void findNashEquilibria() const;
    bool isBestResponse(int player, int strategy) const;
};

#endif // NASHMATRIX_H

