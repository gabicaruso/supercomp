#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back(i * i);
    }

    double u = 0;
    double sigma2 = 0;

    for (int i = 0; i < n; i++)
    {
        std::cin >> vec[i];
        std::cout << "valores: " << vec[i] << '\n';

        u += ((double)1 / n) * vec[i];
    }

    for (int i = 0; i < n; i++)
    {
        sigma2 += ((double)1 / n) * std::pow(vec[i] - u, 2);
    }

    std::cout << "u = " << std::setprecision(10) << u << " sigma2 = " << std::setprecision(10) << sigma2 << '\n';
}