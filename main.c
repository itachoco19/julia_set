#include <stdio.h>
#include <stdlib.h>
#include "julia.h"

int main(int argc, char** argv)
{
    int width = 640;
    int height = 480;
    make_julia_set(width, height, -0.8, 0.1);
    return 0;
}