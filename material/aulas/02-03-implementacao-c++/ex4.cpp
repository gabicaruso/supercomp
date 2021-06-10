#include <iostream>
#include <iomanip>      // std::setprecision
#include <cmath>

int main()
{
    int n;
    std::cin >> n;
    double *values = new double[n];
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 1; i <= n; i++)
    {
        std::cin >> values[i];
        sum1 += values[i];
    }
    double u = sum1/n;

    for (int i = 1; i <= n; i++)
    {
        sum2 += pow(values[i] - u, 2);
    }
    double sigma2 = sum2/n;

    std::cout << "u = " << std::setprecision(10) << u << " sigma2 = " << std::setprecision(10) << sigma2 << '\n';

    delete[] values;
}