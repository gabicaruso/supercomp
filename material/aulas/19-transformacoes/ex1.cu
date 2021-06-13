#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

struct sub
{
    __host__ __device__
    double operator()(const double& x, const double& y) {
        return x - y;
    }
};

// struct media
// {
//     int N;
//     double *aapl, *msft;
//     thrust::device_vector<double> aapl_gpu(aapl, aapl + N);
//     thrust::device_vector<double> msft_gpu(msft, msft + N);

//     media(int n, double aapl, double msft): N(n), aapl(n), msft(n){};
//     // media(int n, double aapl, double msft): N(n), aapl_gpu(n), msft_gpu(n){};
//     __host__ __device__
//     double operator()(const double& aapl, const double& msft) {
//         return (aapl - msft) / N;
//     }
// };

struct variancia
{
    double mean;
    int N;

    variancia(double m, int n): mean(m), N(n){};
    __host__ __device__
    double operator()(const double& x) {
        return pow((x - mean), 2) / N;
    }
};

int main() {
    int N = 2518;
    thrust::device_vector<double> AAPL, MSFT, MEAN_DIF(N, 0), VAR_DIF(N, 0);
    double stocks_AAPL, stocks_MSFT;

    for (int i = 0; i < N; i++)
    {
        std::cin >> stocks_AAPL >> stocks_MSFT;
        AAPL.push_back(stocks_AAPL);
        MSFT.push_back(stocks_MSFT);
    }

    // thrust::transform(AAPL.begin(), AAPL.end(), MSFT.begin(), MEAN_DIF.begin(), thrust::minus<double>());
    // double sum = thrust::reduce(MEAN_DIF.begin(), MEAN_DIF.end(), 0.0, thrust::plus<double>());
    // double mean = sum/N;

    // double mean = thrust::transform_reduce(AAPL.begin(), AAPL.end(), MSFT.begin(), media(N), 0.0, thrust::plus<double>()); ?
    
    thrust::transform(AAPL.begin(), AAPL.end(), MSFT.begin(), MEAN_DIF.begin(), sub());
    double sum = thrust::reduce(MEAN_DIF.begin(), MEAN_DIF.end(), 0.0, thrust::plus<double>());
    double mean = sum/N;
    std::cout << "Média: " << fabs(mean) << "\n";


    // thrust::transform(MEAN_DIF.begin(), MEAN_DIF.end(), thrust::constant_iterator<double>(mean), VAR_DIF.begin(), thrust::minus<double>());
    // thrust::transform(VAR_DIF.begin(), VAR_DIF.end(), VAR_DIF.begin(), VAR_DIF.begin(), thrust::multiplies<double>());
    // double varSum = thrust::reduce(VAR_DIF.begin(), VAR_DIF.end(), 0.0, thrust::plus<double>());
    // double var = varSum/N;

    double var = thrust::transform_reduce(MEAN_DIF.begin(), MEAN_DIF.end(), variancia(mean, N), 0.0, thrust::plus<double>());
    std::cout << "Variância: " << var << "\n";

    // std::cout << "Device vector MEAN_DIF:" << "\n";
    // for (auto i = MEAN_DIF.begin(); i != MEAN_DIF.end(); i++)
    // {
    //     std::cout << *i << "\n";
    // }
    // std::cout << "\n";
}
