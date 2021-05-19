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
    double val = thrust::reduce(dev.begin(), dev.end(), (double)0);
    double val2 = thrust::reduce(dev.end() - 365, dev.end(), (double)0);
    printf("Host vector: ");
    val = val / 2518;
    val2 = val2 / 365;

    auto result = thrust::minmax_element(dev.begin(), dev.end());
    auto result2 = thrust::minmax_element(dev.end() - 365, dev.end());

    // for (auto i = host.begin(); i != host.end(); i++) {
    //     std::cout << *i << " "; // este acesso é rápido -- CPU
    // }
    // printf("\n");

    // printf("Device vector: ");
    // for (auto i = dev.begin(); i != dev.end(); i++) {
    //     std::cout << *i << " "; // este acesso é lento! -- GPU
    // }
    // printf("\n");
    std::cout << "A média de 10 anos é " << val << '\n';
    std::cout << "A média do ultimo ano é " << val2 << '\n';
    std::cout << "O mínimo de 10 anos é " << *(result.first) << '\n';
    std::cout << "O máximo de 10 anos é " << *(result.second) << '\n';
    std::cout << "O mínimo do ultimo ano é " << *(result2.first) << '\n';
    std::cout << "O máximo do ultimo ano é " << *(result2.second) << '\n';
}
