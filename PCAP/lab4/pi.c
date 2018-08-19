#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int i, n;
	double res;
	if(rank==0){
		printf("\n Enter no of intervals : ");
		scanf("%d",&n);
	}
	MPI_Bcast(&n,1,MPI_INT, 0, MPI_COMM_WORLD);
	double x=0, h=0, sum=0.0, mypi;
	if(n!=0){
		h=1.0/n;
		for(i=rank+0.5; i<n; i+=size){
			x += 1.0 / (1.0 + (i*h)*(i*h));
		}
		mypi = 4.0*x*h;

	}
	MPI_Reduce(&mypi,&res, 1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("\nThe value of pi is : %f",res);
	}
	MPI_Finalize();
	return 0;
}