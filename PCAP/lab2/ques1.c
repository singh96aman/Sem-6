#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		//char arr[] = "Aman";
		char arr[50];
		MPI_Status status;
		fgets(arr,10,stdin);
		int len=strlen(arr);
		MPI_Ssend((void*)&len, 1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Ssend((void*)&arr, len , MPI_CHAR,1,1,MPI_COMM_WORLD);
		MPI_Recv((void*)&arr, len, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
		printf("%s",arr);
	}else{
		char arr2[50];
		int len, i;
		MPI_Status status;
		MPI_Recv((void*)&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv((void*)&arr2, len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
		for(i=0; i<len; i++)
			arr2[i]++;
		MPI_Ssend((void*)&arr2, len , MPI_CHAR,0,2,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
