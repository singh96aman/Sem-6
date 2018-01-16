#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1, *fptr2;
	char filename[100], c;
	printf("\n Enter file name to open for reading : ");
	scanf("%s",filename);
	fptr1 = fopen(filename, "r");
	if(fptr1==NULL){
		printf("\n Cannot open file %s",filename);
		exit(0);
	}
	printf("\n Enter filename for writing : ");
	scanf("%s",filename);
	fptr2 = fopen(filename, "w+");
	c = fgetc(fptr1);
	while(c!=EOF){
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}
	printf("\n Contents copied to %s",filename);
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}