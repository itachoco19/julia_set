#include <stdio.h>
#include <stdlib.h>
#include "mpi/mpi.h"
#include "julia.h"

int main(int argc, char** argv)
{
    int width = 0;
    int height = 0;
    if(argc < 3)
    {
        width = 640;
        height = 480;
    }
    else
    {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }
    
    double start, time;
    int id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    if(id == 0)
    {
        fprintf(stderr, "use default 640x480\n");
    }
    start = MPI_Wtime();
    //make_julia_set(width, height, -0.8, 0.15);
    make_julia_mpi(width, height, -0.8, 0.15, id);
    time = MPI_Wtime() - start;
    if(id == 0)printf("time : %lfsec.\n", time);
    MPI_Finalize();
    return 0;
}
