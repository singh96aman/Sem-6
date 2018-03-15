__kernel void revstring(__global char *a,__global int *l,__global char *b)
{
	int id = get_global_id(0);
	int k=0, sum=0, j=0;
	int len;
	
	for(j=0; j<id; j++)
		sum+=l[j]+1;
	len = l[j];
	for(k=0; k<len; k++)
		b[sum+len-k-1] = a[sum+k];
	
	b[sum+len]=' ';
}
