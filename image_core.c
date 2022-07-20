#include "image_core.h"
/*初始常值图像创建*/
Image* Image_Create(   const unsigned int image_width,
		               const unsigned int image_height,
					   const unsigned char static_padd_value,
					   const  Image_Format image_format)
    {
       Image* new_image = (Image*)M_Malloc(sizeof(Image));
       unsigned int image_size = image_width*image_height;
       switch (image_format)
       {
        case IMAGE_FORMAT_GRAY:
           new_image->pixes.gray_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
           new_image->image_width = image_width;
           new_image->image_height = image_height;
           new_image->image_channel = 1;
           new_image->image_size = image_size;
           new_image->image_format = IMAGE_FORMAT_GRAY;
           M_Memset(new_image->pixes.gray_value,static_padd_value,image_size*sizeof(unsigned char));
           break;
        case IMAGE_FORMAT_RGB:
            new_image->pixes.rgb_value.r_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.g_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.b_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->image_width = image_width;
            new_image->image_height = image_height;
            new_image->image_channel = 3;
            new_image->image_size = image_size*3;
            new_image->image_format = IMAGE_FORMAT_RGB;
            M_Memset(new_image->pixes.rgb_value.r_value,static_padd_value,image_size*sizeof(unsigned char));
            M_Memset(new_image->pixes.rgb_value.g_value,static_padd_value,image_size*sizeof(unsigned char));
            M_Memset(new_image->pixes.rgb_value.b_value,static_padd_value,image_size*sizeof(unsigned char));
           break;
       default:
           return NULL;
           break;
       }
       return new_image;
    }
/*从一维数组创建图像*/
Image* Image_Create_FArry( unsigned char* OriArray,
                           const int ArraySize,
                           const unsigned int image_width,
                           const unsigned int image_height,
                            Image_Format image_format)
    {
        Image* new_image = (Image*)M_Malloc(sizeof(Image));
        int i=0,j=0;
        unsigned int image_size = image_width*image_height;
        int step_flag = 0;
       switch (image_format)
       {
       case IMAGE_FORMAT_GRAY:
           if(image_height*image_width!=ArraySize)
           {
            return NULL;
           }
           new_image->pixes.gray_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
           new_image->image_width = image_width;
           new_image->image_height = image_height;
           new_image->image_channel = 1;
           new_image->image_size = image_size;
           new_image->image_format = image_format;
		   new_image->pixes.gray_value=OriArray;
           //M_Memcpy(new_image->pixes.gray_value,OriArray,ArraySize);
           break;
       case IMAGE_FORMAT_RGB:
          if(image_height*image_width*3!=ArraySize)
           {
            return NULL;
           }
            new_image->pixes.rgb_value.r_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.g_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.b_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->image_width = image_width;
            new_image->image_height = image_height;
            new_image->image_channel = 3;
            new_image->image_size = image_size*3;
            new_image->image_format = image_format;
            if(image_height<image_width)
            {
             for(i=0;i<image_height;i++)
                {
                    step_flag =0;
                    for(j=0;j<image_width;j++)
                        {
                            new_image->pixes.rgb_value.r_value[j+i*new_image->image_width] = OriArray[step_flag+i*new_image->image_width*3];
                            new_image->pixes.rgb_value.g_value[j+i*new_image->image_width] = OriArray[step_flag+1+i*new_image->image_width*3];
                            new_image->pixes.rgb_value.b_value[j+i*new_image->image_width] = OriArray[step_flag+2+i*new_image->image_width*3];
                            step_flag+=3;
                        }
                }
            }
            else
            {
              for(i=0;i<image_width;i++)
                {
                    step_flag =0;
                    for(j=0;j<image_height;j++)
                        {
                            new_image->pixes.rgb_value.r_value[j+i*new_image->image_height] = OriArray[step_flag+i*new_image->image_height*3];
                            new_image->pixes.rgb_value.g_value[j+i*new_image->image_height] = OriArray[step_flag+1+i*new_image->image_height*3];
                            new_image->pixes.rgb_value.b_value[j+i*new_image->image_height] = OriArray[step_flag+2+i*new_image->image_height*3];
                            step_flag+=3;
                        }
                }
            }
           break;
       default:
            return NULL;
           break;
       }
       return new_image;
    }
M_ErrMsg Image_Convert_TArray(const Image* OriImage,unsigned char **destArray)
    {
        int i=0,j=0;
        if(OriImage==NULL)
        {
            return M_ERR_PTRNULL;
        }
       // printf("Ori image image_size:%d",OriImage->image_size);
        (*destArray) =(unsigned char*)M_Malloc(OriImage->image_size*sizeof(unsigned char));
        switch (OriImage->image_channel)
        {
        case 1:
           M_Memcpy((*destArray),OriImage->pixes.gray_value,OriImage->image_size);

            break;
        case 3:
            if(OriImage->image_height<OriImage->image_width)
            {
                for(i=0;i<OriImage->image_height;i++)
                    {
                    int step_flag = 0;
                    int row_size=  i*OriImage->image_width;
                    int row_channel_size = i*OriImage->image_width*3;
                    for(j=0;j<OriImage->image_width;j++)
                        {
                            (*destArray)[step_flag+row_channel_size]=OriImage->pixes.rgb_value.r_value[j+row_size];
                            (*destArray)[step_flag+1+row_channel_size]=OriImage->pixes.rgb_value.g_value[j+row_size];
                            (*destArray)[step_flag+2+row_channel_size]=OriImage->pixes.rgb_value.b_value[j+row_size];
                            step_flag+=3;
                        }
                }
            }
            else
            {
                 for(i=0;i<OriImage->image_width;i++)
                    {
                    int step_flag = 0;
                     int height_size=  i*OriImage->image_height;
                    int  height_channel_size = i*OriImage->image_height*3;
                    for(j=0;j<OriImage->image_height;j++)
                        {
                            (*destArray)[step_flag+height_channel_size]=OriImage->pixes.rgb_value.r_value[j+height_size];
                            (*destArray)[step_flag+1+height_channel_size]=OriImage->pixes.rgb_value.g_value[j+height_size];
                            (*destArray)[step_flag+2+height_channel_size]=OriImage->pixes.rgb_value.b_value[j+height_size];
                            step_flag+=3;
                        }
                }
            }
            break;
        default:
            break;
        }
        return M_ERR_None;
    }
/*从另一个图像中深拷贝*/
Image* Image_Create_FImage(const Image* OriImage)
    {
     int i=0,j=0;
     Image* new_image = (Image*)M_Malloc(sizeof(Image));
     int image_size = OriImage->image_height*OriImage->image_width;
    switch (OriImage->image_channel)
    {
    case 1:
        new_image->pixes.gray_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
        new_image->image_width = OriImage->image_width;
        new_image->image_height = OriImage->image_height;
        new_image->image_channel = 1;
        new_image->image_size = image_size;
         new_image->image_format = IMAGE_FORMAT_GRAY;
        for(i=0;i<OriImage->image_height;i++)
        {
            for(j=0;j<OriImage->image_width;j++)
            {
                new_image->pixes.gray_value[j+i*OriImage->image_width] = OriImage->pixes.gray_value[j+i*OriImage->image_width];
            }
        }
        break;
    case 3:
            new_image->pixes.rgb_value.r_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.g_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.b_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->image_width = OriImage->image_width;
            new_image->image_height = OriImage->image_height;
            new_image->image_channel = 3;
            new_image->image_size = image_size*3;
             new_image->image_format = IMAGE_FORMAT_RGB;
             for(i=0;i<OriImage->image_height;i++)
                {
                    for(j=0;j<OriImage->image_width;j++)
                        {
                            new_image->pixes.rgb_value.r_value[j+i*new_image->image_width] = OriImage->pixes.rgb_value.r_value[j+i*new_image->image_width];
                            new_image->pixes.rgb_value.g_value[j+i*new_image->image_width] = OriImage->pixes.rgb_value.g_value[j+i*new_image->image_width];
                            new_image->pixes.rgb_value.b_value[j+i*new_image->image_width] = OriImage->pixes.rgb_value.b_value[j+i*new_image->image_width];
                        }
                }
    break;
    default:
      return NULL;
        break;
    }
    return new_image;
    }
/*图像释放*/
bool  Image_Destroy(Image** OriImage)
{
    if((*OriImage)==NULL)
    {
        return false;
    }
    switch ((*OriImage)->image_channel)
    {
    case 1:
        M_Free((*OriImage)->pixes.gray_value);
        M_Free((*OriImage));
        (*OriImage) = NULL;
        break;
    case 3:
        M_Free((*OriImage)->pixes.rgb_value.r_value);
        M_Free((*OriImage)->pixes.rgb_value.g_value);
        M_Free((*OriImage)->pixes.rgb_value.b_value);
        M_Free((*OriImage));
        (*OriImage) = NULL;
    break;
    default:
        break;
    }
    return true;
}
bool Image_TraversalAllPixs(const Image* OriImage,void(*func)(unsigned char*))
    {
     unsigned char* pixs;
     int i=0,j=0;
    switch (OriImage->image_channel)
    {
    case 1:
           pixs = (unsigned char*)M_Malloc(sizeof(unsigned char));
           for(i=0;i<OriImage->image_height;i++)
            {
             for(j=0;j<OriImage->image_width;j++)
            {
                pixs[0] = OriImage->pixes.gray_value[j+i*OriImage->image_width];
                func(pixs);
            }
            }
        break;
    case 3:
         pixs = (unsigned char*)M_Malloc(3*sizeof(unsigned char));
         for(i=0;i<OriImage->image_height;i++)
            {
                for(j=0;j<OriImage->image_width;j++)
                {
                    pixs[0]=  OriImage->pixes.rgb_value.r_value[j+i*OriImage->image_width];
                    pixs[1]=  OriImage->pixes.rgb_value.g_value[j+i*OriImage->image_width];
                    pixs[2]=  OriImage->pixes.rgb_value.b_value[j+i*OriImage->image_width];
                    func(pixs);
                }
            }
        break;
    default:
        break;
    }
        free(pixs);
         return true;
    }
/*图像像素点查找*/
unsigned char* Image_PixsAt(const Image* OriImage,const unsigned int x,const unsigned int y)
    {
    unsigned char* pixs;
    if(x<0||x>OriImage->image_width-1||y<0||y>OriImage->image_height-1)
    {
        return NULL;
    }
    switch (OriImage->image_channel)
    {
    case 1:
        pixs = (unsigned char*)M_Malloc(sizeof(unsigned char));
        pixs[0] = OriImage->pixes.gray_value[y*OriImage->image_width+x];
        break;
    case 3:
        pixs = (unsigned char*)M_Malloc(3*sizeof(unsigned char));
        pixs[0]= OriImage->pixes.rgb_value.r_value[y*OriImage->image_width+x];
        pixs[1]= OriImage->pixes.rgb_value.g_value[y*OriImage->image_width+x];
        pixs[2]= OriImage->pixes.rgb_value.b_value[y*OriImage->image_width+x];
        break;
    default:
        break;
    }
    return pixs;
    }
/*对应位置修改像素值*/
bool Image_PixsReplace(Image* OriImage,unsigned int x,unsigned char y,unsigned char* pixs)
    {
  if(x<0||x>OriImage->image_width-1||y<0||y>OriImage->image_height-1)
    {
        return false;
    }
    switch (OriImage->image_channel)
    {
    case 1:
        OriImage->pixes.gray_value[y*OriImage->image_width+x]=pixs[0];
        break;
    case 3:
        OriImage->pixes.rgb_value.r_value[y*OriImage->image_width+x] = pixs[0];
        OriImage->pixes.rgb_value.g_value[y*OriImage->image_width+x] = pixs[1];
        OriImage->pixes.rgb_value.b_value[y*OriImage->image_width+x] = pixs[2];
        break;
    default:
        break;
    }
    return true;
    }
/*灰度算法：Gray = (R*38 + G*75 + B*15) >> 7*/
Image* Image_ConvertColor(const Image* OriImage,Image_TranFormat image_transfomat)
    {
        int i=0,j=0;
    Image* new_image = (Image*)M_Malloc(sizeof(Image));
    int image_size = OriImage->image_height*OriImage->image_width;
    switch (image_transfomat)
    {
    case IMAGE_TRANS_RGB2GRAY:
        new_image->pixes.gray_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
        new_image->image_width = OriImage->image_width;
        new_image->image_height = OriImage->image_height;
        new_image->image_channel = 1;
        new_image->image_size = image_size;
         new_image->image_format = IMAGE_FORMAT_GRAY;
        for(i=0;i<OriImage->image_height;i++)
        {
            int width_size = i*OriImage->image_width;
            for(j=0;j<OriImage->image_width;j++)
            {
                int r_value = (OriImage->pixes.rgb_value.r_value[j+width_size]);
                int g_value = (OriImage->pixes.rgb_value.g_value[j+width_size]);
                int b_value = (OriImage->pixes.rgb_value.b_value[j+width_size]);
                new_image->pixes.gray_value[j+width_size] = (r_value*299+g_value*587+b_value*114)/1000;
            }
        }
        break;
    case IMAGE_TRANS_GRAY2RGB:
            new_image->pixes.rgb_value.r_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.g_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->pixes.rgb_value.b_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
            new_image->image_width = OriImage->image_width;
            new_image->image_height = OriImage->image_height;
            new_image->image_channel = 3;
            new_image->image_size = image_size*3;
             new_image->image_format = IMAGE_FORMAT_RGB;
            for(i=0;i<OriImage->image_height;i++)
                {
                    int width_size = i*new_image->image_width;
                    for(j=0;j<OriImage->image_width;j++)
                        {
                            new_image->pixes.rgb_value.r_value[j+width_size] = OriImage->pixes.gray_value[j+width_size];
                            new_image->pixes.rgb_value.g_value[j+width_size] = OriImage->pixes.gray_value[j+width_size];
                            new_image->pixes.rgb_value.b_value[j+width_size] = OriImage->pixes.gray_value[j+width_size];
                        }
                }
      break;
    case IMAGE_TRANS_RGB2HSI:
    break;
    case IMAGE_TRANS_HSI2RGB:
    break;
    case IMAGE_TRANS_RGB2LAB:
    break;
    case IMAGE_TRANS_LAB2RGB:
    break;
    default:
    return NULL;
        break;
    }
    return new_image;
    }

