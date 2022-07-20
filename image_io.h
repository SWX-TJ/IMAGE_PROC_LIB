#ifndef __IMAGE_IO_H__
#define __IMAGE_IO_H__
#include "image_core.h"
#include "jpeglib.h"
bool Image_Read_Jpeg(char* filename,Image** OriImage);
M_ErrMsg Image_Write_Jpeg(char* filename,Image* OriImage);
#endif