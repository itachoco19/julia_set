#include <stdio.h>
#include <stdlib.h>
#include "julia.h"

int main(int argc, char** argv)
{
    double start_real = -1.0, start_image = -1.0, end_real = 1.0, end_image = 1.0, interval = 0.01;
    double c_real = 0.5, c_image = 0.1;
    char* julia_set = NULL;
    char* file_name = "dump_julia_result.bin";
    FILE* fp = NULL;
    int real_count = ((int)end_real - (int)start_real) / 2;
    int image_count = ((int)end_image - (int)start_image) / 2;
    julia_set = (char*)malloc((real_count * image_count) + 1);
    fp = fopen(file_name, "wb");
    if(fp == NULL)
    {
        fprintf(stderr, "File can not open.\n");
        return 1;
    }
    else if(julia_set == NULL)
    {
        fprintf(stderr, "Memory error\n");
        return 2;
    }
    make_julia_set(start_real, start_image, interval, real_count, image_count, julia_set, c_real, c_image);
    fwrite(julia_set, sizeof(char), real_count * image_count, fp);
    fclose(fp);
    return 0;
}