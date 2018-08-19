#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *f1, *f2;
	char file1[50], file2[50];
	printf("\n Enter File 1 : ");
	scanf("%s",file1);
	printf("\n Enter File 2 : ");
	scanf("%s",file2);
	f1 = fopen(file1,"r");
	f2 = fopen(file2,"w+");

	char c = fgetc(f1);
	char temp[200]; int index=0;

	//Without an extra array
	fseek(f1,-1,SEEK_END);
	long n = ftell(f1)+1;
	while(n){
		c = fgetc(f1);
		fseek(f1,-2,SEEK_CUR);
		printf("%c",c);
		n--;
	}

	/*while(c!=EOF){
		temp[index++]=c;
		//printf("%c",c);
		c = fgetc(f1);
	}
	while(index!=0){
		putc(temp[--index],f2);
	//	printf("%c",temp[--index]);
	}*/
	fclose(f1);
	fclose(f2);
	return 0;
}