#ifndef __USR_API_H__
#define __USR_API_H__
#include "image_core.h"
#include "image_proc.h"
void FindEyeCenter(unsigned char*InputImage,int image_width,int image_height,int resize_img_widht,int resize_img_height,int *center_x,int *center_y,int *radius,int blur_threshold_value,int min_radius,int max_radius);
#endif