 #include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int i=0;
	int a[]={1,2,3,4,5};
	int b[]={6,7,8,9,10};
	int c[5];
	for(i=rank; i<5; i+=size)
	{	c[i]=a[i]+b[i];
		printf("%d\n",c[i]);
	}
	//sleep(5);
		printf("\n");
	return 0;
}