// multiply MXN and NXP

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int i,j, m, n, p, ans=0;
	int input1[3][3], input2[3][], matrix1[50], matrix2[50], temp1[50], temp2[50], res[50], final[50];
	if(rank==0){
		printf("Enter M : \n");
		scanf("%d",&m);
		printf("Enter N : \n");
		scanf("%d",&n);
		printf("Enter P : \n");
		scanf("%d",&p);
		printf("Enter Matrix 1\n");

		for(i=0; i<m; i++)
			for(j=0; j<n; j++)
			scanf("%d",&input1[i][j]);
		for(i=0; i<n; i++)
			for(j=0; j<p; j++)
				scanf("%d",&input2[j][i]);
		int index=0;

		/*
		for(i=0; i<n; i++)
			for(j=0; j<p; j++)
			matrix1[index++]=input1[i][j];
		index=0;

		for(i=0; i<n; i++)
			for(j=0; j<p; j++)
			matrix2[index++]=input2[i][j];*/

	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&p,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(input1,n,MPI_INT,&temp1,n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(input2,n,MPI_INT,&temp2,n,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0; i<n; i++)
		printf("%d ",temp1[i]);
	printf("\n");
	for(i=0; i<n; i++)
		printf("%d ",temp2[i]);
	printf("\n");
	//for(i=0;i<n; i++)
	//{	res[i]=temp1[i]*temp2[i];
	//	ans += res[i];}

	//MPI_Gather(ans,1,MPI_INT,final,1,MPI_INT,0,MPI_COMM_WORLD);
	//if(rank==0)
	//{
		//for(i=0; i<n; i++)
		//printf("%d ",final[i]);}

	MPI_Finalize();
	return 0;
}