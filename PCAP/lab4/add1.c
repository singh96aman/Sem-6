#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int i, input1[50], input2[50], recv1[50], recv2[50], res[50], output[50];
	if(rank==0)
	{
		for(i=0; i<9; i++)
			scanf("%d",&input1[i]);
		for(i=0; i<9; i++)
			scanf("%d",&input2[i]);
	}	
	MPI_Scatter(input1,3,MPI_INT,recv1,3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(input2,3,MPI_INT,recv2,3,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0; i<3; i++)
		res[i]=recv1[i]+recv2[i];
	MPI_Gather(res,3,MPI_INT,output,3,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
		for(i=0; i<9; i++)
			printf("%d ",output[i]);
	MPI_Finalize();
	return 0;
}