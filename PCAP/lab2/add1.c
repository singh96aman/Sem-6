#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int found, i, n, arr[50], recv[50], count=0, ans=0, brr[50];
	if(rank==0)
	{
		printf("Enter : \n");
		scanf("%d",&n);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
		printf("Enter no of find : \n");
		scanf("%d",&found);
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&found,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,n/2,MPI_INT,&recv,n/2,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0; i<n/2; i++)
		if(found==arr[i])
			count++;
	//MPI_Reduce(&count,&ans,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Gather(&count,1,MPI_INT,&brr,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
		for(i=0; i<size; i++)
			printf("Count is : \n%d",brr[i]);
	MPI_Finalize();
	return 0;
}