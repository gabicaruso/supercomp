#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

struct Object
{
    int id, peso, valor;
    double fracao;
    bool operator<(Object &a)
    {
        return double(valor) / peso > double(a.valor) / a.peso;
    }
};

int main()
{
    int n, maxWeight;
    std::cin >> n >> maxWeight;
    std::vector<struct Object> objects(n);

    for (int i = 0; i < n; i++)
    {
        objects[i].id = i;
        std::cin >> objects[i].peso >> objects[i].valor;
    }

    std::sort(objects.begin(), objects.end());

    int peso_atual = 0;
    int valor_atual = 0;

    for (auto &obj : objects)
    {
        if (peso_atual + obj.peso <= maxWeight)
        {
            valor_atual += obj.valor;
            peso_atual += obj.peso;
            obj.fracao = 1.0;
        }
        else if (peso_atual <= maxWeight)
        {
            double fracao = double(maxWeight - peso_atual) / obj.peso;
            valor_atual += fracao * obj.valor;
            peso_atual += fracao * obj.peso;
            obj.fracao = fracao;
        }
    }

    std::cout << peso_atual << " " << valor_atual << " ";
    for (auto &obj : objects)
    {
        std::cout << obj.fracao << " ";
    }
    std::cout << "\n";

    return 0;
}