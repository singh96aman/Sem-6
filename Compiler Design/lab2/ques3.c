#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fa, *fb;
	char filename[50];
	char keywords[6][50] = {"int","main","if","else","char","return"};
	printf("\n Enter the filename to open: ");
	scanf("%s",filename);
	fa = fopen(filename,"r");
	printf("\n Enter the filename to close: ");
	scanf("%s",filename);
	fb = fopen(filename, "w+");
	if(fa==NULL)
		printf("\n Cannot open file");
	if(fb==NULL)
		printf("\n Cannot open file");
	char ca = getc(fa);
	char buffer[50];
	int index=0, i, k, flag=1;
	while(ca!=EOF){
		if(ca==' ' || ca=='(' || ca=='\n' || ca=='\t'){
			buffer[index]='\0';
			for(i=0; i<6; i++)
				if(strcmp(buffer,keywords[i])==0)
					{
						//fseek(fa,-1*index, SEEK_CUR);
						for(k=0; buffer[k]!='\0'; k++)
							buffer[k]-=32;
					}
			for(k=0; buffer[k]!='\0'; k++)
				putc(buffer[k],fb);
			putc(ca,fb);
			index=0;
		}else{
			buffer[index++]=ca;
			//putc(ca,fb);
		}
		ca = getc(fa);
	}
	for(k=0; buffer[k]!='\0'; k++)
		putc(buffer[k],fb);
	fclose(fa);
	fclose(fb);
	return 0;
}