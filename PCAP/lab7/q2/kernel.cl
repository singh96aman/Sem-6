__kernel void mat_mul(__global int *a, int widthA, int heightA)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	if(row!=0 && row!=(widthA-1) && col!=0 && col!=(heightA-1)){
		int temp = a[row*widthA+col];
		int i, j, arr[100], index=0;
		while(temp!=0){
			arr[index++]=temp%2;
			temp/=2;
		}
		for(i=0; i<index; i++)
			if(arr[i]==1)
				arr[i]=0;
			else
				arr[i]=1;

		int sum=0, mul=1;
		for(i=index-1; i>=0; i--){
			sum+=arr[i]*mul;
			mul*=10;
		}
		a[row*widthA+col]=sum;
	}
}