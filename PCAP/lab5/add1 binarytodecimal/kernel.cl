__kernel void octal(__global int *a,__global int *b)
{
	int i = get_global_id(0);
	int temp = a[i];
	int temp2 = 0, mul=1;
	while(temp!=0){
		temp2+=mul*(temp%2);
		mul*=2;
		temp/=10;
	} 
	b[i]=temp2;
}