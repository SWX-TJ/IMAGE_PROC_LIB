#include "image_filter.h"
Image* MeanFilter(Image* OriImage,int kernel_size)
{
    Image* new_image;
    double kernel_value = 1.0/(kernel_size*kernel_size);
    switch (OriImage->image_channel)
    {
    case 1:{
       M_Matrix2D *_mask = Matrix2D_Create(kernel_size,kernel_size,kernel_value);
       M_Matrix2D* _ori = Matrix2D_Create_FImage(OriImage);
       Matrix2DConvFliter(_ori,_mask);
       new_image = Matrix2D_Trans_TImage(_ori);
       Matrix2D_Destroy(&_ori);
       Matrix2D_Destroy(&_mask);
    }
        break;
    case 3:
        {
            
        }
        break;
    default:
        break;
    }
    return new_image;
}
Image* MedianFilter(Image* OriImage,int kernel_size)
{
    Image* new_image;
      switch (OriImage->image_channel)
    {
    case 1:
        {
          
        }
        break;
    case 3:
        {
          
        }
        break;
    default:
        break;
    }
    return new_image;
}

void dilation(Image* InputImage, int width, int height)
{
    int i, j, index, sum, flag;
    //sum = height * width * sizeof(uchar);
    Image *tmpdata =Image_Create_FImage(InputImage);
    //memcpy((char*)tmpdata, (char*)data, sum);
    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width - 1;j++)
        {
            flag = 1;
            for(int m = i - 1;m < i + 2;m++)
            {
                for(int n = j - 1; n < j + 2;n++)
                {
                    //自身及领域中若有一个为255
                    //则将该点设为255
                    if(tmpdata->pixes.gray_value[i * width + j] == 0
                        || tmpdata->pixes.gray_value[m * width + n] == 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    break;
                }
            }
            if(flag == 0)
            {
                InputImage->pixes.gray_value[i * width + j] = 255;
            }
            else
            {
                InputImage->pixes.gray_value[i * width + j] = 0;
            }
        }
    }
    Image_Destroy(&tmpdata);
}