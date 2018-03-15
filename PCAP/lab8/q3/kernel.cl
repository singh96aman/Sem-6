__kernel void sort_vector(__global char *A, __global char *B, __global int *len)
{
	int id = get_global_id(0);

	int i, j, l, start = 0, end=0;
	for(i=0; i<id; i++)
		start+=len[i]+1;

	end=start+len[id];

	for(l=0; B[l]!='\0'; l++);

	for(i=start, j=0; i<end; i++, j++)
		if(A[i]==B[j])
			continue;
		else
			break;

	if(j==l)
		printf("\nWord found at %d position",start);

}