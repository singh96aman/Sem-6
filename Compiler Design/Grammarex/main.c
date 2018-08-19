//S->a|->|(T)
//T-T,S|S

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void S();
void T();
void T_();

char *arr;
char c='s';

void S(){
	printf("\n S %c",c);
	c=*arr++;
	if(c=='a'){
		c=*arr++;
	}else if(c=='-'){
		c=*arr++;
		c=*arr++;
	}else if(c=='('){
		T();
		c=*arr++;
		if(c==')')
			c=*arr++;
	}
	if(c=='$')
		printf("\n String Accepted!");
}

void T(){
	printf("\nT %c",c);
	S();
	T_();
}

void T_(){
	printf("\nT_ %c",c);
	if(c==','){
		S();
		T_();
	}
}

int main()
{
	arr = (char*) malloc(sizeof(char)*50);
	printf("\n Enter String : ");
	scanf("%s",arr);
	S();
}