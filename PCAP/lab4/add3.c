#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int i,j,index=0,arr[50][50], in[50], in2[50], recv[50], rowmax[50], colmax[50];
	if(rank==0)
	{
		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				scanf("%d",&arr[i][j]);

		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				in[index++]=arr[i][j];

		index=0;
		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				in2[index++]=arr[j][i];

	}
	MPI_Scatter(in,3,MPI_INT,recv,3,MPI_INT,0,MPI_COMM_WORLD);
	int max=0;
	for(i=0; i<3; i++)
		if(max<recv[i])
			max=recv[i];
	MPI_Gather(&max,1,MPI_INT,rowmax,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
		for(i=0; i<3; i++)
			printf("%d ",rowmax[i]);

	MPI_Scatter(in2,3,MPI_INT,recv,3,MPI_INT,0,MPI_COMM_WORLD);
	max=0;
	for(i=0; i<3; i++)
		if(max<recv[i])
			max=recv[i];
	MPI_Gather(&max,1,MPI_INT,colmax,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
		for(i=0; i<3; i++)
			printf("%d ",colmax[i]);
	MPI_Finalize();
	return 0;
}