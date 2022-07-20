#ifndef __IMAGE_DRAW_H__
#define __IMAGE_DRAW_H__
#include "image_core.h"
typedef enum
{
 IMAGE_COLOR_RED=0,
 IMAGE_COLOR_GREEN,
 IMAGE_COLOR_BLUE,
 IMAGE_COLOR_BLACK,
 IMAGE_COLOR_YELLOW
}Image_Color_Index;
void Draw_Image_Point(Image* InputImage,int x,int y,Image_Color_Index _color_index);
void Draw_Image_Cross(Image* InputImage,int x,int y,int line_width,Image_Color_Index _color_index);
void Draw_Image_Circle(Image* InputImage,int x,int y,int radius,int line_width,Image_Color_Index _color_index);
#endif