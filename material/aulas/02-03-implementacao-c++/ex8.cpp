#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

void calcula_distancias (std::vector<double> &x, std::vector<double> &y, std::vector<std::vector<double>> &d)
{
    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        std::vector<double> linha;
        for (int j = 0; j < n; j++)
        {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double dist = sqrt(pow(dx, 2) + pow(dy, 2));
            linha.push_back(dist);
        }
        d.push_back(linha);
    }
}

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
    calcula_distancias(x, y, d);    

    for (auto linha : d)
    {
        for (auto el : linha)
        {
            std::cout << std::setprecision(2) << std::fixed;
            std::cout << el << " ";
        }
        std::cout << "\n";
    }
}