#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void S(FILE *);
void T(FILE *);
void T2(FILE *);

void S(FILE *fp){
	//printf("\n S");
	char c = getc(fp);
	if(c=='a')
		c=getc(fp);
	else if(c=='-'){
		c=getc(fp);
		if(c=='>')
			c=getc(fp);
		else 
			return;
	}
	else if(c=='('){
		c=getc(fp);
		T(fp);
		c=getc(fp);
		if(c==')')
			c=getc(fp);
		else
			return;
	}
	else return;
}

void T(FILE *fp){
	//printf("\n T2");
	S(fp);
	T2(fp);
}

void T2(FILE *fp){
	//printf("\n T2");
	char c = getc(fp);
	if(c==','){
		S(fp);
		T2(fp);
	}
	else
		c=getc(fp);
}

int main(){

	FILE *fp;
	fp = fopen("input1.txt","r");
	if(!fp)
		printf("\nError");

	S(fp);
	fseek(fp,-1,SEEK_CUR);
	char c = getc(fp);
	//printf("\n%c %c\n",c,EOF);

	if(c==EOF || c=='$')
		printf("\n Successful !\n");
	else
		printf("\n Error while parsing\n");

	return 0;
}