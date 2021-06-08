#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>

int main()
{
    thrust::host_vector<double> host(2518, 0);
    for (int i = 0; i < 2518; i++)
    {
        std::cin >> host[i];
    }
    /* na linha abaixo os dados são copiados
       para GPU */

    auto start = std::chrono::system_clock::now();
    thrust::device_vector<double> dev(host);
    auto end = std::chrono::system_clock::now();

    std::cerr << "Tempo alocacao e copia: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " millisegundos \n";
}
