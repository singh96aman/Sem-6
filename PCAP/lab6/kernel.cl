__kernel void octal(__global int *a,__global int *b)
{
int i = get_global_id(0);

int d=a[i];
int o=0,t=1;
    while (d != 0)
    {
        o += (d % 8) * t;
        d /= 8;
        t *= 10;
    }
b[i]=o;

}