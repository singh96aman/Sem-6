#include <mpi.h>
#include <stdio.h>
#include <string.h>

int factorial(int d){
	int sum = 1;
	while(d>1){
		sum*=d;
		d--;
	}
	return sum;
}

int main(int argc, char *argv[])
{
	int rank, size;
	int arr[50];
	int recv;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		int n, i;
		n = size;
		printf("\n Enter %d no of Values \n",n);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
	}
	MPI_Scatter(arr, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\n I have received %d in process %d\n",recv, rank);
	int answer = factorial(recv);
	printf("\n Factorial of %d is : %d\n",recv, answer);
	MPI_Finalize();
	return 0;
}
