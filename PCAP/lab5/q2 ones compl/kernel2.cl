__kernel void octal(__global int *a,__global int *b)
{
	int i=0;
	int id = get_global_id(0);
	for(i=id*8; i<(id*8)+8; i++)
		if(a[i]==0)
			b[i]=1;
		else
			b[i]=0;
}