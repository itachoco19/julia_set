#include <stdio.h>
#include <stdlib.h>
#include "mpi/mpi.h"
#include "julia.h"

int main(int argc, char** argv)
{
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    double start, time;
    start = MPI_Wtime();
    make_julia_set(width, height, -0.8, 0.15);
    time = MPI_Wtime() - start;
    printf("time : %lfsec.\n", time);
    return 0;
}
