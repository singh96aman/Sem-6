#include <mpi.h>
#include <stdio.h>
#include <string.h>

int prime(int d){
	int flag=1, i;
	for(i=d-1; i>=2; i--)
		if(d%i==0){
			flag=0; break;
		}
	return flag;
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
	if(prime(recv))
		printf("\n %d is Prime !\n", recv);
	else
		printf("\n %d is not Prime !\n", recv);
	MPI_Finalize();
	return 0;
}
