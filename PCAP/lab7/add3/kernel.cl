__kernel void mat_mul(__global int *a, int widthA, int heightA, __global int *b)
{
	int row = get_global_id(1);
	int col = get_global_id(0);

	int rowlim=widthA/2;
	int collim=heightA/2;

	if((row<rowlim) && (col<collim))
		b[row*widthA+col]=a[row*widthA+col]+1;
	else if((row<rowlim) && (col>=collim))
		b[row*widthA+col]=a[row*widthA+col]+2;
	else if((row>=rowlim) && (col<collim))
		b[row*widthA+col]=a[row*widthA+col]+3;
	else
		b[row*widthA+col]=a[row*widthA+col]+4;
}
