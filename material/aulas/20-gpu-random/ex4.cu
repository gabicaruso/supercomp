#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/random.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>

struct rndNum
{
    int N, *VEC, SEED;

    rndNum(int n, int *vec, int seed): N(n), VEC(vec), SEED(seed){};
    __host__ __device__
    int operator()(const int& x) {
        thrust::default_random_engine generator(SEED * x * 10000);
        thrust::uniform_int_distribution<int> distribution(25, 40);

        int rnd_num = distribution(generator);
        VEC[x] = rnd_num;

        return VEC[x];
    }
};

int main() {
    int N = 10;
    thrust::host_vector<int> vec_cpu(N);

    int seed = 0;
    char *SEED_VAR = getenv("SEED");
    if (SEED_VAR != NULL)
    {
        seed = atoi(SEED_VAR);
    }

    thrust::device_vector<int> vec_gpu(N);

    thrust::transform(thrust::make_counting_iterator<int>(0),
                      thrust::make_counting_iterator<int>(N),
                      vec_gpu.begin(),
                      rndNum(N, vec_gpu.data().get(), seed));

    for (int i = 0; i < N; i++)
    {
        std::cout << vec_gpu[i] << " ";
    }
    std::cout << "\n";
}