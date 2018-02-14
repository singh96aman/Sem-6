__kernel void octal(__global int *a,__global int *b)
{
	int id = get_global_id(0);
	//printf("\n%d\n",id);
	b[id]=a[id+2];
	b[id+2]=a[id];
}