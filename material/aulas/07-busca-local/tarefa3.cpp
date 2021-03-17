#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

struct Object
{
    int weight, value, id;

    bool operator<(Object &a)
    {
        return value > a.value;
    }
};

int main()
{
    int n, maxWeight;
    std::cin >> n >> maxWeight;
    std::vector<struct Object> objects(n);

    int seed = 10;
    char *SEED_VAR = getenv("SEED");
    if (SEED_VAR != NULL)
    {
        seed = atoi(SEED_VAR);
    }
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < n; i++)
    {
        objects[i].id = i;
        std::cin >> objects[i].weight >> objects[i].value;
    }

    std::sort(objects.begin(), objects.end()); // a chance de ter pego nao importa a ordem

    std::vector<bool> bestUsados(n, false);
    int bestWeight = 0;
    int bestValue = 0;

    for (int i = 0; i < 10; i++)
    {
        std::vector<bool> usados(n, false);
        int currentWeight = 0;
        int currentValue = 0;

        for (auto &obj : objects)
        {
            double rnd_num = distribution(generator); // gera número
            // std::cerr << rnd_num << "\n";
            if (currentWeight + obj.weight <= maxWeight && rnd_num <= 0.5)
            {
                currentWeight += obj.weight;
                currentValue += obj.value;
                usados[obj.id] = true;
            }
        }

        for (auto &obj : objects)
        {
            if ((currentWeight + obj.weight <= maxWeight) && (usados[obj.id] == false))
            {
                currentWeight += obj.weight;
                currentValue += obj.value;
                usados[obj.id] = true;
            }
        }

        if (currentValue > bestValue)
        {
            bestWeight = currentWeight;
            bestValue = currentValue;
            bestUsados = usados;
        }

        std::cout << currentWeight << " " << currentValue << "\n";
        for (int i = 0; i < n; i++)
        {
            if (usados[i])
            {
                std::cout << i << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << bestWeight << " " << bestValue << "\n";
    for (int i = 0; i < n; i++)
    {
        if (bestUsados[i])
        {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";

    return 0;
}