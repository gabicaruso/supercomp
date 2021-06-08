#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/extrema.h>
#include <iostream>

int main()
{
    thrust::host_vector<double> host(2518, 0);
    for (int i = 0; i < 2518; i++)
    {
        std::cin >> host[i];
    }

    /* na linha abaixo os dados são copiados
       para GPU */
    thrust::device_vector<double> dev(host);

    double val = thrust::reduce(dev.begin(), dev.end(), (double)0, thrust::plus<double>());
    double val2 = thrust::reduce(dev.end() - 365, dev.end(), (double)0, thrust::plus<double>());

    val = val / 2518;
    val2 = val2 / 365;

    auto result = thrust::minmax_element(dev.begin(), dev.end());
    auto result2 = thrust::minmax_element(dev.end() - 365, dev.end());

    // auto min_result = thrust::reduce(dev.begin(), dev.end(), 9999.9, thrust::minimum<double>());
    // auto max_result = thrust::reduce(dev.begin(), dev.end(), -1, thrust::maximum<double>());
    // auto min_result2 = thrust::reduce(dev.end() - 365, dev.end(), 9999.9, thrust::minimum<double>());
    // auto max_result2 = thrust::reduce(dev.end() - 365, dev.end(), -1, thrust::maximum<double>());

    std::cout << "A média de 10 anos é " << val << '\n';
    std::cout << "A média do ultimo ano é " << val2 << '\n';
    std::cout << "O mínimo de 10 anos é " << *(result.first) << '\n';
    std::cout << "O máximo de 10 anos é " << *(result.second) << '\n';
    std::cout << "O mínimo do ultimo ano é " << *(result2.first) << '\n';
    std::cout << "O máximo do ultimo ano é " << *(result2.second) << '\n';
    // std::cout << "O mínimo de 10 anos é " << min_result << '\n';
    // std::cout << "O máximo de 10 anos é " << max_result << '\n';
    // std::cout << "O mínimo do ultimo ano é " << min_result2 << '\n';
    // std::cout << "O máximo do ultimo ano é " << max_result2 << '\n';
}
