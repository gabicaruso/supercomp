#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    int i = 0;
    double n;
    double s = 0;
    std::cin >> n;

    while (i < n)
    {
        s += 1 / std::pow(2, i);
        i++;
    }

    std::cout << std::setprecision(15) << s << '\n';
}