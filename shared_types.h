#pragma once

#include <vector>

// Спільні вхідні дані: система Ax = b
struct InputData
{
    std::vector<std::vector<double>> A; // матриця коефіцієнтів n x n
    std::vector<double> b;              // вектор вільних членів

    double epsilon = 1e-6;   // точність (для методу простих ітерацій)
    int maxIterations = 1000; // обмеження кількості ітерацій (для методу Б)
};

// Результат розв'язання системи
struct Result
{
    std::vector<double> x;   // вектор розв'язків
    int iterations = 0;      // кількість ітерацій (для Гауса можна лишити 0)
    double residualNorm = 0.0; // норма нев'язки ||Ax - b||
};
