__kernel void revstring(__global char *a,__global char *b)
{
	int i,k=0;
	int id = get_global_id(0);
	int j=id;
	int temp = (id*(id+1))/2;
	while(id>=0){
		b[temp]=a[j];
		temp++;
		id--;
	}
}
