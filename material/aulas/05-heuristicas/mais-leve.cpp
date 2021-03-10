#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

struct Object
{
    int weight, value, id;

    bool operator<(Object &a)
    {
        return weight < a.weight;
    }
};

int main()
{
    int n, maxWeight;
    std::cin >> n >> maxWeight;
    std::vector<struct Object> objects(n);
    std::vector<bool> usados(n, false);

    for (int i = 0; i < n; i++)
    {
        objects[i].id = i;
        std::cin >> objects[i].weight >> objects[i].value;
    }

    std::sort(objects.begin(), objects.end());

    int currentWeight = 0;
    int currentValue = 0;
    for (auto &obj : objects)
    {
        if (currentWeight + obj.weight <= maxWeight)
        {
            currentWeight += obj.weight;
            currentValue += obj.value;
            usados[obj.id] = true;
        }
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

    return 0;
}