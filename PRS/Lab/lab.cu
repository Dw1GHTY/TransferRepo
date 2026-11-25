#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define N 5


// Resenje ako zelimo jedan blok sa vise niti
__global__ void izracunaj_niz(float* input_array, int array_size, float* out_array)
{
	if (threadIdx.x < array_size - 2) 
	{
		out_array[threadIdx.x] = (input_array[threadIdx.x] + input_array[threadIdx.x + 1] + input_array[threadIdx.x + 2]) / 3;
	}
}


int main() 
{
	float a[N], b[N-2];
	float* dev_a;
	float* dev_b;

	// Alokacija memorije na Device-u
	cudaMalloc((void**)& dev_a, sizeof(float) * N);
	cudaMalloc((void**)&dev_b, sizeof(float) * (N - 2));	// manje za 2 jer niz b uvek ima 2 manje elementa

	// Inicijalizacija niza a[N] nasumicnim brojevima - na Host-u
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 10 + 1;
	}

	// Kopiranje Host -> Device
	cudaMemcpy(dev_a, a, N * sizeof(float), cudaMemcpyHostToDevice);

	// Pozivanje kernel-a
	izracunaj_niz <<<1, N - 2>>> (dev_a, N, dev_b);	

	// Kopiranje Device -> Host / pribavljanje rezultata
	cudaMemcpy(b, dev_b, (N - 2) * sizeof(float), cudaMemcpyDeviceToHost);

	// Oslobadjanje memorije Device-a
	cudaFree(dev_a);
	cudaFree(dev_b);

	// Prikaz rezultata
	printf("A: ");
	for (int i = 0; i < N; i++)
	{
		printf("%.2f ", a[i]);
	}
	printf("\nB: ");
	for (int i = 0; i < N - 2; i++)
	{
		printf("%.2f ", b[i]);
	}
	printf("\n");

	return 0;
}