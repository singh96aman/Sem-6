__kernel void sort_vector(__global char *A, __global char *RES, __global int *c)
{
    int id = get_global_id(0);
    int n = get_global_size(0);
    int i=0, j, pos=0;
    int len = *c;
    int index = id*len+id;
    char min = A[index];
    for(i=0; i<(n*len+n-1); i+=(len+1))
            if(A[i]<A[index])
                pos++;
            else if(A[i]==A[index])
            {
                int temp=i;
                for(j=index; j<(index+len); j++,temp++)
                    if(A[temp]==A[j])
                        continue;
                    else
                        break;
                if(A[temp]<A[j])    
                    pos++;
            }
    printf("\n%d %d",id,pos);
    for(i=(pos*len+pos), j=index; i<(pos*len+pos+len); i++, j++)
        RES[i]=A[j];
    RES[i]=' ';
}