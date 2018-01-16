#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1, *fptr2, *fptr3;
	char file1[50], file2[50], file3[50];
	
	printf("\n Enter the file 1 : ");
	scanf("%s",file1);
	fptr1 = fopen(file1,"r");

	printf("\n Enter the file 2 : ");
	scanf("%s",file2);
	fptr2 = fopen(file2,"r");

	printf("\n Enter the file 3 : ");
	scanf("%s",file3);
	fptr3 = fopen(file3,"w+");
	
	if(fptr1==NULL)
		printf("\n Cannot open file 1");

	if(fptr2==NULL)
		printf("\n Cannot open file 2");

	char c = fgetc(fptr1);
	char d = fgetc(fptr2);

	while(c!=EOF && d!=EOF)
	{
		while(c!='\n' && c!=EOF)
			{ fputc(c, fptr3); printf("\n%c",c);c = fgetc(fptr1);}
		fputc('\n',fptr3);
		while(d!='\n' && d!=EOF)
			{ fputc(d, fptr3); printf("\n%c",d);d = fgetc(fptr2);}
		fputc('\n',fptr3);
		c = fgetc(fptr1);
		d = fgetc(fptr2);
	}
	printf("\n Contents copied to %s",file3);
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}