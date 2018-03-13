#include <stdio.h>
#include <mpi.h>

/*
mpicc -o simulatempireduce simulatempireduce.c
mpirun -np 2 ./simulatempireduce
*/

int main(int argc, char *argv[])
{
	int rank, size;
	int arr[50], recv=0, sum=0;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank==0){
		for(int i=0; i<size; i++)
			scanf("%d",&arr[i]);
		recv=arr[0];
		for(int i=1; i<size; i++)
			MPI_Send(&arr[i],1,MPI_INT, i, i, MPI_COMM_WORLD);
	}else
		MPI_Recv((void*)&recv,1,MPI_INT,0,rank,MPI_COMM_WORLD, &status);

	MPI_Send((void*)&recv, 1,MPI_INT,0,rank,MPI_COMM_WORLD);

	if(rank==0){
		for(int i=0; i<size; i++){
			MPI_Recv((void*)&recv, 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);
			sum+=recv;
		}
		printf("\n%d",sum);
	}
	
	MPI_Finalize();
	return 0;
}