#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	char arr[50], brr[50], res[50];
	int i=0, n;
	if(rank==0)
	{
		scanf("%d",&n);
		scanf("%s",arr);
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);	
	MPI_Scatter(arr,1,MPI_CHAR,&brr,1,MPI_CHAR,0,MPI_COMM_WORLD);
	i=1;
	for(; i<rank+1; i++)
		brr[i]=brr[i-1];
	for(;i<n; i++)
		brr[i]='-';
	//printf("%s\n",brr);
	MPI_Gather(brr,n,MPI_CHAR,res,n,MPI_CHAR,0,MPI_COMM_WORLD);
	if(rank==0)
		for(i=0; i<n*n; i++)
			if(res[i]!='-')
				printf("%c",res[i]);
	MPI_Finalize();
	return 0;
}