
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int factorial(int d){
	int sum = 1;
	while(d>1){
		sum*=d;
		d--;
	}
	return sum;
}

int main(int argc, char *argv[])
{
	int rank, size;
	int arr[50], brr[50];
	int recv;
	int n, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		n = size;
		printf("\n Enter %d no of Values \n",n);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
	}
	MPI_Scatter(arr, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\n I have received %d in process %d\n",recv, rank);
	int answer = factorial(recv);
	printf("\n Factorial of %d is : %d\n",recv, answer);
	//MPI_Reduce(&answer,&recv,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Gather(&answer,1,MPI_INT,&brr,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("\n Gathered factorial is \n");
		int sum=0;
		for(i=0; i<n; i++)
			{ sum+=brr[i];printf("%d ",brr[i]);}
		printf("\n Gathered Sum : %d",sum);
	}
	MPI_Finalize();
	return 0;
}
