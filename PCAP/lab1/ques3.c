#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int a=8, b=4;
	if(rank==0)
	{
		printf("\n Rank %d Addition %d + %d = %d",rank,a,b,a+b);
	}
	else if(rank==1)
	{
		printf("\n Rank %d Subtraction %d - %d = %d",rank,a,b,a-b);
	}
	else if(rank==2)
	{
		printf("\n Rank %d Multiplication %d * %d = %d",rank,a,b,a*b);
	}
	else
		printf("\n Rank %d Division %d / %d = %d",rank,a,b,a/b);

	MPI_Finalize();
	return 0;
}