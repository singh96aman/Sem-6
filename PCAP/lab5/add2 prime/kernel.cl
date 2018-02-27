__kernel void octal(__global int *a,__global int *b)
{
	int i, id = get_global_id(0);
	int temp = a[id], flag=0;
	for(i=temp-1; i>=2; i--)
		if(temp%i==0)
		{flag=1; break;}
	if(flag==0)
		b[id]=temp;
	else 
		b[id]=temp*temp;
}