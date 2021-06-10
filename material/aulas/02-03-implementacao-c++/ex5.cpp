#include <iostream>
#include <iomanip>      // std::setprecision
#include <cmath>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> vec(n);
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 1; i <= n; i++)
    {
        std::cin >> vec[i];
        sum1 += vec[i];
    }
    double u = sum1/n;

    for (int i = 1; i <= n; i++)
    {
        sum2 += pow(vec[i] - u, 2);
    }
    double sigma2 = sum2/n;

    std::cout << "u = " << std::setprecision(10) << u << " sigma2 = " << std::setprecision(10) << sigma2 << '\n';
}