#include <stdio.h>
#include <stdlib.h>

char *arr;
char c;

void X();
void X_();
void Y();
void P();
void Q();
void X(){
	c=*arr++;
	Y();
	if(c=='n'){
		c=*arr++;
		if(c=='n')
			c=*arr++;
		X_();
	}
	if(c=='$')
		printf("\n String accepted");
}

void X_(){
	if(c=='m'){
		c=*arr++;
		if(c=='m'){
			c=*arr++;
			X_();
		}
	}
}

void Y(){
	if(c=='m'){
		c=*arr++;
		if(c=='n'){
			c=*arr++;
			P();
		}
	}
	else if(c=='n'){
		c=*arr++;
		if(c=='n'){
			c=*arr++;
			Q();
		}
	}
}

void P(){
	if(c=='p')
		c=*arr++;
}

void Q(){
	if(c=='q')
		c=*arr++;
}

int main(){
	arr = (char*) malloc(sizeof(char)*50);
	scanf("%s",arr);
	X();
}