#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <math.h> 
#include "imagem.hpp"
#include <thrust/iterator/constant_iterator.h>
#include <vector>

struct limiar
{
    int cols;
    limiar(int cols) : cols(cols) {};
    __host__ __device__

    unsigned char operator()(const unsigned char &p) {
        if(p > 127){
            return 255;
        }else{
            return 0;
        }
        
    }
};

int main(int argc, char *argv[]) {
    Imagem im = Imagem::read(std::string(argv[1]));

    //COPIAR PARA GPU
    thrust::device_vector<unsigned char> pixels_gpu(im.pixels, im.pixels + im.total_size);

    //transform
    limiar lim(im.cols);
    thrust::transform(pixels_gpu.begin(), pixels_gpu.end(), pixels_gpu.begin(), lim);

    //copia de volta para a CPU
    thrust::copy(pixels_gpu.begin(), pixels_gpu.end(), im.pixels);

    im.write("out.pgn");

    return 0;
}
