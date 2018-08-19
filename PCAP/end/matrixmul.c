#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank, size;
	int n, i, j, a[3][3], b[3][3], res[3], temp[3], c[3][3];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0)
	{
		n=size;
		for(i=0; i<n; i++)
			for(j=0; j<n; j++)
				scanf("%d",&a[i][j]);

		for(i=0; i<n; i++)
			for(j=0; j<n; j++)
				scanf("%d",&b[i][j]);
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&b,n*n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(a,n,MPI_INT,&res,n,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0; i<n; i++)
		temp[i]=0;

	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			temp[i]+=res[j]*b[i][j];

	MPI_Gather(&temp,n,MPI_INT,c,n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank==0){
		for(i=0; i<n; i++){
			for(j=0; j<n; j++)
				printf("%d ",c[i][j]);
		printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}