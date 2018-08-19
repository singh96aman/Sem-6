#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int n, done=0;
    double PI25DT = 3.141592653589793238462643;
    double mypi, h, pi, i, sum, x, a;
    int myid, numprocs, resultlen;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    if(myid == 0)
    {
        printf("Enter No Of intervals :");
        scanf("%d",&n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(n!=0)
    {
    sum = 0.0;
    h   = 1.0/n;
    for (i=myid+0.5; i<n; i+=numprocs)
    {
    	x = (1.0 / (1.0 + (i*h)*(i*h)));
        sum += x;
    }

    mypi = 4.0*h*sum;

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myid == 0)
    {
        printf("pi is approximately %.16f, Error is %.16f\n",
                pi, fabs(pi - PI25DT));
    }
    }
    MPI_Finalize();
    return 0;
}
