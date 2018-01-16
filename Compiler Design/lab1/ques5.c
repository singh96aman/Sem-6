#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1, *fptr2;
	char file1[50], file2[50];
	
	printf("\n Enter the file 1 : ");
	scanf("%s",file1);
	fptr1 = fopen(file1,"r");

	printf("\n Enter the file 2 : ");
	scanf("%s",file2);
	fptr2 = fopen(file2,"r");
	
	if(fptr1==NULL)
		printf("\n Cannot open file 1");

	if(fptr2==NULL)
		printf("\n Cannot open file 2");

	char c = fgetc(fptr1);
	char d = fgetc(fptr2);

	int flag=0;
	while(c!=EOF && d!=EOF){
		if(c==EOF)
			{flag=1; break;}
		if(d==EOF)
			{flag=1; break;}
		if(c!=d)
			{flag=1; break;}
		c = fgetc(fptr1);
		d = fgetc(fptr2);
	}
	if(flag==0)
		printf("\n File are same");
	else
		printf("\n File are different");
	return 0;
}