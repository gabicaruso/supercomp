#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

int main() {
    int N = 2518;
    thrust::device_vector<double> AAPL, MSFT, MEAN_DIF(N, 0), U_VEC(N, 0), VAR_DIF(N, 0);
    double stocks_AAPL, stocks_MSFT, mean, var;

    for (int i = 0; i < N; i++)
    {
        std::cin >> stocks_AAPL >> stocks_MSFT;
        AAPL.push_back(stocks_AAPL);
        MSFT.push_back(stocks_MSFT);
    }

    thrust::transform(AAPL.begin(), AAPL.end(), MSFT.begin(), MEAN_DIF.begin(), thrust::minus<double>());
    double sum = thrust::reduce(MEAN_DIF.begin(), MEAN_DIF.end(), 0.0, thrust::plus<double>());
    mean = sum/N;

    std::cout << "Média: " << fabs(mean) << "\n";

    thrust::fill(U_VEC.begin(), U_VEC.end(), mean);
    thrust::transform(MEAN_DIF.begin(), MEAN_DIF.end(), U_VEC.begin(), VAR_DIF.begin(), thrust::minus<double>());
    thrust::transform(VAR_DIF.begin(), VAR_DIF.end(), VAR_DIF.begin(), VAR_DIF.begin(), thrust::multiplies<double>());
    double varSum = thrust::reduce(VAR_DIF.begin(), VAR_DIF.end(), 0.0, thrust::plus<double>());
    var = varSum/N;

    std::cout << "Variância: " << var << "\n";
}
