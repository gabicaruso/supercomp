#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> x(n), y(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> x[i] >> y[i];
    }

    std::vector<std::vector<double>> d;
    for (int i = 0; i < n; i++)
    {
        std::vector<double> linha;
        for (int j = 0; j < n; j++)
        {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double dist = sqrt(pow(dx, 2) + pow(dy, 2));
            linha.push_back(dist);
            // std::cout << std::setprecision(2) << std::fixed;
            // std::cout << "dist = " << dist << "\n";
        }
        d.push_back(linha);
    }

    for (auto linha : d)
    {
        for (auto el : linha)
        {
            std::cout << std::setprecision(2) << std::fixed;
            std::cout << el << " ";
        }
        std::cout << "\n";
    }
    // std::cout << std::setprecision(2) << std::fixed;
    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << "x = " << x[i] << " y = " << y[i] << '\n';
    // }
}