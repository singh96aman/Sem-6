#include <stdio.h>
#include <mpi.h>

int factorial(int d){
	int fact=1;
	while(d>=1){
		fact*=d;
		d--;
	}
	return fact;
}

int sum(int d){
	int sum=0;
	while(d>=0){
		sum+=d;
		d--;
	}
	return sum;
}

int main(int argc, char *argv[])
{
	int rank, size;
	int arr[50];
	int n, recv, ans;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		n=size;
	}

	if((rank+1)%2!=0)
		recv=factorial(rank+1);
	else
		recv=sum(rank+1);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&recv, &ans, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank==0)
		printf("\n Ans : %d",ans);

	MPI_Finalize();
	return 0;
}
