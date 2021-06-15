#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#include <iostream>

#include "imagem.hpp"

struct Limiar {
    unsigned char* ptr;
    int cols, rows;

    __host__ __device__ unsigned char operator()(const int& i) {
        int x = i % cols;
        int y = i / cols;
        return (ptr[i] + ptr[i + 1] + ptr[i - 1]) / 3;
    }
};

int main(int argc, char* argv[]) {
    Imagem img = Imagem::read(std::string(argv[1]));

    std::cout << img.rows << "\n";

    thrust::device_vector<unsigned char> img_gpu(img.pixels, img.pixels + img.total_size);
    thrust::device_vector<unsigned char> pixels_out(img.total_size);

    Limiar limiar = {
        .ptr = img_gpu.data().get(),
        .cols = img.cols,
        .rows = img.rows,
    };

    thrust::transform(thrust::make_counting_iterator<int>(0),
                      thrust::make_counting_iterator<int>(img.total_size),
                      pixels_out.begin(),
                      limiar);

    thrust::copy(img_gpu.begin(), img_gpu.end(), img.pixels);
    img.write(std::string(argv[2]));

    return 0;
}