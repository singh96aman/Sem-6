#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		int n, i;
		//MPI_Status status;
		scanf("%d",&n);
		for(i=1; i<size; i++)
			MPI_Send((void*)&n, 1,MPI_INT,i,i,MPI_COMM_WORLD);
	}else
	{
		int n;
		MPI_Status status;
		MPI_Recv((void*)&n, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		printf("%d",n);
	}
	return 0;
}
