# Nashpp

Nashpp is a C++ library inspired by [Nashpy](https://github.com/drvinceknight/Nashpy), designed to facilitate the modeling and analysis of games using Nash matrices, as well as solving linear programming problems. With Nashpp, users can conveniently represent games, compute Nash equilibria, and perform various game-theoretic and optimization tasks.

## Key features
1. Game Modeling: Nashpp enables users to define and manipulate games using Nash matrices, making it easy to represent various types of strategic interactions.

2. Nash Equilibrium Computation: The library provides functions to compute Nash equilibria for both two-player and n-player games, allowing users to analyze strategic outcomes efficiently.

3. Linear Programming Solver: Nashpp includes functionality to solve linear programming problems, enabling optimization tasks to be addressed within the same framework as game theory.

4. Efficient Algorithms: The library is built on efficient algorithms for computing Nash equilibria and solving linear programming problems, ensuring fast performance even for large-scale games and optimization tasks.

## How to use Nashpp

Using Nashpp is simple and straightforward. Users can include the library in their C++ projects and utilize its classes and functions to model games, compute Nash equilibria, and solve linear programming problems. Here's a basic example of how to get started with Nashpp:

```
#include <iostream>
#include "nashpp.h"

int main() {
    // Define a 2x2 matrix game
    NashMatrix game({{3, 2}, {1, 4}});

    // Compute Nash equilibria
    auto equilibria = game.computeNashEquilibria();

    // Print the computed Nash equilibria
    std::cout << "Nash Equilibria:" << std::endl;
    for (const auto& eq : equilibria) {
        std::cout << "Player 1 strategy: " << eq.first << ", Player 2 strategy: " << eq.second << std::endl;
    }

    return 0;
}
```

## Contributions

Nashpp welcomes contributions from the community to enhance its features, improve performance, and fix bugs. If you're interested in contributing, feel free to submit pull requests with your improvements.

