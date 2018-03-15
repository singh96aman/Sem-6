__kernel void octal(__global char *a)
{
	int id = get_global_id(0);
	if(a[id]=='a' || a[id]=='e' || a[id]=='i' || a[id]=='o' || a[id]=='u')
		a[id]=a[id]-32;
	else if(a[id]>=65 && a[id]<=90 && !(a[id]=='A' || a[id]=='E' || a[id]=='I' || a[id]=='O' || a[id]=='U'))
		a[id]=a[id]+32;
}