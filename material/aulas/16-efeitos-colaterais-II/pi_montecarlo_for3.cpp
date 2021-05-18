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

#pragma omp parallel default(none) shared(sum) firstprivate(N)
    {
        int id = omp_get_thread_num();
        std::default_random_engine generator(id * 137321);
        std::uniform_real_distribution<double> distribution(0, 1);

#pragma omp for reduction(+ \
                          : sum)
        for (long i = 0; i < N; i++)
        {
            double rnd_numX = distribution(generator);
            double rnd_numY = distribution(generator);

            if (rnd_numX * rnd_numX + rnd_numY * rnd_numY <= 1)
            {
                sum++;
            }
        }
    }

    double pi = 4.0 * sum / N;
    std::cout << "pi = " << pi << "\n";
    std::cerr << "sum = " << sum << "\n";

    return pi;
}