#include "shared_types.h"
#include <iostream>
#include <memory>
#include <iomanip>

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

int main()
{
    auto data = std::make_shared<const InputData>(InputData{
        .A = {
            {4.0, 1.0, 1.0},
            {1.0, 5.0, 1.0},
            {1.0, 1.0, 6.0}
        },
        .b = {6.0, 7.0, 8.0},
        .epsilon = 1e-6,
        .maxIterations = 1000
    });

    auto resultA = calculateA(data);
    auto resultB = calculateB(data);

    auto [valueA, iterA, errorA] = *resultA;
    auto [valueB, iterB, errorB] = *resultB;

    std::cout << std::fixed << std::setprecision(6);

    // Измененная строчка для Студента Б
    std::cout << "=== Lab 1: Numerical Analysis (Updated by Student B) ===\n";
    std::cout << "x = [";
    for (size_t i = 0; i < valueA.size(); ++i)
        std::cout << valueA[i] << (i + 1 < valueA.size() ? ", " : "");
    std::cout << "]\n";
    std::cout << "Residual norm: " << errorA << "\n\n";

    std::cout << "=== Student B (Simple iteration / Jacobi) ===\n";
    std::cout << "x = [";
    for (size_t i = 0; i < valueB.size(); ++i)
        std::cout << valueB[i] << (i + 1 < valueB.size() ? ", " : "");
    std::cout << "]\n";
    std::cout << "Iterations: " << iterB << "\n";
    std::cout << "Residual norm: " << errorB << "\n\n";

    std::cout << "=== Comparison ===\n";
    std::cout << "Both methods solve the same system Ax = b.\n";
    std::cout << "Compare residual norms and iteration count above.\n";

    return 0;
}