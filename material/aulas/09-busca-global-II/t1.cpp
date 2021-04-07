#include <stdio.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Object
{
    int weight;
    int value;
};

int decision(int n, vector<struct Object> &objetos, int i, int capacidade, vector<bool> &usados, vector<bool> &melhor)
{
    if (i >= n)
    {
        int soma_usados = 0;
        int soma_melhor = 0;
        for (int j = 0; j < n; j++)
        {
            if (usados[j])
            {
                soma_usados += objetos[j].value;
            }
            if (melhor[j])
            {
                soma_melhor += objetos[j].value;
            }
        }
        if (soma_usados > soma_melhor)
        {
            for (int j = 0; j < n; j++)
            {
                melhor[j] = usados[j];
            }
        }
        return 0;
    }
    usados[i] = false;
    int resposta_sem = decision(n, objetos, i + 1, capacidade, usados, melhor);
    int resposta_com = resposta_sem;
    if ((capacidade - objetos[i].weight) >= 0)
    {
        usados[i] = true;
        resposta_com = objetos[i].value + decision(n, objetos, i + 1, capacidade - objetos[i].weight, usados, melhor);
    }
    if (resposta_com > resposta_sem)
    {
        return resposta_com;
    }
    return resposta_sem;
}

int main()
{

    int n;
    cin >> n;
    int maxweight;
    cin >> maxweight;
    vector<struct Object> backpack(n);
    vector<bool> usados(n, false);
    vector<bool> melhor(n, false);

    for (int i = 0; i < n; i++)
    {
        cin >> backpack[i].weight >> backpack[i].value;
    }

    int finalValue = decision(n, backpack, 0, maxweight, usados, melhor);

    cout << finalValue << " ";
    cout << "\n";

    for (auto linha : melhor)
    {
        cout << linha;
        cout << " ";
    }
}