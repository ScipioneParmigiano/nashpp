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
    void printPayoffMatrices() const;
    int getNumStrategiesA() const { return numStrategiesA; }
    int getNumStrategiesB() const { return numStrategiesB; }
    void computePayoffPure(int strategyA, int strategyB) const;
    void computePayoffMix(const std::vector<double>& mixedStrategyA, const std::vector<double>& mixedStrategyB) const;
    void sociallyOptimal() const;
    bool isNashEquilibrium(int strategyA, int strategyB) const;
    void findNashEquilibria() const;
};

#endif // NASHMATRIX_H
