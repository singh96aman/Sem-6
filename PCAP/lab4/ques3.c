#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int rank, size, find, count=0, ans;
		int arr[50], brr[50];
		int recv[50];
		int n, i;
		MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		if(rank==0)
		{
			n=3;
			printf("\n Enter Value of 3*3 \n");
			for(i=0; i<n*n; i++)
				scanf("%d",&arr[i]);
			printf("\n Enter the value to find : ");
			scanf("%d",&find);
		}
		MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Bcast(&find,1,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Scatter(arr, n, MPI_INT, &recv, n, MPI_INT, 0, MPI_COMM_WORLD);
		for(i=0; i<n; i++)
			if(recv[i]==find)
			{
				printf("\n %d found at %d position in process %d\n",find,i,rank);
				count++;
			}
	MPI_Reduce(&count, &ans, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank==0)
		printf("\n No of occurences are : %d",count);
    MPI_Finalize();
    return 0;
}
