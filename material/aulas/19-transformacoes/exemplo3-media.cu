#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <math.h> 
#include "imagem.hpp"
#include <thrust/iterator/constant_iterator.h>
#include <vector>

struct media
{
    int cols, rows;
    unsigned char *I;
    media(int cols, int rows, unsigned char *I) : cols(cols), rows(rows), I(I) {};
    __host__ __device__

    unsigned char operator()(const int &i) {
        int x = i % cols;
        int y = i / cols;

        unsigned char current = I[x * cols + y];

        unsigned char forward;
        if (x + 1 <= rows)
            forward = I[(x + 1) * cols + y];
        else
            forward = 0;

        unsigned char backward;
        if (x - 1 >= 0)
            backward = I[(x - 1) * cols + y];
        else
            backward = 0;

        unsigned char top;
        if (y - 1 >= 0)
            top = I[x * cols + (y - 1)];
        else
            top = 0;

        unsigned char down;
        if (y + 1 <= cols)
            down = I[x * cols + (y + 1)];
        else
            down = 0;

        return (current + forward + backward + top + down) / 5;
        
    }
};

int main(int argc, char *argv[]) {
    Imagem im = Imagem::read(std::string(argv[1]));

    //COPIAR PARA GPU
    thrust::device_vector<unsigned char> pixels_gpu(im.pixels, im.pixels + im.total_size);
    thrust::device_vector<unsigned char> pixels_gpu_saida(im.total_size);

    //transform
    media med(im.cols, im.rows, pixels_gpu.data().get());
    thrust::counting_iterator<int> iterator(0);
    thrust::transform(iterator, iterator+(im.total_size), pixels_gpu_saida.begin(), med);

    //copia de volta para a CPU
    thrust::copy(pixels_gpu.begin(), pixels_gpu.end(), im.pixels);

    im.write("out2.pgm");

    return 0;
}
