__kernel void sort_vector(__global char *A, __global char *RES)
{
	int id = get_global_id(0);
	char data = A[id];
	int n = get_global_size(0);
	int i, pos=0;
	for(i=0; i<n; i++){
		if((A[i]<data) || (A[i] == data && i<id))
			pos++;
	}
	RES[pos]=data;
}