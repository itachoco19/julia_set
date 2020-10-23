#include "julia.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CONTINUE_TIME 50

char is_divergence(double real, double image, double c_real, double c_image)
{
    double m_real = real; //実部
    double m_image = image; //虚部
    int iter = 0; //イテレータ
    for(iter = 0; iter < CONTINUE_TIME; ++iter)
    {
        //次項を実部と虚部に分けて求める
        double next_real = (m_real * m_real) - (m_image * m_image) + c_real;
        double next_image = (2.0 * m_image * m_real) + c_image;
        //もし、発散するようならば、途中で計算を打ち切る
        if((next_real * next_real + next_image * next_image) > 4.0)break;
        m_real = next_real; m_image = next_image;

    }
    return iter;
}

void make_julia_set(double real_start, double image_start, double interval,int real_count, int image_count, char* result_julia, double c_real, double c_image)
{
    double m_real = real_start, m_image = image_start;
    int real_max = real_count, image_max = image_count;
    int real_index = 0, image_index = 0;
    for(real_index = 0 ; real_index < real_max - 1; ++real_index)
    {
        for(image_index = 0; image_index < image_max; ++image_index)
        {
            result_julia[real_index + (image_index * real_max)] = (char)is_divergence(m_real + (real_index * interval), m_image + (image_index * interval), c_real, c_image);
        }
    }
    for(image_index = 0; image_index < image_max; ++image_index)
    {
        result_julia[real_max - 1 + (image_index * real_max)] = '\n';
    }
}