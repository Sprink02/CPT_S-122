%% cuda
#include <stdio.h>

__global__ void simpleKernel() {
    printf("Hello world\n");
}

int main() {
    simpleKernel << <1, 1 >> > ();

    cudaDeviceSynchronize();

    return 0;
}