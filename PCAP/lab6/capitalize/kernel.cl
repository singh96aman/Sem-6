__kernel void octal(__global char *a,__global char *b)
{
	int id = get_global_id(0);
	if(a[id]=='a' || a[id]=='e' || a[id]=='i' || a[id]=='o' || a[id]=='u')
		b[id]=a[id]-32;
	else
		b[id]=a[id];
}