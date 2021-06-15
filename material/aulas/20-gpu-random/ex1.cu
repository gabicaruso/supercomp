#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/random.h>
#include <iostream>

int main() {
    int N = 10;
    thrust::host_vector<int> vec_cpu(N);

    int seed = 0;
    char *SEED_VAR = getenv("SEED");
    if (SEED_VAR != NULL)
    {
        seed = atoi(SEED_VAR);
    }

    thrust::default_random_engine generator(seed);
    thrust::uniform_int_distribution<int> distribution(25, 40);

    for (int i = 0; i < N; i++)
    {
        int rnd_num = distribution(generator);
        vec_cpu[i] = rnd_num;
    }
    
    thrust::device_vector<int> vec_gpu(vec_cpu);

    for (int i = 0; i < N; i++)
    {
        std::cout << vec_gpu[i] << " ";
    }
    std::cout << "\n";
}