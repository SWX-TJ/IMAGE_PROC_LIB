#ifndef __IMAGE_FILTER_H__
#define __IMAGE_FILTER_H__
#include "image_core.h"
#include "image_math.h"
/*均值滤波器*/
Image* MeanFilter(Image* OriImage,int kernel_size);
/*中值滤波器*/
Image* MedianFilter(Image* OriImage,int kernel_size);
/*高斯滤波器*/
Image* GussianFilter(Image* OriImage,int kernel_size,double sigma_X,double sigma_Y);
//形态学膨胀
void dilation(Image* InputImage, int width, int height);
#endif