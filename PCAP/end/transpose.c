#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank, size;
	int n, i, j, a[3][3], b[3];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0){
		n=size;
		for(i=0; i<n; i++)
			for(j=0; j<n; j++)
				scanf("%d",&a[i][j]);
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0; i<n; i++)
		MPI_Scatter(&a[i],1,MPI_INT,&b[i],1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Gather(&b,n,MPI_INT,a,n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank==0){
		for(i=0; i<n; i++){
			for(j=0; j<n; j++)
				printf("%d ",a[i][j]);
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}