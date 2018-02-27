__kernel void revstring(__global char *a,__global int *c,__global char *b)
{
	int j, i=0, k=0;
	int id = get_global_id(0);
	int n = get_global_size(0);
	int len=*c;
	while(n--){
		b[i*len+id]=a[id];
		i++;
	}
}
