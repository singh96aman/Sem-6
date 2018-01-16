#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr;
	char filename[50], buffer[50][50];
	printf("\n Enter the filename : ");
	scanf("%s",filename);
	fptr = fopen(filename,"r");
	if(fptr==NULL)
		printf("\n Cannot open file");
	char c = fgetc(fptr);
	int lines=0, index=0;
	while(c!=EOF){
		if(c=='\n')
			{buffer[lines][index]='\0'; lines++; index=0;}
		else
			buffer[lines][index++]=c;
		c = fgetc(fptr);
	}
	char choice='c';
	int i=0;
	index=0;
	while(choice=='c'){
		printf("\n Enter Your Choice (c/q) : \n");
		scanf(" %c",&choice);
		if(choice=='q')
			exit(0);
		else
		{
			for(i=index; i<index+5; i++)
				printf("\n %s",buffer[i]);
			index+=5;
		}
	}
	return 0;
}