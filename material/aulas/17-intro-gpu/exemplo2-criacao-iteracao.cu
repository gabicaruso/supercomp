#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
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

    printf("Host vector: ");
    for (auto i = host.begin(); i != host.end(); i++)
    {
        std::cout << *i << " "; // este acesso é rápido -- CPU
    }
    printf("\n");

    printf("Device vector: ");
    for (auto i = dev.begin(); i != dev.end(); i++)
    {
        std::cout << *i << " "; // este acesso é lento! -- GPU
    }
    printf("\n");
}
