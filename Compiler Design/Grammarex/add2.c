#include <stdio.h>
#include <stdlib.h>

char *arr;

int main()
{
	arr = (char *) malloc(sizeof(char *));
	printf("\n Enter String : ");
	scanf("%s",arr);
	
}