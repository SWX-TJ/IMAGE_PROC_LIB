#include "image_draw.h"
void Draw_Image_Point(Image* InputImage,int x,int y,Image_Color_Index _color_index)
{
    switch (_color_index)
    {
    case IMAGE_COLOR_RED:
    InputImage->pixes.rgb_value.r_value[y*InputImage->image_width+x] = 255;
    InputImage->pixes.rgb_value.g_value[y*InputImage->image_width+x] = 0;
    InputImage->pixes.rgb_value.b_value[y*InputImage->image_width+x] = 0;
    break;
    case IMAGE_COLOR_GREEN:
    InputImage->pixes.rgb_value.r_value[y*InputImage->image_width+x] = 0;
    InputImage->pixes.rgb_value.g_value[y*InputImage->image_width+x] = 255;
    InputImage->pixes.rgb_value.b_value[y*InputImage->image_width+x] = 0;
    break;
    case IMAGE_COLOR_BLUE:
        InputImage->pixes.rgb_value.r_value[y*InputImage->image_width+x] = 0;
    InputImage->pixes.rgb_value.g_value[y*InputImage->image_width+x] = 0;
    InputImage->pixes.rgb_value.b_value[y*InputImage->image_width+x] = 255;
    break;
    case IMAGE_COLOR_BLACK:
    break;
    case IMAGE_COLOR_YELLOW:
    break;
    default:
        break;
    }
}

void Draw_Image_Cross(Image* InputImage,int x,int y,int line_width,Image_Color_Index _color_index)
{
    int i = 0;
    for(;i<line_width;i++)
    {
       Draw_Image_Point(InputImage,x-i,y,_color_index);
       Draw_Image_Point(InputImage,x+i,y,_color_index);
       Draw_Image_Point(InputImage,x,y-i,_color_index);
       Draw_Image_Point(InputImage,x,y+i,_color_index);
    }
}


void Draw_Image_Circle(Image* InputImage,int x,int y,int radius,int line_width,Image_Color_Index _color_index)
{
    
}