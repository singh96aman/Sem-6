#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	FILE *fp1 = fopen("input.txt","r");
	char c;
	fseek(fp1,16,SEEK_CUR);
	long n = ftell(fp1);
	c=fgetc(fp1);
	printf("\n Pointer at %ld and %c",n+1,c);
	int count=0;
	while(n!=0){
		c=fgetc(fp1);
		if(c=='\n')
			count++;
		fseek(fp1,-2,SEEK_CUR);
		n--;
		//printf("\n %c",c);
	}
	printf("\n Line no : %d",count);
}
