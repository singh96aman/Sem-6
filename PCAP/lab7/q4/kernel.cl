__kernel void mat_mul(__global int *a, int widthA, int heightA,__global int *rowsum,__global int *colsum)
{
	int row = get_global_id(1);
	int col = get_global_id(0);

	printf("\n%d %d %d %d",row,col,rowsum[row],colsum[col]);
	
	a[row*widthA+col]=rowsum[row]+colsum[col];
}
