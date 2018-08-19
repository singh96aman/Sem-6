#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c='s';

void lexp(FILE *);
void aterm(FILE *);
void list(FILE *);
void lexp_seq(FILE *);
void lexp_seq_(FILE *);

void lexp(FILE *f1){
	c = fgetc(f1);
	if(c=='n'||c=='i')
		aterm(f1);
	else
		list(f1);
	c = fgetc(f1);
	if(c=='$')
		printf("\n String Accepted\n");
}

void aterm(FILE *f1){
	if(c=='n'){
		c = fgetc(f1);
	}else if(c=='i'){
		c = fgetc(f1);
	}
}

void list(FILE *f1){
	if(c=='('){
		lexp_seq(f1);
	}
}

void lexp_seq(FILE *f1){
	lexp(f1);
	lexp_seq_(f1);
}

void lexp_seq_(FILE *f1){
	if(c!=')'){
		lexp(f1);
		lexp_seq_(f1);
	}
}


int main(){
	FILE *f1;
	f1 = fopen("input.txt","r");
	lexp(f1);
}