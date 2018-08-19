#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	//Matrix Multiplication

	int i, j, m, n, p;
	int rank, size;
	int arr[20];
	int arr2[20];
	int recv[20];
	int sum[20];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	// M*N N*P
	if(rank==0){
		scanf("%d %d",&m,&n);
		for(i=0; i<m*n; i++)
			scanf("%d",&arr[i]);
		scanf("%d %d",&n,&p);
		for(i=0; i<n*p; i++)
			scanf("%d",&arr2[i]);
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&p,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&arr,n,MPI_INT,&recv,n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&arr2,n*p,MPI_INT,0,MPI_COMM_WORLD);
	//printf("\n Rank %d",rank);
	for(i=0; i<n; i++){
		sum[i]=0;
		for(j=0; j<p; j++){
			sum[i]+=recv[j]*arr2[j];
		}
	}
	MPI_Gather(&sum[0],p,MPI_INT,&arr[0],p,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0){
		for(i=0; i<m*p; i++){
			printf("%d ",arr[i]);
			if(i!=0 && (i+1)%p==0)
				printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
	
	//Send columns in matrix

	/*int i, j, n;
	int rank, size;
	int arr[3][3];
	int recv[3];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
		scanf("%d",&n);
		for(i=0; i<n; i++)
			for(j=0; j<n; j++)
				scanf("%d",&arr[i][j]);
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0; i<n; i++)
		MPI_Scatter(&arr[i],1,MPI_INT,&recv[i],1,MPI_INT,0,MPI_COMM_WORLD);
	printf("\n Rank %d : ",rank);
	for(i=0; i<n; i++){
			printf("%d ",recv[i]);
	}
	printf("\n");
	MPI_Finalize();
	return 0;*/

	//Send Rows in matrix

	/*int rank, size;
	int i, n;
	int arr[9];
	int recv[3];
	int recv2[3];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
		scanf("%d",&n);
		for(i=0; i<n*n; i++)
			scanf("%d",&arr[i]);
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&arr[0],n,MPI_INT,&recv[0],n,MPI_INT,0,MPI_COMM_WORLD);
	printf("\n Rank %d : ",rank);
	for(i=0; i<n; i++)
		printf("%d ",recv[i]);
	printf("\n");

	MPI_Finalize();
	return 0;*/

}