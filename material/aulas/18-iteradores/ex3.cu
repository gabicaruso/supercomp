#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

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

    // std::cout << "Device vector stocks:" << "\n";
    // for (auto i = stocks.begin(); i != stocks.end(); i++)
    // {
    //     std::cout << *i << "\n";
    // }
    // std::cout << "\n";

    std::cout << "Ganho diário:" << "\n";
    for (auto i = ganho_diario.begin(); i != ganho_diario.end(); i++)
    {
        std::cout << *i << "\n";
    }

    // printf("Ganho: ");
    // for (thrust::device_vector<double>::iterator i = ganho_diario.begin(); i != ganho_diario.end(); i++) {
    //     std::cout << *i << " ";
    // }
    // printf("\n");
}
