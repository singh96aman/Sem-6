__kernel void mat_mul(__global int *A, int widthA, int heightA,__global int *B)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	printf("B[%d] = A[%d] = %d\n", col * heightA + row, row * widthA + col, A[row * widthA + col]);
	B[col * heightA + row] = A[row * widthA + col];
}

