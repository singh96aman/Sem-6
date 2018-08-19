#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char arr[][100]={	"S->a|-|(T)",
					"T->SE",
					"E->,SE|?" };

int n=3;

void First(char X){
	int i=0;
	for(i=0; i<n; i++)
		if(arr[i][0]==X){
			int j=0;
			for(j=0; arr[i][j]!='\0'; j++){
				if(arr[i][j]=='>' || arr[i][j]=='|'){
					if(arr[i][j+1]>=65 && arr[i][j+1]<=90)
						First(arr[i][j+1]);
					else
						printf(" %c ",arr[i][j+1]);
				}
			}
			break;
		}
}

void Follow(char X){
	int i=0, j=0;
	if(arr[0][0]==X)
		printf(" $ ");

	for(i=0; i<n; i++)
		for(j=0; arr[i][j]!='\0'; j++)
			if(arr[i][j]==X && j!=0){
				if(arr[i][j+1]>=65 && arr[i][j+1]<=90){
					First(arr[i][j+1]);
				}else{
					if(arr[i][j+1]=='\0')
						Follow(arr[i][0]);
					else
						printf(" %c ",arr[i][j+1]);
				}
			}
}


int main()
{
	char X;
	printf("\n Enter X :");
	scanf("%c",&X);
	//First(X);
	Follow(X);
}