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
		int arr[50];
		int buffer[100];
		MPI_Buffer_attach(buffer,100);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
		MPI_Send((void*)&n, 1,MPI_INT,1,0,MPI_COMM_WORLD);
		for(i=1; i<n; i++)
			MPI_Bsend(&arr[i], 1,MPI_INT,i,i,MPI_COMM_WORLD);
		printf("\nRank %d computes %d as : %d",rank,arr[0],arr[0]*arr[0]);
		MPI_Buffer_detach(buffer,100);
	}else{
		int n;
		MPI_Status status;
		MPI_Recv((void*)&n, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		if(rank%2==0)
			printf("\nRank %d computes %d as : %d",rank,n,n*n);
		else
			printf("\nRank %d computes %d as : %d",rank,n,n*n*n);
	}
	return 0;
}
