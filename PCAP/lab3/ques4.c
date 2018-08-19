#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int len, rank, size;
	char arr[50], rev[50];
	int indexarr[50];
	char finalarray[50];
	int n, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		n = size;
		printf("\n Enter a String : ");
		scanf("%s",arr);
		len= strlen(arr);
	}
	MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&arr[0], len/n, MPI_CHAR, &rev[0], len/n, MPI_CHAR, 0, MPI_COMM_WORLD);
	int index=0;
	char nonvowel[50];
	for(i=0; i<len/n; i++)
		if(rev[i]=='a' || rev[i]=='e' || rev[i]=='i' || rev[i]=='o' || rev[i]=='u')
			continue;
		else
			nonvowel[index++]=rev[i];

	MPI_Gather(&index,1,MPI_INT,&indexarr,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Gather(&nonvowel,index,MPI_CHAR,&finalarray,index,MPI_CHAR,0,MPI_COMM_WORLD);
	printf("\n Rank : %d has no of vowels as : %d",rank,index);
	for(i=0; i<index; i++)
		printf(" %c ",nonvowel[i]);
	if(rank==0)
	{
		int total=0;
		for(i=0; i<size; i++)
			total+=indexarr[i];
		for(i=0; i<total; i++)
			printf(" %c ",finalarray[i]);

	}
	MPI_Finalize();
	return 0;
}

