
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, sum=0, n;
	int i,j,a[4][4], b[16], arr[4];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/*
	if(rank==0){
		printf("\n Enter 4*4 matrix :\n");
		for(i=0; i<4; i++)
			for(j=0; j<4; j++)
				scanf("%d",&a[i][j]);
	}
	MPI_Scatter(a,4,MPI_INT,b,3,MPI_INT, 0, MPI_COMM_WORLD);
	for(i=0; i<4; i++)
		sum+=b[i];
	MPI_Gather(&sum,1, MPI_INT,&final,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
		for(i=0; i<4; i++)
			printf("%d ",final[i]);
	}

	*/
	if(rank==0){
		n=4;
		printf("\n Enter 4*4 matrix :\n");
		for(i=0; i<4; i++)
			for(j=0; j<4; j++)
				scanf("%d",&a[i][j]);
		int k=0;
		for(j=0; j<4; j++)
			for(i=0; i<4; i++)
				{b[k]=a[i][j]; k++;}

	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&b, n, MPI_INT, &arr, n, MPI_INT, 0, MPI_COMM_WORLD);
	for(i=1; i<4; i++)
		arr[i]+=arr[i-1];
	MPI_Gather(&arr,n,MPI_INT,&b,n,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		for(i=0; i<16; i++)
		{
			printf("%d ",b[i]);
			if(i%4==0)
				printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}
