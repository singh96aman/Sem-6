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
	char c = fgetc(fptr);
	int lines=0, characters=0;
	while(c!=EOF){
		if(c=='\n')
			lines++;
		else
			characters++;
		c = fgetc(fptr);
	}
	printf("\n %s has %d lines and %d characters \n",filename,lines,characters);
	return 0;
}