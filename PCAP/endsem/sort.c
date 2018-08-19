#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int rank, size;
	int arr[4];
	int i, n;
	int recv[4];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
		scanf("%d",&n);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(arr,n,MPI_INT,0,MPI_COMM_WORLD);
	int min=arr[rank];
	int pos=0;
	for(i=0; i<n; i++)
		if(arr[i]<min || (arr[i]==min && i<rank))
			pos++;
	MPI_Gather(&pos,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0){
		int final[n];
		for(i=0; i<n; i++){
			final[recv[i]]=arr[i];
		}
		for(i=0; i<n; i++)
			printf("\n%d",final[i]);
	}
	MPI_Finalize();
	return 0;
}