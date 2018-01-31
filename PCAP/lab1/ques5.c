 #include <mpi.h>
#include <stdio.h>

void createPrime(int low, int high)
{
	int i, j, flag=0;
	for(i=low; i<=high; i++)
	{
		for(j=i-1; j>=2; j--)
			if(i%j==0)
			{
				flag=1;
				break;
			}
		if(flag==0)
			printf("\n%d",i);
		flag=0;
	}
}

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
		createPrime(2,49);
	else
		createPrime(50,100);
	MPI_Finalize();
	return 0;
}