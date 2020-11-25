#include "julia.h"
#include <stdio.h>
#include <stdlib.h>
#include "mpi/mpi.h"

#define CONTINUE_TIME 50

double is_divergence(double real, double image, double c_real, double c_image)
{
    double m_real = real; //実部
    double m_image = image; //虚部
    int iter = 0; //イテレータ

    char finish_flag = 1;
    int result = 50;
    for(iter = 0; iter < CONTINUE_TIME; ++iter)
    {
        //次項を実部と虚部に分けて求める
        double next_m_real = (m_real * m_real) - (m_image * m_image) + c_real;
        double next_m_image = (2.0 * m_real * m_image + c_image);
        //もし、発散するようならば、途中で計算を打ち切る
        if((next_m_real * next_m_real + next_m_image * next_m_image > 4.0) && finish_flag)
        {
            finish_flag = 0;
            result = iter;
        }
        m_real = next_m_real; m_image = next_m_image;
    }
    return ((double)(result)) / ((double)CONTINUE_TIME);
}

void make_julia_set(int width, int height, double c_real, double c_image)
{
    double x = 0.0;
    double y = 0.0;
    double* recode = malloc(sizeof(double) * width * height);
    double minimam = width > height ? height : width;
    for(int i = 0; i < width * height; ++i)
    {
        double x = ((double)(i % width) * 2 - width) / minimam;
        double y = ((double)(i / width) * 2 - height) / minimam;
        recode[i] = is_divergence(x, y, c_real, c_image);
    }
    
    FILE* fp = fopen("result.dat", "wb");
    if(fp == NULL)
    {
        fprintf(stderr, "Can't open file.\n");
        return;
    }
    
    fwrite(&width, sizeof(width), 1, fp);
    fwrite(&height, sizeof(height), 1, fp);
    fwrite(recode, sizeof(recode[0]), width * height, fp);
    
    free(recode);
    fclose(fp);
}

void recode_file(char* filename, int width, int height, double* data)
{
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL)
    {
        fprintf(stderr, "Can't open file\n");
        exit(1);
    }
    fwrite(&width, sizeof(width), 1, fp);
    fwrite(&height, sizeof(height), 1, fp);
    fwrite(data, sizeof(data[0]), width * height, fp);
    fclose(fp);
}

void make_julia_mpi(int width, int height, double c_real, double c_image, int process_number)
{
    double x = 0.0;
    double y = 0.0;
    int pixel;
    int minimam = width < height ? width : height;
    int all_process = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &all_process);
    pixel = (width * height) / all_process;
    double* recieve_buf = (double*)malloc(sizeof(double) * width * height);
    double* send_buf = (double*)malloc(sizeof(double) * pixel);
    int* placement = (int*)malloc(sizeof(int) * all_process);
    int* send_count = (int*)malloc(sizeof(int) * all_process);
    for(int i = 0; i < all_process; ++i)
    {
        send_count[i] = 1;
        placement[i] = process_number * pixel;
    }
    for(int i = 0; i < pixel; ++i)
    {
        double x = (double)(2.0 * ((i + process_number * pixel) % width) - width) / (double)minimam;
        double y = (double)(2.0 * ((i + process_number * pixel) / width) - height) / (double)minimam;
        send_buf[i] = is_divergence(x, y, c_real, c_image);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(send_buf, pixel, MPI_DOUBLE, recieve_buf, pixel, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(process_number == 0)
    {
        recode_file("result.dat", width, height, recieve_buf);
    }
    free(recieve_buf);
    free(send_buf);
    free(placement);
    free(send_count);
}