#ifndef __IMAGE_CORE_H__
#define __IMAGE_CORE_H__
/**图像核心模块v1.0****/
/*
Author: 沈文祥
Edit time:2020.3.21
*/
#include "image_engine.h"

typedef enum
{
	IMAGE_FORMAT_GRAY = 0,
	IMAGE_FORMAT_RGB
}Image_Format;//图像通道枚举

typedef enum
{
IMAGE_TRANS_RGB2GRAY=0,
IMAGE_TRANS_GRAY2RGB,
IMAGE_TRANS_RGB2HSI,
IMAGE_TRANS_HSI2RGB,
IMAGE_TRANS_RGB2LAB,
IMAGE_TRANS_LAB2RGB
}Image_TranFormat;//图像通道转换枚举

typedef struct 
{
	int x;
	int y;
}Image_Size;

typedef struct
{
	union
	{
		struct
		{
		unsigned char *r_value;
		unsigned char *g_value;
		unsigned char *b_value;
		}rgb_value;		
	  unsigned char *gray_value;
	}pixes;
	unsigned int image_size;
	unsigned int image_width;
	unsigned int image_height;
	unsigned int image_channel;
	Image_Format image_format;
}Image;//图像类


//初始常值图像创建
Image* Image_Create(   const unsigned int image_width,
		               const unsigned int image_height,
					   const unsigned char static_padd_value,
					   const  Image_Format image_format);
//从一维数组中创建
Image* Image_Create_FArry( unsigned char* OriArray,
                           const int ArraySize,
                           const unsigned int image_width,
                           const unsigned int image_height,
                            Image_Format image_format);
//从Image转换为1-D Array
M_ErrMsg Image_Convert_TArray(const Image* OriImage,unsigned char **destArray);
//从另一个图像复制创建
Image* Image_Create_FImage(const Image* OriImage);
//图像内存释放
bool  Image_Destroy(Image** OriImage);
//图像像素值遍历
bool Image_TraversalAllPixs(const Image* OriImage,void(*func)(unsigned char*));
//图像像素对应位置查找
unsigned char* Image_PixsAt(const Image* OriImage,const unsigned int x,const unsigned int y);
//图像像素对应位置修改
bool Image_PixsReplace(Image* OriImage,unsigned int x,unsigned char y,unsigned char* pixs);
//图像颜色通道转换
Image* Image_ConvertColor(const Image* OriImage,Image_TranFormat image_transfomat);

#endif