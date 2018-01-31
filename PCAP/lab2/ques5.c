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
		MPI_Status status;
		scanf("%d",&n);
		printf("\n Rank %d n = %d",rank,n);
		n++;
		MPI_Ssend((void*)&n, 1,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Recv((void*)&n, 1, MPI_INT, size-1, 1, MPI_COMM_WORLD, &status);
		printf("\n Rank %d n = %d",rank,n);
	}
	else
	{
		int n;
		MPI_Status status;
		MPI_Recv((void*)&n, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
		printf("\n Rank %d n = %d",rank,n);
		n++;
		if(rank==size-1)
			MPI_Ssend((void*)&n, 1,MPI_INT,0,1,MPI_COMM_WORLD);
		else
			MPI_Ssend((void*)&n, 1,MPI_INT,rank+1,1,MPI_COMM_WORLD);
	}
	return 0;
}


