#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

double conta_complexa(int i)
{
	sleep(1);
	return 2 * i;
}

int main()
{
	int N = 10;
	std::vector<double> vec(N);
	#pragma omp parallel for default(none) shared(vec) firstprivate(N)
	for (int i = 0; i < N; i++)
	{
		vec[i] = conta_complexa(i);
	}

	for (int i = 0; i < N; i++)
	{
		std::cout << vec[i] << " ";
	}

	return 0;
}
