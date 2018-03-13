#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void S(FILE *);
void A(FILE *);
void A2(FILE *);
void B(FILE *);

void S(FILE *fp){
	printf("\nS");
	char c = getc(fp);
	if(c=='a'){
		A(fp);
		c = getc(fp);
		if(c=='c'){
			B(fp);
			c = getc(fp);
			if(c=='e')
				c=getc(fp);
			else return;
		}else return;
	}else return;
}

void A(FILE *fp){
	printf("\nA");
	char c = getc(fp);
	if(c=='b')
		A2(fp);
	else return;
}

void A2(FILE *fp){
	printf("\nA2");
	char c = getc(fp);
	if(c=='b')
		A2(fp);
	else
		fseek(fp,-1,SEEK_CUR);
}

void B(FILE *fp){
	printf("\nB");
	char c=getc(fp);
	if(c=='d')
		c = getc(fp);
}
 
int main(){
	FILE* ip = fopen("input3.txt", "r");
	S(ip);
	char c = getc(ip);
	fseek(ip, -1, SEEK_CUR);
	printf("\n%c %c",c,EOF);
	if (c == EOF || c == '$')
		printf("\nSuccesful!\n");
	else
		printf("\nError while parsing!\n");
}