#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	
	int rank, size;
	int i, n;
	int arr[4], arr2[4];
	int recv;
	int sum=0;
	double t1, t2;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank==0){
		scanf("%d",&n);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
	}

	t1 = MPI_Wtime();
	MPI_Bcast(&n,1,MPI_INT, 0, MPI_COMM_WORLD);
	if(rank==0)
		printf("\n Bcast : %d\n",n);
	MPI_Scatter(arr,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("\n MPI_Scatter %d %d\n",rank,recv);
	MPI_Reduce(&recv,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("\n Reduce : %d\n",sum);
		sum=0;
	}
	MPI_Gather(&recv,1,MPI_INT,&arr2,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("\n Gather : ");
		for(i=0; i<n; i++)
			printf("%d ",arr2[i]);
		printf("\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scan(&recv, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	printf("\n Scan %d rank %d\n",sum, rank);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0){
		printf("\n");
		scanf("%d",&i);
		MPI_Send(&i,1,MPI_INT,1,0,MPI_COMM_WORLD);
	}
	if(rank==1){
		MPI_Status status;
		MPI_Recv(&i,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		printf("Send : %d\n",i);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	//Allgather is exactly same as Bcast
	MPI_Barrier(MPI_COMM_WORLD);
	t2 = MPI_Wtime();
	if(rank==0)
		printf("\n Time : %lf\n",t2-t1);


	MPI_Finalize();
	return 0;
}