__kernel void octal(__global char *a,__global char *b)
{
	int id = get_global_id(0);
	int temp = a[id], temp2=0;
	printf("%d ",temp);
	while(temp!=0){
		temp2=temp2*10+temp%10;
		temp/=10;
	}

	b[id]=temp2;
	printf(" %d %c \n",temp2, b[id]);
}