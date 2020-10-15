#include <stdio.h>
#include <stdlib.h>
#include "julia.h"

int main(int argc, char** argv)
{
    double start_real = -1.0, start_image = -1.0, end_real = 1.0, end_image = 1.0, interval = 0.01;
    char* julia_set = NULL;
    int real_count = ((int)end_real - (int)start_real) / 2;
    int image_count = ((int)end_image - (int)start_image) / 2;
    julia_set = (char*)malloc((real_count * image_count) + 1);

    return 0;
}