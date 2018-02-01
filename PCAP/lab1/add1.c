// multiply MXN and NXP

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int i, m, n, p;
	int matrix1[50], matrix2[50], temp1[50], temp2[50];
	if(rank==0){
		printf("Enter M : \n");
		scanf("%d",&m);
		printf("Enter N : \n");
		scanf("%d",&n);
		printf("Enter P : \n");
		scanf("%d",&p);
		printf("Enter Matrix 1\n");

		for(i=0; i<m*n; i++)
			scanf("%d",&matrix1[i]);
		for(i=0; i<n*p; i++)
				scanf("%d",&matrix2[i]);
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&p,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(matrix1,m,MPI_INT,&temp1,m, MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(matrix2,n,MPI_INT,&temp2,n,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0; i<)


	MPI_Finalize();
	return 0;
}