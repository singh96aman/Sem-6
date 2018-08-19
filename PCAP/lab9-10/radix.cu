#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global void radix(int *a, int *b, int n, int count){
	int id = threadIdx.x;
	int i=0, data=0, j=0, pos=0;
	int temp = a[id];

	while(j<=count){
		data=temp%10;
		temp/=10;
		j++;
	}

	for(i=0; i<n; i++){
		j=0;
		int data2, temp=a[i];
		while(j<=count){
			data2=temp%10;
			temp/=10;
			j++;
		}
		if(data2<data || (data2==data && i<id))
			pos++;
	}
	b[pos]=a[id];
}

int main(){
	//Standard input
	int A[]={170,450,750,900,802,240,200,660};
	int n=8;
	int i, k=3; //3 digit

	int size = sizeof(int)*n;

	int *d_a, *d_b;

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);

	for(i=0; i<k; i++){
		cudaMemcpy(d_a,&A,size,cudaMempyHostToDevice);
		radix<<<1,n>>>(d_a,d_b,n,i);
		cudaMemcpy(&A,d_b,size, cudaMemcpyDeviceToHost);
	}

	for(i=0; i<8; i++)
		printf("\n%d",A[i]);

	cudaFree(d_a);
	cudaFree(d_b);

	getchar()

	return 0;

}