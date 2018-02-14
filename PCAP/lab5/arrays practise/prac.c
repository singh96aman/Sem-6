#include <stdio.h>

int main()
{
	int i,a=5;
	int *num=&a;
	printf("%d\t%d\n",num,*num);

	int n=5;
	int arr[]={1,2,3,4,5};
	printf("%d\t%d\n",arr,*arr);
	for(i=0; i<n; i++)
		{printf("%d ",arr[i]); /*arr++ not applicable*/}
	printf("\n");

	int *num2 = arr;
	printf("%d\t%d\n",num2,*num2);

	for(i=0; i<n; i++)
		{printf("%d ",*num2); num2++;}
	printf("\n");

	return 0;
}