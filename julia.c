#include "julia.h"
#include <stdio.h>
#include <stdlib.h>

#define CONTINUE_TIME 50

int is_divergence(double real, double image, double c_real, double c_image)
{
    double m_real = real; //実部
    double m_image = image; //虚部
    int iter = 0; //イテレータ
    int result = 1; //戻り値
    for(iter = 0; iter < CONTINUE_TIME; ++iter)
    {
        //次項を実部と虚部に分けて求める
        m_real = (m_real * m_real) - (m_image * m_image) + c_real;
        m_image = (2 * m_real * m_image + c_image);
        //もし、発散するようならば、途中で計算を打ち切る
        if((m_real * m_real + m_image * m_image) > 2) result = 0;break;
    }
    return result;
}

void make_julia_set(double real_start, double image_start, double interval,int real_count, int image_count, char* result_julia, double c_real, double c_image)
{
    double m_real = real_start, m_image = image_start;
    int real_max = real_count, image_max = image_count;
    int real_index = 0, image_index = 0;
    for(real_index = 0 ; real_index < real_max; ++real_index)
    {
        for(image_index = 0; image_index < image_max; ++image_index)
        {
            result_julia[real_index + (image_index * real_max)] = is_divergence(m_real + (real_index * interval), m_image + (image_index * interval), c_real, c_image);
        }
    }
}