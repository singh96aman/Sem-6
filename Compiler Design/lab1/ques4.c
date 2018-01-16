#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr;
	char filename[50];
	printf("\n Enter the filename : ");
	scanf("%s",filename);
	fptr = fopen(filename,"r");
	if(fptr==NULL)
		printf("\n Cannot open file");
	fseek(fptr,0,SEEK_END);
	long n = ftell(fptr);
	printf("\n File Size is %d",n);
	return 0;
}