#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr;
	char filename[50];
	int count=3;
	while(count){
		printf("\n Enter filename : ");
		scanf("%s",filename);
		fptr = fopen(filename,"r");
		if(fptr==NULL)
		{
			count--;
			printf("\n Invalid File! Chances left %d",count);
		}else{
			printf("\n Valid file !");
			break;
		}
	}
	return 0;
}