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

    std::uniform_real_distribution<double> distribution(0, 1);

    #pragma omp parallel for reduction(+ : sum)
    for (long i = 0; i < N; i++)
    {
        seed = i;
        std::default_random_engine generator(seed);

        double rnd_numX = distribution(generator);
        double rnd_numY = distribution(generator);

        if (rnd_numX * rnd_numX + rnd_numY * rnd_numY <= 1)
        {
            #pragma omp critical
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