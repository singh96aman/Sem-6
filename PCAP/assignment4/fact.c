#include <mpi.h>
#include <stdio.h>

int getSum(int n){
	int sum=0;
	while(n>=1){
		sum+=n;
		n--;
	}
	return sum;
}

int getFact(int n){
	int fact=1;
	while(n>1){
		fact*=n;
		n--;
	}
	return fact;
}

int main(int argc, char *argv[])
{
	int rank, size, n, sum=0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0)
		n=size;

	int count[n];

	if((rank+1)%2==0)
		{count[rank] = getSum(rank+1); }//printf("\n%d",count[rank]);}
	else
		{count[rank] = getFact(rank+1); }//printf("\n%d",count[rank]);}

	if(rank==0){
		for(int i=0; i<n; i++)
			{sum+=count[i]; printf("\n%d",count[i]);}
		printf("\n Sum is : %d",sum);
	}
	MPI_Finalize();
	return 0;
}