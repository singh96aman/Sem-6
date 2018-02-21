__kernel void revstring(__global char *a,__global int *c,__global char *b)
{
	int i,k=0;
	int id = get_global_id(0);
	int len=*c;
	for(i=id*len; i<((id*len)+len); i++,k++)
		b[i]=a[k];
}
