#include "image_engine.h"
#include "image_core.h"
//#include "image_math.h"
#include "image_io.h"
#include "image_proc.h"
//#include "image_filter.h"
#include "image_draw.h"
#include "time.h"
#include "usr_api.h"
void proc_image(int i)
{
   int c_x = -1, c_y = -1,radius =0,image_id = 0;
   unsigned char *outputimage;
   Image *test_rgb_image, *test_rgbtgray_image, *test_grayrgb_image;
  
   char filename[50] = {0};
    image_id = i+1;
   M_Memset(filename, 0, 50);
   sprintf(filename, "D:\\ARM_IMAGE_PROCESS_LIB\\build\\img\\1_ (%i).jpg", image_id);
   printf("open file %s\r\n", filename);
   Image_Read_Jpeg(filename,&test_rgb_image);

   if (test_rgb_image->image_channel == 3)
   {
    test_rgbtgray_image = Image_ConvertColor(test_rgb_image, IMAGE_TRANS_RGB2GRAY);
    Image_Convert_TArray(test_rgbtgray_image, &outputimage);
   }
   else
   {
      test_grayrgb_image = Image_ConvertColor(test_rgb_image, IMAGE_TRANS_GRAY2RGB);
      Image_Convert_TArray(test_rgb_image, &outputimage);
   }
   //  M_Memset(filename, 0, 50);
   //    sprintf(filename, "D:\\ARM_IMAGE_PROCESS_LIB\\build\\result\\test_1_(%d).jpg", (i + 1));
   //    printf("save file %s\r\n", filename);
   //    Image_Write_Jpeg(filename,  test_rgb_image);
   clock_t start = clock();
    FindEyeCenter(outputimage, test_rgb_image->image_width, test_rgb_image->image_height, 160,120,&c_x, &c_y,&radius,40,10,20);
   double stop = (double)(clock() - start) / CLOCKS_PER_SEC;
   printf("test done,time is %f\r\n", stop);
    printf("c_x->%d,c_y->%d,r->%d\r\n", c_x, c_y,radius);
   if(c_x>0&&c_y>0)
   {
if (test_rgb_image->image_channel == 3)
   {
       Draw_Image_Cross(test_rgb_image, 320, 240, 56, IMAGE_COLOR_RED);
      Draw_Image_Cross(test_rgb_image, c_x, c_y, 10, IMAGE_COLOR_GREEN);
      M_Memset(filename, 0, 50);
      sprintf(filename, "D:\\ARM_IMAGE_PROCESS_LIB\\build\\result\\res_1_(%d).jpg", (i + 1));
      printf("save file %s\r\n", filename);
      Image_Write_Jpeg(filename, test_rgb_image);
      printf("saved ok\r\n");
      Image_Destroy(&test_rgb_image);
      Image_Destroy(&test_rgbtgray_image);
      M_Free(outputimage);
   }
   else
   {
      Draw_Image_Cross(test_grayrgb_image, 320, 240, 56, IMAGE_COLOR_RED);
      Draw_Image_Cross(test_grayrgb_image, c_x, c_y, 10, IMAGE_COLOR_GREEN);
      M_Memset(filename, 0, 50);
      sprintf(filename, "D:\\ARM_IMAGE_PROCESS_LIB\\build\\result\\res_1_(%d).jpg", (i + 1));
      printf("save file %s\r\n", filename);
      Image_Write_Jpeg(filename, test_grayrgb_image);
      printf("saved ok\r\n");
      Image_Destroy(&test_rgb_image);
      Image_Destroy(&test_grayrgb_image);
      M_Free(outputimage);
   }
   }
   
}
int main()
{

   for (int i = 0; i <109; i++)
   {
     printf("i_flag-->%d\r\n",i);
     proc_image(i);
   }
   // proc_image(0);
   // proc_image(15);
   //proc_image(47);
}
// //   printf("test grayImage create\r\n");
// //   Image* test_gray_image = Image_Create(3,3,34,IMAGE_FORMAT_GRAY);
// //   for(int i=0;i<test_gray_image->image_width;i++)
// //   {
// //     for(int j=0;j<test_gray_image->image_height;j++)
// //     {
// //         printf("%d ",test_gray_image->pixes.gray_value[j+i*test_gray_image->image_width]);
// //     }
// //     printf("\n");
// //   }
// //   printf("test done \r\n");
// // ////////////////////////////////////////////////
// //  printf("test rgbImage create\r\n");
// //   Image* test_rgb_image = Image_Create(3,3,34,IMAGE_FORMAT_RGB);
// //   for(int i=0;i<test_rgb_image->image_width;i++)
// //   {
// //     for(int j=0;j<test_rgb_image->image_height;j++)
// //     {
// //         printf("<%d %d %d>",test_rgb_image->pixes.rgb_value.r_value[j+i*test_rgb_image->image_width],
// //                             test_rgb_image->pixes.rgb_value.g_value[j+i*test_rgb_image->image_width],
// //                             test_rgb_image->pixes.rgb_value.b_value[j+i*test_rgb_image->image_width]);
// //     }
// //     printf("\n");
// //   }
// //   printf("test done \r\n");
// /////////////////////////////////////////////////////
// // printf("test grayImage create from array\r\n");
// // unsigned char OriArry[9]={0,1,2,3,4,5,6,7,8};
// //   Image* test_gray_image = Image_Create_FArry(OriArry,9,3,3,IMAGE_FORMAT_GRAY);
// //   for(int i=0;i<test_gray_image->image_height;i++)
// //   {
// //     for(int j=0;j<test_gray_image->image_width;j++)
// //     {
// //      printf("%d ",test_gray_image->pixes.gray_value[j+i*test_gray_image->image_width]);
// //     }
// //     printf("\n");
// //   }
// //   printf("Pixs at (1,1) is %d\n",(Image_PixsAt(test_gray_image,2,2))[0]);
// //   printf("test done \r\n");
// /////////////////////////////////////////////////////
// // printf("test rgbImage create from array\r\n");
// // unsigned char OriArry[27]={0,1,2,3,4,5,6,7,8,
// //                            9,10,11,12,13,14,15,
// //                            16,17,18,19,20,21,22,
// //                            23,24,25,26};
// //   Image* test_rgb_image = Image_Create_FArry(OriArry,27,3,3,IMAGE_FORMAT_RGB);
// //   for(int i=0;i<test_rgb_image->image_width;i++)
// //   {
// //     for(int j=0;j<test_rgb_image->image_height;j++)
// //     {
// //         printf("<%d %d %d>",test_rgb_image->pixes.rgb_value.r_value[j+i*test_rgb_image->image_width],
// //                             test_rgb_image->pixes.rgb_value.g_value[j+i*test_rgb_image->image_width],
// //                             test_rgb_image->pixes.rgb_value.b_value[j+i*test_rgb_image->image_width]);
// //     }
// //     printf("\n");
// //   }
// //   printf("test done \r\n");
// //   ////////////////////////////////////////////////
// //  printf("test rgbImagetogray create\r\n");
// //   Image* test_rgb_image = Image_Create(3,3,1,IMAGE_FORMAT_RGB);
// //   for(int i=0;i<test_rgb_image->image_width;i++)
// //   {
// //     for(int j=0;j<test_rgb_image->image_height;j++)
// //     {
// //         test_rgb_image->pixes.rgb_value.r_value[j+i*test_rgb_image->image_width] = i;
// //         test_rgb_image->pixes.rgb_value.g_value[j+i*test_rgb_image->image_width] = j;
// //         test_rgb_image->pixes.rgb_value.b_value[j+i*test_rgb_image->image_width] = i+j;
// //         printf("<%d %d %d>",test_rgb_image->pixes.rgb_value.r_value[j+i*test_rgb_image->image_width],
// //                             test_rgb_image->pixes.rgb_value.g_value[j+i*test_rgb_image->image_width],
// //                             test_rgb_image->pixes.rgb_value.b_value[j+i*test_rgb_image->image_width]);
// //     }
// //     printf("\n");
// //   }
// //   Image* test_rgbtgray_image = Image_ConvertColor(test_rgb_image,IMAGE_TRANS_RGB2GRAY);
// //     for(int i=0;i<test_rgbtgray_image->image_width;i++)
// //   {
// //     for(int j=0;j<test_rgbtgray_image->image_height;j++)
// //     {
// //         printf("%d ",test_rgbtgray_image->pixes.gray_value[j+i*test_rgbtgray_image->image_width]);
// //     }
// //     printf("\n");
// //   }
// //   printf("test done \r\n");
// //   printf("test Matrix2d operate\r\n");
// //   double temp1[6]={0.0,1.0,2.0,3.0,4.0,5.0};
// //    M_Matrix2D* new_matrix_1 = Matrix2D_Create_FArry(temp1,6,3,2);
// //    printf("new_matrix_1\r\n");
// //   Matrix2D_Printf(new_matrix_1);
// //  M_Matrix2D* new_matrix_3= Matrix2D_Create_FArry(temp1,6,3,2);
// //   printf("new_matrix_3\r\n");
// //   Matrix2D_Printf(new_matrix_3);
// //   M_Matrix2D* new_matrix_result =  Matrix2DCrossProduct(new_matrix_1,new_matrix_3);
// //   printf("new_matrix_result\r\n");
// //   if(new_matrix_result!=NULL)
// //     Matrix2D_Printf(new_matrix_result);
// //   else
// //   {
// //     printf("shape is not right\r\n");
// //   }
// //   Matrix2D_Destroy(&new_matrix_1);
// //   Matrix2D_Destroy(&new_matrix_3);
// //   Matrix2D_Destroy(&new_matrix_result);
// //   printf("test done");
//     printf("test start\r\n");

//     //read_jpeg(filename, &data, &width, &height);

//     Image* test_rgb_image =Image_Read_Jpeg("test.jpg");// Image_Create_FArry(data,width*height*3,width,height,IMAGE_FORMAT_RGB);
//     Image* test_rgbtgray_image = Image_ConvertColor(test_rgb_image,IMAGE_TRANS_RGB2GRAY);
//     clock_t start = clock();
//     Image* resize_image = Image_Resize(test_rgbtgray_image,640,480,0,0,IMAGE_RESIZE_NEAREST);
//     Image* filter_image = MeanFilter(resize_image,3);
//     double stop = (double)(clock() - start) / CLOCKS_PER_SEC;
//    // int procevalue = Image_Threshold(resize_image,100,255,IMAGE_THREAD_OSTU);

//     //printf("threshold value %d \r\n",procevalue);

//     // unsigned char OriArry[27]={0,1,2,3,4,5,6,7,8,
//     //                        9,10,11,12,13,14,15,
//     //                        16,17,18,19,20,21,22,
//     //                        23,24,25,26};
//     //Image* test_rgb_images = Image_Create_FArry(OriArry,27,1,9,IMAGE_FORMAT_RGB);

//       Image_Write_Jpeg("resize.jpg",filter_image);

//      printf("test done,time is %f\r\n",stop);

// }
