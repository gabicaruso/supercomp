#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    long N = 10000000;
    long sum = 0;
    int seed = 10000;
    if (getenv("SEED"))
    {
        seed = atoi(getenv("SEED"));
    }

    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0, 1);

    #pragma omp parallel for reduction(+ : sum)
    for (long i = 0; i < N; i++)
    {
        #pragma omp critical
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