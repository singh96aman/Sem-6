#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank, size;
	int n, i, j, a[4][4], b[4], recv[4], sum;
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
	MPI_Scatter(a,n,MPI_INT,&b,n,MPI_INT,0,MPI_COMM_WORLD);

	int max=0;
	for(i=0; i<n; i++)
		if(b[i]>max)
			max=b[i];

	MPI_Gather(&max,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank==0){
		int temp=recv[n-1];
		for(i=n-2; i>=0; i--)
			recv[i+1]=recv[i];
		recv[0]=temp;
		for(i=0; i<n; i++)
			printf("%d ",recv[i]);
		printf("\n");
	}

	MPI_Scatter(&recv,1,MPI_INT,&sum,1,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0; i<n; i++)
		b[i]+=sum;

	MPI_Gather(&b,n,MPI_INT,&a,n,MPI_INT,0,MPI_COMM_WORLD);
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