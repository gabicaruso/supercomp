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

    int n_threads = omp_get_max_threads();
    std::vector<std::default_random_engine> generator(n_threads);
    for (int i = 0; i < n_threads; i++)
    {
        generator[i] = std::default_random_engine(i * 137321);
    }
    std::vector<std::uniform_real_distribution<double>> distribution(n_threads);

#pragma omp parallel for reduction(+ \
                                   : sum)
    for (long i = 0; i < N; i++)
    {
        int id = omp_get_thread_num();
        double rnd_numX = distribution[id](generator[id]);
        double rnd_numY = distribution[id](generator[id]);

        if (rnd_numX * rnd_numX + rnd_numY * rnd_numY <= 1)
        {
            sum++;
        }
    }

    double pi = 4.0 * sum / N;
    std::cout << "pi = " << pi << "\n";
    std::cerr << "sum = " << sum << "\n";

    return pi;
}