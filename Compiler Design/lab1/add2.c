#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr;
	char filename[50];
	printf("\n Enter the filename : ");
	scanf("%s",filename);
	fptr = fopen(filename,"r");
	char c = fgetc(fptr);
	int blanklines=0, linesendcolon=0, blankspaces=0;
	while(c!=EOF){
		printf("%c",c);
		if(c==';')
			{linesendcolon++; c = fgetc(fptr);}
		else if(c==' ')
			{blankspaces++; c = fgetc(fptr);}
		else if(c=='\n')
		{
			c = fgetc(fptr);
			while(c=='\n')
			{
				blanklines++;
				c = fgetc(fptr);
			}
		}
		else
			c = fgetc(fptr);
	}
	printf("\n Blank lines : %d\n Lines ending with semicolon : %d\n Blank spaces : %d",blanklines,linesendcolon,blankspaces);
	fclose(fptr);
	return 0;
}