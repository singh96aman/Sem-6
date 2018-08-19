__kernel void mat_mul(__global int *a, int widthA, int heightA)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	int index = row*widthA+col;
	if(row==col){
		a[index]=0;
	}else if(row<col){
		int i, n, fact=1;
		n=a[index];
		for(i=n; i>=2; i--){
			fact*=i;
		}
		a[index]=fact;
	}else{
		int i, n, sum=0;
		n=a[index];
		for(i=n; i>0; i--){
			sum+=i;
		}
		a[index]=sum;
	}
}