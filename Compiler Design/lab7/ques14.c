#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void lexp(FILE *fp);
void aterm(FILE *fp);
void list(FILE *fp);
void lexp_seq(FILE *fp);
void lexp_seq2(FILE *fp);

/*int checkNumber(FILE *fp){
	printf("\nCheckNumber");
	char arr[] = "number";
	char arr2[100];
	int index=0;
	fseek(fp,-1,SEEK_CUR);
	char c=getc(fp);
	while(c!='r' && index<6)
	{
		arr2[index++]=c;
		c=getc(fp);
	}
	arr2[index++]=c;
	arr2[index]='\0';
	printf("\n%c",c);
	if(strcmp(arr,arr2)!=0)
		return 0;
	else
		return 1;
}*/

void lexp(FILE *fp){
	printf("\nlexp");
	list(fp);
	aterm(fp);
}

void aterm(FILE *fp){
	printf("\naterm");
	char c = getc(fp);
	if(c=='n'){
		while(c!='r')
			c=getc(fp);
	}else if(c=='i'){
		while(c!='r')
			c=getc(fp);
	}else return;
}

void list(FILE *fp){
	printf("\nlist");
	char c = getc(fp);
	if(c=='('){
		lexp_seq(fp);
		c = getc(fp);
		if(c==')')
			c=getc(fp);
		else return;
	}else
		fseek(fp, -1, SEEK_CUR);
}

void lexp_seq(FILE *fp){
	printf("\nlexp_seq");
	lexp(fp);
	lexp_seq2(fp);
}

void lexp_seq2(FILE *fp){
	printf("\nlexp_seq2");
	long cur = ftell(fp);
	lexp(fp);
	long now = ftell(fp);
	char c;
	if(cur==now)
		c=getc(fp);
}

int main(){
	FILE* ip = fopen("input4.txt", "r");
	lexp(ip);
	char c = getc(ip);
	fseek(ip, -1, SEEK_CUR);
	printf("\n%c %c",c,EOF);
	if (c == EOF || c == '$')
		printf("\nSuccesful!\n");
	else
		printf("\nError while parsing!\n");
}