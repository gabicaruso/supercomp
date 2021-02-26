#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    int n;
    std::cin >> n;
    double *values = new double[n];

    double u = 0;
    double sigma2 = 0;

    for (int i = 0; i < n; i++)
    {
        std::cin >> values[i];
        std::cout << "valores: " << values[i] << '\n';

        u += ((double)1 / n) * values[i];
    }

    for (int i = 0; i < n; i++)
    {
        sigma2 += ((double)1 / n) * std::pow(values[i] - u, 2);
    }

    std::cout << "u = " << std::setprecision(10) << u << " sigma2 = " << std::setprecision(10) << sigma2 << '\n';

    delete[] values;
}