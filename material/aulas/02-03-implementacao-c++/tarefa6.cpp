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

    std::vector<std::vector<double>> mat;
    for (int i = 0; i < n; i++)
    {
        std::vector<double> linha; // RECRIADO TODA INTERACAO
        for (int j = 0; j < n; j++)
        {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double dist = sqrt(dx * dx + dy * dy);
            linha.push_back(dist);
        }
        mat.push_back(linha);
    }

    std::cout << std::setprecision(2) << std::fixed;
    for (auto linha : mat)
    {
        for (auto el : linha)
        {
            std::cout << el << " ";
        }
        std::cout << "\n";
    }

    return 0;
}