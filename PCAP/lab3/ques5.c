#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int rank, size;
	char a=rr1[5], arr2[5];
	int len;
	char buf1, buf2;
	char temp[3];
	char res[50];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
		len=size;
		printf("\n Enter String 1 : \n");
		scanf("%s",arr1);
		printf("\n Enter String 2 : \n");
		scanf("%s",arr2);
	}
	MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr1,1,MPI_CHAR,&buf1,1,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(arr2,1,MPI_CHAR,&buf2,1,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	temp[0]=buf1; temp[1]=buf2; temp[2]='\0';
	MPI_Gather(temp,2,MPI_CHAR,res,2,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0){
		res[2*len]='\0';
		printf("\n%s",res);
	}
	MPI_Finalize();
	return 0;
}