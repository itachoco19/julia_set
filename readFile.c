#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char filename[] = "result.dat";
    FILE* fp = fopen(filename, "rb");
    int width, height;
    double* recode;
    if(fp == NULL)
    {
        fprintf(stderr, "Can't open file\n");
        return 1;
    }
    fread(&width, sizeof(width), 1, fp);
    printf("%d\n", width);
    fread(&height, sizeof(height), 1, fp);
    printf("%d\n", height);
    recode = malloc(sizeof(recode[0]) * height * width);
    fread(recode, sizeof(double), height * width, fp);
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0 ; j < width; ++j)
        {
            printf("%lf ", recode[j + i * width]);
        }
        printf("\n");
    }
    free(recode);
    fclose(fp);
    return 0;
}