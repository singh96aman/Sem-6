__kernel void sort_vector(__global int *A, __global int *RES, int len)
{
    int id = get_global_id(0);
    int i, j=0, n = get_global_size(0);

    int data, temp=A[id], pos=0;

    while(j<=len){
        data = temp%10;
        temp/=10;
        j++;
    }
    
    for(i=0; i<n; i++){
        
        j=0;
        int data2, temp2=A[i];
        while(j<=len){
            data2 = temp2%10;
            temp2/=10;
            j++;
        }
        if((data2<data)  || (data2 == data && i<id))
            pos++;


    }
    RES[pos]=A[id];
}