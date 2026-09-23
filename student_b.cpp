#include "shared_types.h"
#include <memory>
#include <cmath>
#include <stdexcept>

// Студент Б - метод простих ітерацій (Якобі)
// Потребує діагональної переваги матриці A для гарантованої збіжності
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data)
{
    const auto& A = data->A;
    const auto& b = data->b;
    const int n = static_cast<int>(A.size());
    const double eps = data->epsilon;
    const int maxIter = data->maxIterations;

    std::vector<double> x(n, 0.0);      // початкове наближення
    std::vector<double> xNext(n, 0.0);

    int iter = 0;
    double diff = eps + 1.0;

    while (diff > eps && iter < maxIter)
    {
        for (int i = 0; i < n; ++i)
        {
            if (std::fabs(A[i][i]) < 1e-12)
                throw std::runtime_error("Zero on diagonal - method not applicable");

            double sum = b[i];
            for (int j = 0; j < n; ++j)
            {
                if (j != i)
                    sum -= A[i][j] * x[j];
            }
            xNext[i] = sum / A[i][i];
        }

        diff = 0.0;
        for (int i = 0; i < n; ++i)
            diff += (xNext[i] - x[i]) * (xNext[i] - x[i]);
        diff = std::sqrt(diff);

        x = xNext;
        ++iter;
    }

    // Обчислення норми нев'язки ||Ax - b||
    double residual = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < n; ++j)
            sum += A[i][j] * x[j];
        residual += (sum - b[i]) * (sum - b[i]);
    }
    residual = std::sqrt(residual);

    auto result = std::make_unique<Result>();
    result->x = std::move(x);
    result->iterations = iter;
    result->residualNorm = residual;
    return result;
}
