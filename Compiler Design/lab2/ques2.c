#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fa, *fb;
	char filename[50];
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
	while(ca!=EOF){
		if(ca=='#')
		{
			while(ca!='\n')
				ca = getc(fa);
			putc(ca,fb);
		}
		else if(ca=='"'){
			putc(ca,fb);
			ca = getc(fa);
			while(ca!='"')
			{
				putc(ca,fb);
				ca = getc(fa);
			}
			putc(ca,fb);
			ca = getc(fa);
		}
		else
			putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}