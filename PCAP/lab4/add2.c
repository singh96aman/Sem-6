#include <stdio.h>
#include <mpi.h>

int checkPrime(int n)
{
	int i=n, j, flag=0;
	if(n==0 || n==1)
		return 0;
		for(j=n-1; j>=2; j--)
			if(i%j==0)
			{
				flag=1;
				break;
			}
		if(flag==0)
			return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int i, input[50], recv1[50], sum=0, answer=0;
	if(rank==0)
		for(i=0; i<9; i++)
			scanf("%d",&input[i]);

	MPI_Scatter(input,3,MPI_INT,recv1,3,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0; i<3; i++)
		if(checkPrime(recv1[i]))
			sum+=recv1[i];

	//printf("%d\n",sum);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&sum,&answer,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
		printf("%d",answer);
	MPI_Finalize();
	return 0;
}
