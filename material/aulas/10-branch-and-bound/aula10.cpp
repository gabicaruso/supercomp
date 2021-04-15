#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

struct Object
{
    int id, peso, valor;
};

struct Solucao
{
    std::vector<bool> usado;
    int peso, valor;

    Solucao(int N)
    {
        usado.resize(N, false);
        valor = peso = 0;
    }
};

long num_copy = 0;
long num_leaf = 0;
long num_bound = 0;

int busca_exaustiva(long unsigned int n, std::vector<Object> &obj, int C, Solucao &melhor, Solucao &atual, int valor_total, long unsigned int i = 0)
{
    if (i == obj.size())
    {
        num_leaf++;
        if (atual.valor > melhor.valor)
        {
            melhor = atual;
            num_copy++;
        }
        return 0;
    }

    //VALE A PENA CONTINUAR? valor otimista inclui todos
    int valor_otimista = atual.valor + valor_total;
    if (valor_otimista <= melhor.valor)
    {
        num_bound++;
        return 0;
    }

    int com = 0;
    if (obj[i].peso <= C)
    {
        atual.usado[i] = true;
        atual.valor += obj[i].valor;
        atual.peso += obj[i].peso;
        com = obj[i].valor + busca_exaustiva(n, obj, C - obj[i].peso, melhor, atual, valor_total - obj[i].valor, i + 1);
        atual.usado[i] = false;
        atual.valor -= obj[i].valor;
        atual.peso -= obj[i].peso;
    }
    atual.usado[i] = false;
    int sem = busca_exaustiva(n, obj, C, melhor, atual, valor_total - obj[i].valor, i + 1);

    return std::max(com, sem);
}
int main()
{
    int n, maxWeight;
    std::cin >> n >> maxWeight;
    std::vector<struct Object> objects(n);
    int valor_total = 0;

    for (int i = 0; i < n; i++)
    {
        objects[i].id = i;
        std::cin >> objects[i].peso >> objects[i].valor;
    }
    for (auto &obj : objects)
    {
        valor_total += obj.valor;
    }

    Solucao melhor(n);
    Solucao atual(n);
    busca_exaustiva(n, objects, maxWeight, melhor, atual, valor_total);

    std::cout << melhor.peso << " " << melhor.valor << " 1"
              << "\n";
    for (int i = 0; i < n; i++)
    {
        if (melhor.usado[i])
        {
            std::cout << i << " ";
        }
    }

    std::cout << "\n";
    std::cerr << "num_copy" << num_copy << "\n";
    std::cerr << "num_leaf" << num_leaf << "\n";
    std::cerr << "num_bound" << num_bound << "\n";

    return 0;
}