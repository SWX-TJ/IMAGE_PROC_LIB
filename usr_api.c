#include "usr_api.h"
//参数说明
//arg1:图像缓存区图像指针
//arg2:图像宽
//arg3:图像长
//arg4:中心点结果x坐标
//arg5:中心点结果y坐标
//arg6:圆半径
//arg7:模糊阈值参数
// int maxvalue = 0;
//     int area_flag;
// 	int temp_x,temp_y = 0;
//char filename[50] = {0};
void FindEyeCenter(unsigned char*InputImage,int image_width,int image_height,int resize_img_widht,int resize_img_height,int *center_x,int *center_y,int *radius,int blur_threshold_value,int min_radius,int max_radius)
{
  //变量定义
  Image *test_rgb_image; //转换后的输入图像
  Image *resize_image;
  Image *Edge_Image; //提取了轮廓后的图像
	E_Circle *m_cirle;
	int scale = image_width/resize_img_widht;
  // int i=0;
  //1.加载图像
  test_rgb_image = Image_Create_FArry(InputImage, image_width * image_height, image_width, image_height, IMAGE_FORMAT_GRAY);
  resize_image = Image_Resize(test_rgb_image, resize_img_widht, resize_img_height, 0, 0, IMAGE_RESIZE_NEAREST);
  Edge_Image = Image_Create(resize_image->image_width, resize_image->image_height, 0, IMAGE_FORMAT_GRAY);
  m_cirle =E_FastDetectAttentionPoint(resize_image,Edge_Image,scale,min_radius,max_radius);
  // M_Memset(filename, 0, 50);
  //     sprintf(filename, "D:\\ARM_IMAGE_PROCESS_LIB\\build\\img\\resize_1_(%d)_(%d).jpg", img_id,0);
  //     printf("save file %s\r\n", filename);
  //     Image_Write_Jpeg(filename, Edge_Image);
 //E_FastCornerDetectionByNineArea(resize_image,Edge_Image,blur_threshold_value,scale,min_radius,max_radius);//E_TestNewCornerDection(resize_image,Edge_Image,10,scale);//E_FastCornerDetection(resize_image,Edge_Image,blur_threshold_value,scale);
    
  *center_x = m_cirle->x * scale;
  *center_y = m_cirle->y * scale;
	*radius =m_cirle->radius*scale;
  Image_Destroy(&test_rgb_image);
  Image_Destroy(&resize_image);
  Image_Destroy(&Edge_Image);
	M_Free(m_cirle);
}


