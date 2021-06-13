#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

struct is_positive
{
  __host__ __device__
  bool operator()(const double &x)
  {
    return x > 0;
  }
};

struct is_negative
{
  __host__ __device__
  bool operator()(const double &x)
  {
    return x < 0;
  }
};

int main() {
    int N = 2518;
    thrust::device_vector<double> stocks, ganho_diario(N-1, 0);
    double stks;

    for (int i = 0; i < N; i++)
    {
        std::cin >> stks;
        stocks.push_back(stks);
    }

    thrust::transform(stocks.begin() + 1, stocks.end(), stocks.begin(), ganho_diario.begin(), thrust::minus<double>());
    int valUp = thrust::count_if(ganho_diario.begin(), ganho_diario.end(), is_positive());
    thrust::replace_if(ganho_diario.begin(), ganho_diario.end(), is_negative(), 0);

    std::cout << "Ganho diário:" << "\n";
    for (auto i = ganho_diario.begin(); i != ganho_diario.end(); i++)
    {
        std::cout << *i << "\n";
    }

    // std::cout << valUp << "\n";
}
