__kernel void rev(__global char *a, __global char *b){
	int id = get_global_id(0);
	b[id]=a[id]+1;
	printf("\nHello");
}