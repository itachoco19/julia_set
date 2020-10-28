#include "julia.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CONTINUE_TIME 50

double is_divergence(double real, double image, double c_real, double c_image)
{
    double m_real = real; //実部
    double m_image = image; //虚部
    int iter = 0; //イテレータ
    for(iter = 0; iter < CONTINUE_TIME; ++iter)
    {
        //次項を実部と虚部に分けて求める
        double next_m_real = (m_real * m_real) - (m_image * m_image) + c_real;
        double next_m_image = (2.0 * m_real * m_image + c_image);
        //もし、発散するようならば、途中で計算を打ち切る
        if((next_m_real * next_m_real + next_m_image * next_m_image) > 4.0)break;
        m_real = next_m_real; m_image = next_m_image;
    }
    return ((double)(iter)) / ((double)CONTINUE_TIME);
}

double min(int x, int y)
{
    return x > y ? x : y;
}

void make_julia_set(int width, int height, double c_real, double c_image)
{
    double x = 0.0;
    double y = 0.0;
    double* recode = malloc(sizeof(double) * width * height);
    for(int i = 0; i < width * height + 1; ++i)
    {
        double x = ((double)(i % width) * 2 - width) / (double)min(width, height);
        double y = ((double)(i / width) * 2 - height) / (double)min(width, height);
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