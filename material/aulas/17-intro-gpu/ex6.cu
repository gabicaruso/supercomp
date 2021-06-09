#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

int main() {
    int N = 2518;
    thrust::device_vector<double> AAPL, MSFT, MEAN_DIF(N, 0);
    double stocks_AAPL, stocks_MSFT, mean;

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

    // std::cout << "Device vector MEAN_DIF:" << "\n";
    // for (auto i = MEAN_DIF.begin(); i != MEAN_DIF.end(); i++)
    // {
    //     std::cout << *i << "\n";
    // }
    // std::cout << "\n";
    
    // std::cout << "Device vector AAPL:" << "\n";
    // for (auto i = AAPL.begin(); i != AAPL.end(); i++)
    // {
    //     std::cout << *i << "\n";
    // }
    // std::cout << "\n";

    // std::cout << "Device vector MSFT:" << "\n";
    // for (auto i = MSFT.begin(); i != MSFT.end(); i++)
    // {
    //     std::cout << *i << "\n";
    // }
    // std::cout << "\n";
}
