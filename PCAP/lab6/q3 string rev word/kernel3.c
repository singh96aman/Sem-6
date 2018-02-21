__kernel void octal(__global char *a,__global int *c)
{
	int id = get_global_id(0);

	int len=*c;
	char temp = a[id];
	a[id] = a[len-id-2];
	a[len-id-2] = temp;
}