__kernel void mat_mul(__global int *a, int widthA, int heightA, __global int *b)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	int index = row*widthA+col;
	if(index%2==0){
		int i, start=row*widthA;
		int sum=0;
		for(i=start; i<(start+widthA); i++)
			sum+=a[i];
		b[index]=sum;
		//printf("\n%d %d %d %d",row,col,start,sum);
	}
	else{
		int i, start=col;
		int sum=0, j=0;
		for(i=start; j<widthA; i+=widthA, j++)
			sum+=a[i];
		b[index]=sum;
		//printf("\n%d %d %d %d",row,col,start,sum);
	}
}