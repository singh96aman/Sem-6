#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int arr[50], brr[50];
	int recv[50];
	int m,n, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		n = size;
		printf("\n Enter value Of M : ");
		scanf("%d",&m);
		printf("\n Enter Value of m*n \n");
		for(i=0; i<m*n; i++)
			scanf("%d",&arr[i]);
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr, m, MPI_INT, &recv, m, MPI_INT, 0, MPI_COMM_WORLD);
	int sum=0;
	for(i=0; i<m; i++)
		sum+=recv[i];
	printf("\n Process : %d & Avg : %d",rank,sum/m);
	sum/=m;
	MPI_Gather(&sum,1,MPI_INT,&arr,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
	sum=0;
	for(i=0; i<m; i++)
	{
		//printf("\n%d",arr[i]);
		sum+=arr[i];
	}
	printf("\n Total Avg : %d",sum/m);
	}
	MPI_Finalize();
	return 0;
}
