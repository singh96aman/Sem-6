#include <stdio.h>
#include <mpi.h>

void ErrorHandler(int error_code){
	if(error_code != MPI_SUCCESS){
		char error_string[400];
		int length_of_error_string, error_class;
		MPI_Error_class(error_code, &error_class);
		MPI_Error_string(error_class, error_string, &length_of_error_string);
		fprintf(stderr,"%s %d\n",error_string,length_of_error_string);
		MPI_Error_string(error_code,error_string,&length_of_error_string);
		fprintf(stderr,"Hello_ErrorCode %s\n",error_string);
	}
}

int main(int argc, char *argv[])
{
	int rank, size;
	int i,j,n=3;
	//int arr[n];
	int arr[n];
	int recv[n];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
	int error_code=MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
	ErrorHandler(error_code);
	if(rank==0){
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
	}
	MPI_Bcast(&arr,n,MPI_INT,0, MPI_COMM_WORLD);
	MPI_Alltoall(&arr,1,MPI_INT,&recv,1,MPI_INT,MPI_COMM_WORLD);
	printf("\n rank : %d ",rank);
	for(i=0; i<n; i++){
		printf("%d ",recv[i]);
	}
	printf("\n");
	MPI_Finalize();
	return 0;
}