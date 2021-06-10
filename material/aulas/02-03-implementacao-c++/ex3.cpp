#include <iostream>
#include <iomanip>      // std::setprecision
#include <cmath>

int main()
{
    int n;
    std::cin >> n;

    double sum = 0;
    for (int i = 0; i <= n; i++)
    {
        sum += 1.0 / (pow(2.0, i)) ;
    }

    std::cout << "Saída: " << std::setprecision(15) << sum << "\n";
}