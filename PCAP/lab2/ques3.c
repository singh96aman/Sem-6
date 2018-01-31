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
		int arr[50];
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
		MPI_Send((void*)&n, 1,MPI_INT,1,0,MPI_COMM_WORLD);
		for(i=0; i<n/2; i++)
			MPI_Send((void*)&arr[i], 1,MPI_INT,1,1,MPI_COMM_WORLD);
		int sum=0;
		double t1, t2;
		t1 = MPI_Wtime();
		for(i=(n/2); i<n; i++)
			sum+=arr[i];
		t2 = MPI_Wtime();
		printf("\n %d sum and time %lf ",sum,t2-t1);
		MPI_Recv((void*)&n, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
		printf("\n  Sum is : %d",sum+n);
	}else{
		int i, n;
		int sum=0;
		int arr[100];
		double t1, t2;
		MPI_Status status;
		MPI_Recv((void*)&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		for(i=0; i<n/2; i++)
			MPI_Recv((void*)&arr[i], 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		t1 = MPI_Wtime();
		for(i=0; i<n/2; i++)
			sum+=arr[i];
		t2 = MPI_Wtime();
		printf("\n %d sum and time %lf ",sum,t2-t1);
		MPI_Ssend((void*)&sum, 1,MPI_INT,0,2,MPI_COMM_WORLD);
	}
	return 0;
}
