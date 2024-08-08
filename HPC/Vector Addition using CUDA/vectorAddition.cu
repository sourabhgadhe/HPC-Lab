#include <stdio.h>
#define SIZE 50000

__global__ void p_vecAdd(int *a, int *b, int *c, int n)
{
	int i = threadIdx.x;
	if (i < n)
	{
		c[i] = a[i] + b[i];
	}
}

void s_vecAdd(int *a, int *b, int *c, int n)
{

	for (int i = 0; i < n; i++)
	{
		c[i] = a[i] + b[i];
	}
}

int main()
{
	int *a, *b, *c;

	cudaMallocManaged(&a, SIZE * sizeof(int));
	cudaMallocManaged(&b, SIZE * sizeof(int));
	cudaMallocManaged(&c, SIZE * sizeof(int));

	for (int i = 0; i < SIZE; i++)
	{
		a[i] = i;
		b[i] = i;
		c[i] = 0;
	}

	clock_t start = clock();
	p_vecAdd<<<10, SIZE>>>(a, b, c, SIZE);
	clock_t end = clock();
	double elapsed_sec = ((double)(end - start)) / CLOCKS_PER_SEC;
	long long nanoseconds = (long long)(elapsed_sec * 1e9);
	printf("\nTime taken for kernel exexution=%lld\n nanosec", nanoseconds);

	clock_t start2 = clock();
	s_vecAdd(a, b, c, SIZE);
	clock_t end2 = clock();
	double elapsed_sec2 = (double(end2 - start2)) / CLOCKS_PER_SEC;
	long long nanosec2 = (long long)(elapsed_sec2 * 1e9);
	printf("\nTime taken for seq. execution=%lld nanosec", nanosec2);

	cudaDeviceSynchronize();

	for (int i = 0; i < SIZE; i++)
	{
		printf("\nc[%d]=%d", i, c[i]);
	}
}