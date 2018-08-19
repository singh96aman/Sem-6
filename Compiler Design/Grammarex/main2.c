#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void E();
void E_();
void T();
void T_();
void F();

char *arr;
char c='s';

void E(){
	T();
	E_();
	if(c=='$')
		printf("\n String accepted!");
}

void E_(){
	if(c=='+'){
		T();
		E_();
	}
}

void T(){
	F();
	T_();
}

void T_(){
	if(c=='*'){
		F();
		T_();
	}
}

void F(){
	c=*arr++;
	if(c=='('){
		E();
		c=*arr++;
		if(c==')')
			c=*arr++;
		//printf("\n Lala %s",arr);
	}else if(c=='i'){
		c=*arr++;
		c=*arr++;
		//printf("\n Hello %s",arr);
	}
}

int main(){
	arr = (char*) malloc(sizeof(char)*50);
	printf("\n Enter String : ");
	scanf("%s",arr);
	E();
}