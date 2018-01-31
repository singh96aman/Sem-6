
#include <stdio.h>
#include <mpi.h>
#include <math.h>

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
	int c=3;
	int numtasks, rank, len, error_code;
	error_code = MPI_Init(&argc, &argv);
	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	error_code = MPI_Comm_size(c,&numtasks);
	ErrorHandler(error_code);
	MPI_Finalize();
	return 0;
}
