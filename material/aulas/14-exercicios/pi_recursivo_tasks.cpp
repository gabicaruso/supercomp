#include <omp.h>
#include <iostream>
#include <iomanip>
static long num_steps = 1024l * 1024 * 1024 * 2;

#define MIN_BLK 1024 * 1024 * 256

double sum = 0;

void pi_r(long Nstart, long Nfinish, double step)
{
    long i, iblk;
    double res_parte1 = 0.0, res_parte2 = 0.0;

    if (Nfinish - Nstart < MIN_BLK)
    {
#pragma omp parallel
        {
#pragma omp master
            {
#pragma omp task
                {
                    for (long i = Nstart; i < (Nstart + Nfinish) / 2; i++)
                    {
                        double x = (i + 0.5) * step;
                        res_parte1 += 4.0 / (1.0 + x * x);
                    }
                }
#pragma omp task
                {
                    for (long i = (Nstart + Nfinish) / 2; i < Nfinish; i++)
                    {
                        double x = (i + 0.5) * step;
                        res_parte2 += 4.0 / (1.0 + x * x);
                    }
                }
            }
        }
        sum += res_parte1 + res_parte2;
    }
    else
    {
        iblk = Nfinish - Nstart;
        pi_r(Nstart, Nfinish - iblk / 2, step);
        pi_r(Nfinish - iblk / 2, Nfinish, step);
    }
}

int main()
{
    long i;
    double step, pi;
    double init_time, final_time;
    step = 1.0 / (double)num_steps;
    init_time = omp_get_wtime();
    pi_r(0, num_steps, step);
    pi = step * sum;
    final_time = omp_get_wtime() - init_time;

    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";
}
