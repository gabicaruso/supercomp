#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>

int main()
{
    long N = 10000000;
    long sum = 0;
    int seed = 10000;
    if (getenv("SEED"))
    {
        seed = atoi(getenv("SEED"));
    }

    #pragma omp parallel default(none) shared(sum) firstprivate(N, seed)
    {
        int thread_atual = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        std::default_random_engine generator(thread_atual * seed);
        std:: uniform_real_distribution<double> distribution(0, 1);

        long chunk_size = N / nthreads;
        long start = thread_atual * chunk_size;
        long end = (thread_atual + 1) * chunk_size;
        if(end > N) end = N;

        double local_sum = 0;
        for(int i = start; i < end; i++)
        {
            double rnd_numX = distribution(generator);
            double rnd_numY = distribution(generator);

            if (rnd_numX * rnd_numX + rnd_numY * rnd_numY <= 1)
            {
                local_sum++;
            }
        }
        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    double pi = 4.0 * sum / N;
    std::cout << "pi = " << pi << "\n";
    std::cerr << "sum = " << sum << "\n";

    return pi;
}