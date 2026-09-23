#include "shared_types.h"
#include <memory>
#include <cmath>
#include <stdexcept>

// Студент А - метод Гауса (прямий та зворотний хід)
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data)
{
    const auto& Ain = data->A;
    const auto& bin = data->b;
    const int n = static_cast<int>(Ain.size());

    // Робоча копія розширеної матриці [A | b], щоб не змінювати вхідні дані
    std::vector<std::vector<double>> M(n, std::vector<double>(n + 1, 0.0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            M[i][j] = Ain[i][j];
        M[i][n] = bin[i];
    }

    // Прямий хід з частковим вибором головного елемента
    for (int col = 0; col < n; ++col)
    {
        int pivotRow = col;
        double maxVal = std::fabs(M[col][col]);
        for (int row = col + 1; row < n; ++row)
        {
            if (std::fabs(M[row][col]) > maxVal)
            {
                maxVal = std::fabs(M[row][col]);
                pivotRow = row;
            }
        }

        if (maxVal < 1e-12)
            throw std::runtime_error("Matrix is singular or nearly singular");

        std::swap(M[col], M[pivotRow]);

        for (int row = col + 1; row < n; ++row)
        {
            double factor = M[row][col] / M[col][col];
            for (int j = col; j <= n; ++j)
                M[row][j] -= factor * M[col][j];
        }
    }

    // Зворотний хід
    std::vector<double> x(n, 0.0);
    for (int row = n - 1; row >= 0; --row)
    {
        double sum = M[row][n];
        for (int col = row + 1; col < n; ++col)
            sum -= M[row][col] * x[col];
        x[row] = sum / M[row][row];
    }

    // Обчислення норми нев'язки ||Ax - b||
    double residual = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < n; ++j)
            sum += Ain[i][j] * x[j];
        residual += (sum - bin[i]) * (sum - bin[i]);
    }
    residual = std::sqrt(residual);

    auto result = std::make_unique<Result>();
    result->x = std::move(x);
    result->iterations = 0; // прямий метод, ітерацій немає
    result->residualNorm = residual;
    return result;
}
