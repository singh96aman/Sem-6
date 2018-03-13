#include <stdio.h>
#include "lexical.c"
#include <string.h>
#include <ctype.h>

void Program();
void declaration();
int data_type();
void identifier_list();
void assign_stat();
void assign_stat2();
void printError();

char *buf2;

void Program(FILE *fp1){
	buf2 = getNextToken(fp1);
	if(strcmp(buf2,"main")==0)
	{
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"(")==0){
			buf2 = getNextToken(fp1);
			if(strcmp(buf2,")")==0){
				buf2 = getNextToken(fp1);
				if(strcmp(buf2,"{")==0){
					declaration(fp1);
					assign_stat(fp1);
					buf2 = getNextToken(fp1);
					if(strcmp(buf2,"}")!=0)
						printError();
				}else 
					printError();
			}else
				printError();
		}else
			printError();
	}else
		printError();
}

void declaration(FILE *fp1){
	if(data_type(fp1))
	{
		identifier_list(fp1);
		buf2 = getNextToken(fp1);
	}
}

int data_type(FILE *fp1){
	buf2 = getNextToken(fp1);
	if(strcmp(buf2,"int")==0 || strcmp(buf2,"char")==0)
	{
		return 1;
	}
	return 0;
}

void identifier_list(FILE *fp1){
	buf2 = getNextToken(fp1);
	if(strcmp(buf2,"id")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,",")==0)
			{identifier_list(fp1);}
		else if(strcmp(buf2,";")==0)
			{declaration(fp1);}
	}
}

void assign_stat(FILE *fp1){
	if(strcmp(buf2,"id")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"=")==0){
			assign_stat2(fp1);
		}
	}
}

void assign_stat2(FILE *fp1){
	buf2 = getNextToken(fp1);
	int num = atoi(buf2);
	if(strcmp(buf2,"id")==0 || num!=0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,";")==0)
			buf2 = getNextToken(fp1);
	}else
		printError();
}


int main(){
	FILE *fp1 = fopen("input.txt","r");
	buf2="start";
	Program(fp1);
	buf2 = getNextToken(fp1);
	//printf("\nLast %s",buf2);
	if(strcmp(buf2,"end")==0)
		printf("\nAccepted\n");
	else
		printf("\n Syntax Error!");
}

void printError(){
	printf("\nSyntax Error at %s",buf);
	exit(0);
}


/*
int main2(){
	dataindex=generate();
	Program();		
	i++;
	//printf("\n%d %d",dataindex, i);
	if(dataindex==i)
		printf("\n\nAccepted");
}
*/