#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i, rank, size;
	int len;
	char arr[50], recv[10], res[50];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
		printf("\n Enter String 1 : \n");
		scanf("%s",arr);
		len=strlen(arr);
	}
	MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,len/size,MPI_CHAR,recv,len/size,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	for(i=0; i<len/size; i++)
		recv[i]++;
	MPI_Gather(recv,len/size,MPI_CHAR,res,len/size,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0){
		res[len]='\0';
		printf("\n Result : %s",res);
	}
	MPI_Finalize();
	return 0;
}