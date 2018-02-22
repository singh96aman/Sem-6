__kernel void matrixop(__global int *a, __global int *c)
{
	int i, id = get_global_id(0);
	int n = *c;
	for(i=(id*n); i<(id*n)+n; i++)
	{
		int temp=id, mul=a[i];
		while(temp!=0){
			a[i]*=mul;
			temp--;
		}
	}
}