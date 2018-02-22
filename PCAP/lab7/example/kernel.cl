__kernel void mat_mul(__global int *a, __global int *b, __global int *c, int widthA, int widthB)
{
	int row = get_global_id(0);
	int col = get_global_id(1);
	int sum=0;
	//printf("%d %d",row,col);
	for(int i=0; i<widthA; i++)
		sum+=a[row*widthA+i]*b[i*widthB+col];
	c[row*widthB+col]=sum;
}