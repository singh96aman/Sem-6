__kernel void octal(__global int *a)
{
	int id = get_global_id(0);
	int temp = a[id+2];
	a[id+2]=a[id];
	a[id]=temp;
}