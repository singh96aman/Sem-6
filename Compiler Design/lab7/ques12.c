#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
void E(FILE*);
void E1(FILE*);
void T(FILE*);
void T1(FILE*);
void F(FILE*);
 
void F(FILE* ip){
	//printf("\nF");
	char c = getc(ip);
	if (c == '('){
		E(ip);
		c = getc(ip);
		if (c != ')'){
			printf("Error while parsing!\n");
			exit(0);
		}
	}else if (c == 'i'){
		c = getc(ip);
		if (c != 'd'){
			printf("Error while parsing!\n");
			exit(0);
		}
	}else{
		printf("Error while parsing!\n");
		exit(0);
	}
}
 
void T(FILE* ip){
	//printf("\nT");
	F(ip);
	T1(ip);
}
 
void E(FILE* ip){
	//printf("\nE");
	T(ip);
	E1(ip);	
}
 
void E1(FILE* ip){
	//printf("\nE1");
	char c = getc(ip);
	if (c == '+'){
		T(ip);
		E1(ip);
	}else
		fseek(ip, -1, SEEK_CUR);
}
 
void T1(FILE* ip){
	//printf("\nT1");
	char c = getc(ip);
	if (c == '*'){
		F(ip);
		T1(ip);
	}else
		fseek(ip, -1, SEEK_CUR);
}
 
int main(){
	FILE* ip = fopen("input2.txt", "r");
	E(ip);
	char c = getc(ip);
	fseek(ip, -1, SEEK_CUR);
	if (c != EOF && c == '$')
		printf("\nSuccesful!\n");
	else
		printf("\nError while parsing!\n");
}