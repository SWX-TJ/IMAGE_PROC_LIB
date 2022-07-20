#include "image_proc.h"
int **hough;
const E_Point2D directions[8] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
const float log_10_table[255]={0 ,
0.30103 ,
0.477121 ,
0.60206 ,
0.69897 ,
0.778151 ,
0.845098 ,
0.90309 ,
0.954243 ,
1 ,
1.04139 ,
1.07918 ,
1.11394 ,
1.14613 ,
1.17609 ,
1.20412 ,
1.23045 ,
1.25527 ,
1.27875 ,
1.30103 ,
1.32222 ,
1.34242 ,
1.36173 ,
1.38021 ,
1.39794 ,
1.41497 ,
1.43136 ,
1.44716 ,
1.4624 ,
1.47712 ,
1.49136 ,
1.50515 ,
1.51851 ,
1.53148 ,
1.54407 ,
1.5563 ,
1.5682 ,
1.57978 ,
1.59106 ,
1.60206 ,
1.61278 ,
1.62325 ,
1.63347 ,
1.64345 ,
1.65321 ,
1.66276 ,
1.6721 ,
1.68124 ,
1.6902 ,
1.69897 ,
1.70757 ,
1.716 ,
1.72428 ,
1.73239 ,
1.74036 ,
1.74819 ,
1.75587 ,
1.76343 ,
1.77085 ,
1.77815 ,
1.78533 ,
1.79239 ,
1.79934 ,
1.80618 ,
1.81291 ,
1.81954 ,
1.82607 ,
1.83251 ,
1.83885 ,
1.8451 ,
1.85126 ,
1.85733 ,
1.86332 ,
1.86923 ,
1.87506 ,
1.88081 ,
1.88649 ,
1.89209 ,
1.89763 ,
1.90309 ,
1.90849 ,
1.91381 ,
1.91908 ,
1.92428 ,
1.92942 ,
1.9345 ,
1.93952 ,
1.94448 ,
1.94939 ,
1.95424 ,
1.95904 ,
1.96379 ,
1.96848 ,
1.97313 ,
1.97772 ,
1.98227 ,
1.98677 ,
1.99123 ,
1.99564 ,
2 ,
2.00432 ,
2.0086 ,
2.01284 ,
2.01703 ,
2.02119 ,
2.02531 ,
2.02938 ,
2.03342 ,
2.03743 ,
2.04139 ,
2.04532 ,
2.04922 ,
2.05308 ,
2.0569 ,
2.0607 ,
2.06446 ,
2.06819 ,
2.07188 ,
2.07555 ,
2.07918 ,
2.08279 ,
2.08636 ,
2.08991 ,
2.09342 ,
2.09691 ,
2.10037 ,
2.1038 ,
2.10721 ,
2.11059 ,
2.11394 ,
2.11727 ,
2.12057 ,
2.12385 ,
2.1271 ,
2.13033 ,
2.13354 ,
2.13672 ,
2.13988 ,
2.14301 ,
2.14613 ,
2.14922 ,
2.15229 ,
2.15534 ,
2.15836 ,
2.16137 ,
2.16435 ,
2.16732 ,
2.17026 ,
2.17319 ,
2.17609 ,
2.17898 ,
2.18184 ,
2.18469 ,
2.18752 ,
2.19033 ,
2.19312 ,
2.1959 ,
2.19866 ,
2.2014 ,
2.20412 ,
2.20683 ,
2.20952 ,
2.21219 ,
2.21484 ,
2.21748 ,
2.22011 ,
2.22272 ,
2.22531 ,
2.22789 ,
2.23045 ,
2.233 ,
2.23553 ,
2.23805 ,
2.24055 ,
2.24304 ,
2.24551 ,
2.24797 ,
2.25042 ,
2.25285 ,
2.25527 ,
2.25768 ,
2.26007 ,
2.26245 ,
2.26482 ,
2.26717 ,
2.26951 ,
2.27184 ,
2.27416 ,
2.27646 ,
2.27875 ,
2.28103 ,
2.2833 ,
2.28556 ,
2.2878 ,
2.29003 ,
2.29226 ,
2.29447 ,
2.29667 ,
2.29885 ,
2.30103 ,
2.3032 ,
2.30535 ,
2.3075 ,
2.30963 ,
2.31175 ,
2.31387 ,
2.31597 ,
2.31806 ,
2.32015 ,
2.32222 ,
2.32428 ,
2.32634 ,
2.32838 ,
2.33041 ,
2.33244 ,
2.33445 ,
2.33646 ,
2.33846 ,
2.34044 ,
2.34242 ,
2.34439 ,
2.34635 ,
2.3483 ,
2.35025 ,
2.35218 ,
2.35411 ,
2.35603 ,
2.35793 ,
2.35984 ,
2.36173 ,
2.36361 ,
2.36549 ,
2.36736 ,
2.36922 ,
2.37107 ,
2.37291 ,
2.37475 ,
2.37658 ,
2.3784 ,
2.38021 ,
2.38202 ,
2.38382 ,
2.38561 ,
2.38739 ,
2.38917 ,
2.39094 ,
2.3927 ,
2.39445 ,
2.3962 ,
2.39794 ,
2.39967 ,
2.4014 ,
2.40312 ,
2.40483 ,
2.40654};
E_Edge *Init_E_Edge_Struct(void)
{
    E_Edge *_edge = (E_Edge *)M_Malloc(sizeof(E_Edge));
    assert(_edge != NULL);
    _edge->Candidate_Point = Init_VectorPt(sizeof(E_Point2D));
    assert(_edge->Candidate_Point != NULL);
    _edge->edge_point_num = 0;
    return _edge;
}

bool insert_pt(E_Edge *arg1, E_Point2D *arg2)
{

    VectorPt_PushBack(arg1->Candidate_Point, arg2);
    arg1->edge_point_num += 1;
    return true;
}

unsigned int find_pt(E_Edge *arg1, E_Point2D *arg2)
{
    unsigned int pt_index = 0;
    return pt_index;
}

bool E_Edge_Clear(E_Edge *arg1)
{
    VectorPt_Clear(arg1->Candidate_Point);
    arg1->edge_point_num = 0;
    return true;
}

bool insert_edge(E_Edge_t *arg1, E_Edge *arg2)
{

    if (arg1->edge_num >= 100)
    {
        return false;
    }
    else
    {
        //  new_edge = arg2;
        arg1->Candidate_Edge[arg1->edge_num] = *arg2;
        arg1->edge_num += 1;
        return true;
    }
}

E_Edge_t *Init_E_Edge_t_Struct(void)
{
    E_Edge_t *_edge_t = (E_Edge_t *)M_Malloc(sizeof(E_Edge_t));
    _edge_t->edge_num = 0;
    return _edge_t;
}

int Image_Threshold(Image *Oriimage, unsigned char thresholdvalue, unsigned char MaxValue, IMAGE_THREAD_TYPE method)
{
    int threshold = 0, i = 0, j = 0;

    threshold = thresholdvalue;
    //Image* new_image = Image_Create(Oriimage->image_width,Oriimage->image_height,0,IMAGE_FORMAT_GRAY);
    switch (method)
    {
    case IMAGE_THREAD_BIN:
    {
        for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                if (Oriimage->pixes.gray_value[i * Oriimage->image_width + j] > thresholdvalue)
                {
                    // Oriimage->pixes.gray_value[(i-1) * Oriimage->image_width + j] = MaxValue;
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = MaxValue;
                    // Oriimage->pixes.gray_value[(i+1) * Oriimage->image_width + j] = MaxValue;
                    //Oriimage->pixes.gray_value[i * Oriimage->image_width + j-1] = MaxValue;
                    // Oriimage->pixes.gray_value[i * Oriimage->image_width + j+1] = MaxValue;
                }
                else
                {
                    // Oriimage->pixes.gray_value[(i-1) * Oriimage->image_width + j] = 0;
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 0;
                    //Oriimage->pixes.gray_value[(i+1) * Oriimage->image_width + j] = 0;
                    // Oriimage->pixes.gray_value[i * Oriimage->image_width + j-1] = 0;
                    //Oriimage->pixes.gray_value[i * Oriimage->image_width + j+1] = 0;
                }
            }
        }
    }
    break;
    case IMAGE_THREAD_BIN_INV:
    {
        for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                if (Oriimage->pixes.gray_value[i * Oriimage->image_width + j] < thresholdvalue)
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = MaxValue;
                }
                else
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 0;
                }
            }
        }
    }
    break;
   case IMAGE_THREAD_HIST:
    {
      float histogram[256] = {0};
      int cnt = 0,index = 0;
      for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                //Oriimage->pixes.gray_value[j + i * Oriimage->image_width] = Oriimage->pixes.gray_value[j + i * Oriimage->image_width]+50;
                histogram[Oriimage->pixes.gray_value[j + i * Oriimage->image_width]]++;
                 if(histogram[Oriimage->pixes.gray_value[j + i * Oriimage->image_width]]>cnt &&Oriimage->pixes.gray_value[j + i * Oriimage->image_width]>=0.88*255&&i<245)
                {
                    index =Oriimage->pixes.gray_value[j + i * Oriimage->image_width];
                    cnt =histogram[Oriimage->pixes.gray_value[j + i * Oriimage->image_width]];
                   // printf("threash-->%d--cnt-->%d\r\n",index,cnt);
                }

            }
        }
        // for(i=0;i<256;i++)
        // {
           
        // }
       
        for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                int grayvalue = (int)(Oriimage->pixes.gray_value[i * Oriimage->image_width + j])+20;
                if(grayvalue>=255)
                {
                    //printf("gravyvalue--->%d\r\n",grayvalue);
                    grayvalue = 255;
                }
                
                if (grayvalue>= index)
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = MaxValue;
                }
                else
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 0;
                }
            }
        }
     threshold= index;
    }
    break;
    case IMAGE_THREAD_OSTU:
    {
        float histogram[256] = {0};

        int sum0, sum1, cnt0, cnt1;
        double w0, w1, u0, u1;
        double variance = 0.0;
        double maxVariance = 0;
        for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                histogram[Oriimage->pixes.gray_value[j + i * Oriimage->image_width]]++;
            }
        }
        for (i = 1; i < 256; i++) //一次遍历每个像素
        {
            sum0 = 0;
            sum1 = 0;
            cnt0 = 0;
            cnt1 = 0;
            w0 = 0;
            w1 = 0;
            for (j = 0; j < i; j++)
            {
                cnt0 += histogram[j];
                sum0 += j * histogram[j];
            }

            u0 = (double)sum0 / cnt0;
            w0 = (double)cnt0 / Oriimage->image_size;

            for (j = i; j <= 255; j++)
            {
                cnt1 += histogram[j];
                sum1 += j * histogram[j];
            }

            u1 = (double)sum1 / cnt1;
            w1 = 1 - w0; // (double)cnt1 / size;

            variance = w0 * w1 * (u0 - u1) * (u0 - u1);
            if (variance > maxVariance)
            {
                maxVariance = variance;
                threshold = i;
            }
        }
        for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                if (Oriimage->pixes.gray_value[i * Oriimage->image_width + j] >= threshold)
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = MaxValue;

                    //Oriimage->pixes.gray_value[(i-1) * Oriimage->image_width + j] = MaxValue;
                    // Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = MaxValue;
                    //Oriimage->pixes.gray_value[(i+1) * Oriimage->image_width + j] = MaxValue;
                    // Oriimage->pixes.gray_value[i * Oriimage->image_width + j-1] = MaxValue;
                    // Oriimage->pixes.gray_value[i * Oriimage->image_width + j+1] = MaxValue;
                }
                else
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 0;
                    //   Oriimage->pixes.gray_value[(i-1) * Oriimage->image_width + j] = 0;
                    //  Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 0;
                    //  Oriimage->pixes.gray_value[(i+1) * Oriimage->image_width + j] = 0;
                    //  Oriimage->pixes.gray_value[i * Oriimage->image_width + j-1] = 0;
                    //  Oriimage->pixes.gray_value[i * Oriimage->image_width + j+1] = 0;
                }
            }
        }
    }
    break;
    case IMAGE_THREAD_LOG:
     for (i = 0; i < Oriimage->image_height; i++)
        {
            for (j = 0; j < Oriimage->image_width; j++)
            {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] =1.5*Oriimage->pixes.gray_value[i * Oriimage->image_width + j]-50;//10*log_10_table[1+Oriimage->pixes.gray_value[i * Oriimage->image_width + j]];
                if (Oriimage->pixes.gray_value[i * Oriimage->image_width + j] < 0)
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 0;
                }
                else if(Oriimage->pixes.gray_value[i * Oriimage->image_width + j] >255)
                {
                    Oriimage->pixes.gray_value[i * Oriimage->image_width + j] = 255;
                }
            }
        }
    break;
    default:
        break;
    }
    return threshold;
}
Image *Image_Resize(Image *OriImage, int target_width, int target_height, double fx, double fy, IMAGE_RESIZE_TYPE image_resize_type)
{
    int i = 0, j = 0;
    double ratio_w = (double)target_width / (double)OriImage->image_width;
    double ratio_h = (double)target_height / (double)OriImage->image_height;
    Image *new_image = Image_Create(target_width, target_height, 0, OriImage->image_format);
    switch (image_resize_type)
    {
    case IMAGE_RESIZE_NEAREST:
    {
        switch (new_image->image_format)
        {
        case IMAGE_FORMAT_GRAY:
            for (i = 0; i < new_image->image_height; i++)
            {
                for (j = 0; j < new_image->image_width; j++)
                {
                    new_image->pixes.gray_value[j + i * new_image->image_width] = OriImage->pixes.gray_value[((int)(j / ratio_w) + (int)(i / ratio_h) * OriImage->image_width)];
                }
            }
            break;
        case IMAGE_FORMAT_RGB:
            for (i = 0; i < new_image->image_height; i++)
            {
                for (j = 0; j < new_image->image_width; j++)
                {
                    new_image->pixes.rgb_value.r_value[j + i * new_image->image_width] = OriImage->pixes.rgb_value.r_value[((int)(j / ratio_w) + (int)(i / ratio_h) * OriImage->image_width)];
                    new_image->pixes.rgb_value.g_value[j + i * new_image->image_width] = OriImage->pixes.rgb_value.g_value[((int)(j / ratio_w) + (int)(i / ratio_h) * OriImage->image_width)];
                    new_image->pixes.rgb_value.b_value[j + i * new_image->image_width] = OriImage->pixes.rgb_value.b_value[((int)(j / ratio_w) + (int)(i / ratio_h) * OriImage->image_width)];
                }
            }
            break;
        default:
            break;
        }
    }
    break;
    case IMAGE_RESIZE_LINEAR:
    {
        switch (new_image->image_format)
        {
        case IMAGE_FORMAT_GRAY:
            for (i = 0; i < new_image->image_height; i++)
            {
                int width_size = i * new_image->image_width;
                for (j = 0; j < new_image->image_width; j++)
                {
                    double ori_x = (double)i / ratio_h;
                    double ori_y = (double)j / ratio_w;
                    int x_1 = (int)ori_x;
                    int y_1 = (int)ori_y;
                    int x_2 = x_1 + 1;
                    int y_2 = y_1 + 1;
                    int x_1_width_size = x_1 * OriImage->image_width;
                    int x_2_width_size = x_2 * OriImage->image_width;

                    double q_11 = OriImage->pixes.gray_value[y_1 + x_1_width_size];
                    double q_12 = OriImage->pixes.gray_value[y_2 + x_1_width_size];
                    double q_21 = OriImage->pixes.gray_value[y_1 + x_2_width_size];
                    double q_22 = OriImage->pixes.gray_value[y_2 + x_2_width_size];
                    double pixs = q_11 * (x_2 - ori_x) * (y_2 - ori_y) + q_21 * (ori_x - x_1) * (y_2 - ori_y) + q_12 * (x_2 - ori_x) * (ori_y - y_1) + q_22 * (ori_x - x_1) * (ori_y - y_1);
                    if (pixs > 255.0)
                    {
                        new_image->pixes.gray_value[j + width_size] = 255;
                    }
                    else if (pixs < 0.0)
                    {
                        new_image->pixes.gray_value[j + width_size] = 0;
                    }
                    else
                    {
                        new_image->pixes.gray_value[j + width_size] = (int)pixs;
                    }
                }
            }
            break;
        case IMAGE_FORMAT_RGB:
            for (i = 0; i < new_image->image_height; i++)
            {
                for (j = 0; j < new_image->image_width; j++)
                {
                    double ori_x = (double)i / ratio_h;
                    double ori_y = (double)j / ratio_w;
                    int x_1 = (int)ori_x;
                    int y_1 = (int)ori_y;
                    int x_2 = x_1 + 1;
                    int y_2 = y_1 + 1;
                    double q_11_r = OriImage->pixes.rgb_value.r_value[y_1 + x_1 * OriImage->image_width];
                    double q_12_r = OriImage->pixes.rgb_value.r_value[y_2 + x_1 * OriImage->image_width];
                    double q_21_r = OriImage->pixes.rgb_value.r_value[y_1 + x_2 * OriImage->image_width];
                    double q_22_r = OriImage->pixes.rgb_value.r_value[y_2 + x_2 * OriImage->image_width];

                    double q_11_g = OriImage->pixes.rgb_value.g_value[y_1 + x_1 * OriImage->image_width];
                    double q_12_g = OriImage->pixes.rgb_value.g_value[y_2 + x_1 * OriImage->image_width];
                    double q_21_g = OriImage->pixes.rgb_value.g_value[y_1 + x_2 * OriImage->image_width];
                    double q_22_g = OriImage->pixes.rgb_value.g_value[y_2 + x_2 * OriImage->image_width];

                    double q_11_b = OriImage->pixes.rgb_value.b_value[y_1 + x_1 * OriImage->image_width];
                    double q_12_b = OriImage->pixes.rgb_value.b_value[y_2 + x_1 * OriImage->image_width];
                    double q_21_b = OriImage->pixes.rgb_value.b_value[y_1 + x_2 * OriImage->image_width];
                    double q_22_b = OriImage->pixes.rgb_value.b_value[y_2 + x_2 * OriImage->image_width];

                    double pixs_r = q_11_r * (x_2 - ori_x) * (y_2 - ori_y) + q_21_r * (ori_x - x_1) * (y_2 - ori_y) + q_12_r * (x_2 - ori_x) * (ori_y - y_1) + q_22_r * (ori_x - x_1) * (ori_y - y_1);
                    double pixs_g = q_11_g * (x_2 - ori_x) * (y_2 - ori_y) + q_21_g * (ori_x - x_1) * (y_2 - ori_y) + q_12_g * (x_2 - ori_x) * (ori_y - y_1) + q_22_g * (ori_x - x_1) * (ori_y - y_1);
                    double pixs_b = q_11_b * (x_2 - ori_x) * (y_2 - ori_y) + q_21_b * (ori_x - x_1) * (y_2 - ori_y) + q_12_b * (x_2 - ori_x) * (ori_y - y_1) + q_22_b * (ori_x - x_1) * (ori_y - y_1);
                    if (pixs_r > 255.0)
                    {
                        new_image->pixes.rgb_value.r_value[j + i * new_image->image_width] = 255;
                    }
                    else if (pixs_r < 0.0)
                    {
                        new_image->pixes.rgb_value.r_value[j + i * new_image->image_width] = 0;
                    }
                    else
                    {
                        new_image->pixes.rgb_value.r_value[j + i * new_image->image_width] = (int)pixs_r;
                    }

                    if (pixs_b > 255.0)
                    {
                        new_image->pixes.rgb_value.b_value[j + i * new_image->image_width] = 255;
                    }
                    else if (pixs_b < 0.0)
                    {
                        new_image->pixes.rgb_value.b_value[j + i * new_image->image_width] = 0;
                    }
                    else
                    {
                        new_image->pixes.rgb_value.b_value[j + i * new_image->image_width] = (int)pixs_b;
                    }
                    if (pixs_g > 255.0)
                    {
                        new_image->pixes.rgb_value.g_value[j + i * new_image->image_width] = 255;
                    }
                    else if (pixs_g < 0.0)
                    {
                        new_image->pixes.rgb_value.g_value[j + i * new_image->image_width] = 0;
                    }
                    else
                    {
                        new_image->pixes.rgb_value.g_value[j + i * new_image->image_width] = (int)pixs_g;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    break;
    case IMAGE_RESIZE_AREA:
        break;
    case IMAGE_RESIZE_CUBIC:
        break;
    default:
        break;
    }
    return new_image;
}


int E_Contour_extractSimple(Image *InputImage, Image *OutputImage)
{
   int i, j;
     for (i = 1; i < InputImage->image_height - 1; i += 1)
    {
        for (j = 1; j < InputImage->image_width - 1; j += 1)
        {
            int t = InputImage->pixes.gray_value[(i - 1) * InputImage->image_width + j] + InputImage->pixes.gray_value[(i + 1) * InputImage->image_width + j] + InputImage->pixes.gray_value[i * InputImage->image_width + j - 1] + InputImage->pixes.gray_value[i * InputImage->image_width + j + 1];
            if (t > 0 && t < 4 * 255 && InputImage->pixes.gray_value[i * InputImage->image_width + j] == 255)
            {
                OutputImage->pixes.gray_value[i * InputImage->image_width + j] = 255;
            }
            else
            {
                OutputImage->pixes.gray_value[i * InputImage->image_width + j] = 0;
            }
            
        }
    }
}





int E_Contour_extract(Image *InputImage, Image *OutputImage)
{
    int i, j;
    int cacu_lu = 0, cacu_ld = 0, cacu_ru = 0, cacu_rd = 0, cacu_center = 0;
    for (i = 1; i < InputImage->image_height - 1; i += 1)
    {
        for (j = 1; j < InputImage->image_width - 1; j += 1)
        {
            int t = InputImage->pixes.gray_value[(i - 1) * InputImage->image_width + j] + InputImage->pixes.gray_value[(i + 1) * InputImage->image_width + j] + InputImage->pixes.gray_value[i * InputImage->image_width + j - 1] + InputImage->pixes.gray_value[i * InputImage->image_width + j + 1];
            if (t > 0 && t < 4 * 255 && InputImage->pixes.gray_value[i * InputImage->image_width + j] == 255)
            {
                OutputImage->pixes.gray_value[i * InputImage->image_width + j] = 255;
                if (i >= InputImage->image_height / 4 && i <= InputImage->image_height - InputImage->image_height / 4&& j >= InputImage->image_width / 4&& j <= InputImage->image_width - InputImage->image_width / 4)
                {
                    cacu_center++;
                    continue;
                }
                else if (i < InputImage->image_height / 2 && j < InputImage->image_width / 2)
                {
                    cacu_lu++;
                    continue;
                }
                else if (i > InputImage->image_height / 2 && j < InputImage->image_width / 2)
                {
                    cacu_ld++;
                    continue;
                }
                else if (i < InputImage->image_height / 2 && j > InputImage->image_width / 2)
                {
                    cacu_ru++;
                    continue;
                }
                else if (i > InputImage->image_height / 2 && j > InputImage->image_width / 2)
                {
                    cacu_rd++;
                    continue;
                }
            }
            else
            {
                OutputImage->pixes.gray_value[i * InputImage->image_width + j] = 0;
            }
        }
    }
    //printf("lu %d,ld %d,ru %d,rd %d,center %d\r\n", cacu_lu, cacu_ld, cacu_ru, cacu_rd, cacu_center);
    if (cacu_lu > cacu_ld && cacu_lu > cacu_ru && cacu_lu > cacu_rd && cacu_lu > cacu_center)
    {
        return 1;
    }
    else if (cacu_ld > cacu_lu && cacu_ld > cacu_ru && cacu_ld > cacu_rd && cacu_ld > cacu_center)
    {
        return 2;
    }
    else if (cacu_ru > cacu_lu && cacu_ru > cacu_rd && cacu_ru > cacu_ld && cacu_ru > cacu_center)
    {
        return 3;
    }
    else if (cacu_rd > cacu_lu && cacu_rd > cacu_ru && cacu_rd > cacu_ld && cacu_rd > cacu_center)
    {
        return 4;
    }
    else if (cacu_center > cacu_lu && cacu_center > cacu_ru && cacu_center > cacu_ld && cacu_center > cacu_rd)
    {
        return 5;
    }
}

E_Edge_t *E_Contour_track(Image *InputImage)
{
    int i, j, counts = 0, curr_d = 0;
    E_Edge_t *m_edge_t = Init_E_Edge_t_Struct();
    E_Point2D b_pt = {0, 0};
    E_Point2D c_pt = {0, 0};
    // 边缘跟踪
    for (i = 1; i < InputImage->image_height - 1; i++)
    {
        for (j = 1; j < InputImage->image_width - 1; j++)
        {
            b_pt.x = j;
            b_pt.y = i;
            c_pt.x = j;
            c_pt.y = i;
            // 如果当前点为前景点
            if (255 == InputImage->pixes.gray_value[c_pt.y * InputImage->image_width + c_pt.x])
            {
                E_Edge *m_edge = Init_E_Edge_Struct();
                bool tra_flag = false;
                // 存入
                insert_pt(m_edge, &c_pt);
                InputImage->pixes.gray_value[c_pt.y * InputImage->image_width + c_pt.x] = 0;
                // 进行跟踪
                while (!tra_flag)
                {
                    // 循环八次
                    for (counts = 0; counts < 8; counts++)
                    {
                        // 防止索引出界
                        if (curr_d >= 8)
                        {
                            curr_d -= 8;
                        }
                        if (curr_d < 0)
                        {
                            curr_d += 8;
                        }
                        // 当前点坐标
                        // 跟踪的过程，应该是个连续的过程，需要不停的更新搜索的root点
                        //c_pt = Point(b_pt.x + directions[curr_d].x, b_pt.y + directions[curr_d].y);
                        c_pt.x = b_pt.x + directions[curr_d].x;
                        c_pt.y = b_pt.y + directions[curr_d].y;
                        // 边界判断
                        if ((c_pt.x > 0) && (c_pt.x < InputImage->image_width - 1) &&
                            (c_pt.y > 0) && (c_pt.y < InputImage->image_width - 1))
                        {
                            // 如果存在边缘
                            if (255 == InputImage->pixes.gray_value[c_pt.y * InputImage->image_width + c_pt.x])
                            {
                                curr_d -= 2; // 更新当前方向
                                // E_Point2D d_pt = { c_pt.x,c_pt.y };
                                insert_pt(m_edge, &c_pt);
                                InputImage->pixes.gray_value[c_pt.y * InputImage->image_width + c_pt.x] = 0;
                                // 更新b_pt:跟踪的root点
                                b_pt.x = c_pt.x;
                                b_pt.y = c_pt.y;
                                break; // 跳出for循环
                            }
                        }
                        curr_d++;
                    } // end for
                    // 跟踪的终止条件：如果8邻域都不存在边缘
                    if (8 == counts)
                    {
                        // 清零
                        curr_d = 0;
                        tra_flag = true;
                        if (m_edge->edge_point_num > 20)
                        {
                            //   printf("insert_edge_num:%d\r\n",m_edge->edge_point_num);
                            if (insert_edge(m_edge_t, m_edge))
                            {
                            }
                            else
                            {
                                break;
                            }
                        }
                        break;
                    }
                } // end while
                E_Edge_Clear(m_edge);
            } // end if
        }
    }
    return m_edge_t;
}

//圆拟合
E_Circle *E_LeastSquareFittingCircle(E_Edge *edge)
{
    E_Circle *m_circle;
    int k;
    float x1 = 0;
    float x2 = 0;
    float x3 = 0;
    float y1 = 0;
    float y2 = 0;
    float y3 = 0;
    float x1y1 = 0;
    float x1y2 = 0;
    float x2y1 = 0;
    float C, D, E, G, H, a, b, c;
    m_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));

    // printf("circle_parm %d,%d\r\n",edge->Candidate_Point->total_size,edge->edge_point_num);
    for (k = 0; k < edge->edge_point_num; k++)
    {

        //x1 = x1 + VectorPt_At(edge->Candidate_Point, k)->x;
        x1 = x1 + VectorPt_At(edge->Candidate_Point, k)->x;
        //  printf("x,y:%d,%d\r\n",VectorPt_At(edge->Candidate_Point, k)->x,VectorPt_At(edge->Candidate_Point, k)->y);
        x2 = x2 + VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->x;
        x3 = x3 + VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->x;
        y1 = y1 + VectorPt_At(edge->Candidate_Point, k)->y;
        y2 = y2 + VectorPt_At(edge->Candidate_Point, k)->y * VectorPt_At(edge->Candidate_Point, k)->y;
        y3 = y3 + VectorPt_At(edge->Candidate_Point, k)->y * VectorPt_At(edge->Candidate_Point, k)->y * VectorPt_At(edge->Candidate_Point, k)->y;
        x1y1 = x1y1 + VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->y;
        x1y2 = x1y2 + VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->y * VectorPt_At(edge->Candidate_Point, k)->y;
        x2y1 = x2y1 + VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->x * VectorPt_At(edge->Candidate_Point, k)->y;
    }

    //num = temp_coordinates.size();
    C = edge->edge_point_num * x2 - x1 * x1;
    D = edge->edge_point_num * x1y1 - x1 * y1;
    E = edge->edge_point_num * x3 + edge->edge_point_num * x1y2 - x1 * (x2 + y2);
    G = edge->edge_point_num * y2 - y1 * y1;
    H = edge->edge_point_num * x2y1 + edge->edge_point_num * y3 - y1 * (x2 + y2);
    a = (H * D - E * G) / (C * G - D * D);
    b = (H * C - E * D) / (D * D - G * C);
    c = -(x2 + y2 + a * x1 + b * y1) / edge->edge_point_num;
    m_circle->x = -a / 2;                               //圆心x坐标
    m_circle->y = -b / 2;                               //圆心y坐标
    m_circle->radius = sqrt(a * a + b * b - 4 * c) / 2; //圆心半径
    // printf("circle_parm %d,%d,%d\r\n", m_circle->x*4, m_circle->y*4,m_circle->radius);
    return m_circle;
}

E_Lines *Init_E_Lines_Struct(void)
{
    E_Lines *_lines = (E_Lines *)M_Malloc(sizeof(E_Lines));
    assert(_lines != NULL);
    _lines->Candidate_Line = Init_VectorPt(sizeof(E_Point2D *));
    //VectorNew(&(arg1->Candidate_Line), sizeof(E_Point*), E_Point_free, E_Point_copy, E_Point_Compare);
    //_lines->insert_line = insert_line;
    //	_lines->find_line = find_line;
    _lines->line_num = 0;
    return _lines;
}

bool insert_line(E_Lines *arg1, E_Point2D *arg2)
{
    if (arg1->line_num >= 100)
    {
        return false;
    }
    else
    {
        VectorPt_PushBack(arg1->Candidate_Line, arg2);
        //Vectorpush_back(&(arg1->Candidate_Line), arg2);
        //arg1->Candidate_Point[arg1->edge_point_num] = *arg2;
        arg1->line_num += 1;
        return true;
    }
}
bool find_line(E_Lines *arg1, E_Point2D *arg2)
{
    return VectorPt_Search(arg1->Candidate_Line, arg2);
}

int E_HoughLines(Image *InputImage, E_Lines *m_lines, double rho, double theta, int threshold)
{
    int i, j, x, y, idx = 0;
    int rtho;
    double angle;
    int nrho = sqrt(InputImage->image_height * InputImage->image_height + InputImage->image_width * InputImage->image_width);
    E_Point2D m_pt;
    int points_size;
    E_Point2D *points = NULL;
    points_size = InputImage->image_height * InputImage->image_width * sizeof(E_Point2D);
    points = (E_Point2D *)M_Malloc(points_size);

    for (i = 0; i < InputImage->image_height; i++)
    {
        for (j = 0; j < InputImage->image_width; j++)
        {
            if (InputImage->pixes.gray_value[i * InputImage->image_width + j] == 255)
            {
                points[idx].x = j;
                points[idx].y = i;
                idx++;
            }
        }
    }

    hough = (int **)M_Malloc(nrho * sizeof(int *));
    memset(hough, 0, nrho * sizeof(int *));
    for (i = 0; i < nrho; i++)
    {
        hough[i] = (int *)M_Malloc((HOUGH_RES_SHT) * sizeof(int));
        memset(hough[i], 0, (HOUGH_RES_SHT) * sizeof(int));
    }
    for (j = 0; j < idx; j++)
    {
        x = points[j].x;
        y = points[j].y;
        //printf("x,y: %d,%d\r\n", x, y);
        if (!x && !y)
            continue;
        for (i = 0; i < HOUGH_RES_SHT; i++)
        {
            angle = i * E_PI / HOUGH_RES_SHT;
            rtho = (sin(angle) * y) + (cos(angle) * x);
            if (rtho >= 0 && rtho <= nrho)
            {
                hough[rtho][i]++;
            }
        }
    }
    for (i = 0; i < nrho; i++)
    {
        for (j = 0; j < HOUGH_RES_SHT; j++)
        {
            if (hough[i][j] > threshold)
            {
                m_pt.x = i;
                m_pt.y = j * E_PI / HOUGH_RES_SHT;
                if (find_line(m_lines, &m_pt))
                {
                    continue;
                }
                else
                {
                    insert_line(m_lines, &m_pt);
                }
            }
        }
    }
    return m_lines->line_num;
}

bool insert_circle(E_Circles *arg1, E_Point3D *arg2)
{
    if (arg1->Circle_num >= 100)
    {
        return false;
    }
    else
    {
        VectorPt3D_PushBack(arg1->Candidate_Circle, arg2);
        arg1->Circle_num += 1;
        return true;
    }
}

int E_CacuPtDistance(E_Point2D *m_pt1, E_Point2D *m_pt2)
{
    int distance = sqrt((pow((m_pt1->x - m_pt2->x), 2) + pow((m_pt1->y - m_pt2->y), 2)));
    return distance;
}

int E_SelectCircle(E_Circle *InputCircles, E_Edge *InputEdge)
{
    int i, count_match_point = 0;

    E_Point2D m_circle_center;
    m_circle_center.x = InputCircles->x;
    m_circle_center.y = InputCircles->y;
    for (i = 0; i < InputEdge->edge_point_num; i++)
    {
        if (abs(E_CacuPtDistance(VectorPt_At(InputEdge->Candidate_Point, i), &m_circle_center) - InputCircles->radius) < 5)
        {
            count_match_point++;
        }
    }
    if ((float)count_match_point / InputEdge->edge_point_num >= 0.618)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

E_Circles *Init_E_Circles_Struct(void)
{
    E_Circles *_circles = (E_Circles *)M_Malloc(sizeof(E_Circles));
    assert(_circles != NULL);
    _circles->Candidate_Circle = Init_VectorPt3D(sizeof(E_Point3D *));
    assert(_circles->Candidate_Circle != NULL);
    //VectorNew(&(arg1->Candidate_Point),sizeof(E_Point*), E_Point_free, E_Point_copy, E_Point_Compare);
    //_edge->insert_pt = insert_pt;
    //_edge->find_pt = find_pt;
    _circles->Circle_num = 0;
    return _circles;
}

int E_FindMaxValue(unsigned int *Array, int start_pos, int stop_pos)
{
    int max_cord, max_value, i;
    max_value = 0;
    for (i = start_pos; i < stop_pos; i++)
    {
        if (Array[i] >= max_value)
        {
            max_cord = i;
            max_value = Array[i];
        }
    }
    return max_cord;
}

float cos_table[180] = {
1 ,
0.999391 ,
0.997567 ,
0.994527 ,
0.990278 ,
0.984823 ,
0.97817 ,
0.970326 ,
0.961301 ,
0.951106 ,
0.939753 ,
0.927257 ,
0.913632 ,
0.898895 ,
0.883064 ,
0.866158 ,
0.848198 ,
0.829206 ,
0.809204 ,
0.788218 ,
0.766272 ,
0.743393 ,
0.71961 ,
0.694951 ,
0.669446 ,
0.643126 ,
0.616024 ,
0.588172 ,
0.559604 ,
0.530354 ,
0.50046 ,
0.469956 ,
0.43888 ,
0.40727 ,
0.375164 ,
0.342602 ,
0.309623 ,
0.276267 ,
0.242574 ,
0.208587 ,
0.174345 ,
0.139892 ,
0.105268 ,
0.0705155 ,
0.0356776 ,
0.000796327 ,
-0.034086 ,
-0.0689268 ,
-0.103684 ,
-0.138314 ,
-0.172777 ,
-0.207029 ,
-0.241029 ,
-0.274736 ,
-0.308108 ,
-0.341105 ,
-0.373688 ,
-0.405815 ,
-0.437448 ,
-0.468549 ,
-0.49908 ,
-0.529004 ,
-0.558283 ,
-0.586883 ,
-0.614769 ,
-0.641906 ,
-0.668262 ,
-0.693805 ,
-0.718503 ,
-0.742327 ,
-0.765248 ,
-0.787237 ,
-0.808267 ,
-0.828315 ,
-0.847353 ,
-0.865361 ,
-0.882315 ,
-0.898196 ,
-0.912983 ,
-0.926659 ,
-0.939207 ,
-0.950613 ,
-0.960861 ,
-0.969939 ,
-0.977837 ,
-0.984545 ,
-0.990055 ,
-0.99436 ,
-0.997454 ,
-0.999335 ,
-0.999999 ,
-0.999446 ,
-0.997676 ,
-0.994693 ,
-0.990498 ,
-0.985098 ,
-0.978499 ,
-0.97071 ,
-0.961738 ,
-0.951596 ,
-0.940296 ,
-0.927852 ,
-0.914278 ,
-0.899592 ,
-0.88381 ,
-0.866953 ,
-0.849041 ,
-0.830095 ,
-0.810139 ,
-0.789197 ,
-0.767294 ,
-0.744458 ,
-0.720715 ,
-0.696095 ,
-0.670628 ,
-0.644345 ,
-0.617278 ,
-0.589459 ,
-0.560923 ,
-0.531704 ,
-0.501838 ,
-0.471361 ,
-0.440311 ,
-0.408724 ,
-0.37664 ,
-0.344098 ,
-0.311137 ,
-0.277797 ,
-0.244119 ,
-0.210144 ,
-0.175913 ,
-0.141468 ,
-0.106851 ,
-0.0721041 ,
-0.0372692 ,
-0.00238898 ,
0.0324942 ,
0.0673378 ,
0.102099 ,
0.136737 ,
0.171208 ,
0.20547 ,
0.239483 ,
0.273204 ,
0.306592 ,
0.339608 ,
0.37221 ,
0.404359 ,
0.436016 ,
0.467142 ,
0.497699 ,
0.527651 ,
0.556961 ,
0.585593 ,
0.613512 ,
0.640684 ,
0.667077 ,
0.692657 ,
0.717395 ,
0.741259 ,
0.764221 ,
0.786253 ,
0.807329 ,
0.827421 ,
0.846507 ,
0.864562 ,
0.881565 ,
0.897495 ,
0.912332 ,
0.926059 ,
0.938659 ,
0.950117 ,
0.960418 ,
0.969551 ,
0.977503 ,
0.984265 ,
0.98983 ,
0.99419 ,
0.997339 ,
0.999275 
};

float sin_table[180]={
0 ,
0.0348818 ,
0.0697212 ,
0.104476 ,
0.139103 ,
0.173561 ,
0.207808 ,
0.241802 ,
0.275501 ,
0.308866 ,
0.341854 ,
0.374426 ,
0.406543 ,
0.438164 ,
0.469253 ,
0.49977 ,
0.529679 ,
0.558943 ,
0.587528 ,
0.615396 ,
0.642516 ,
0.668854 ,
0.694378 ,
0.719057 ,
0.742861 ,
0.76576 ,
0.787727 ,
0.808736 ,
0.82876 ,
0.847776 ,
0.86576 ,
0.88269 ,
0.898546 ,
0.913308 ,
0.926958 ,
0.939481 ,
0.950859 ,
0.961081 ,
0.970133 ,
0.978004 ,
0.984685 ,
0.990167 ,
0.994444 ,
0.997511 ,
0.999363 ,
1 ,
0.999419 ,
0.997622 ,
0.99461 ,
0.990388 ,
0.984961 ,
0.978335 ,
0.970518 ,
0.96152 ,
0.951351 ,
0.940025 ,
0.927555 ,
0.913955 ,
0.899244 ,
0.883437 ,
0.866556 ,
0.84862 ,
0.829651 ,
0.809672 ,
0.788708 ,
0.766783 ,
0.743926 ,
0.720163 ,
0.695523 ,
0.670038 ,
0.643736 ,
0.616651 ,
0.588816 ,
0.560263 ,
0.531029 ,
0.501149 ,
0.470659 ,
0.439595 ,
0.407997 ,
0.375902 ,
0.34335 ,
0.31038 ,
0.277032 ,
0.243347 ,
0.209365 ,
0.175129 ,
0.14068 ,
0.106059 ,
0.0713099 ,
0.0364735 ,
0.00159265 ,
-0.0332901 ,
-0.0681323 ,
-0.102892 ,
-0.137526 ,
-0.171992 ,
-0.20625 ,
-0.240256 ,
-0.27397 ,
-0.30735 ,
-0.340357 ,
-0.372949 ,
-0.405087 ,
-0.436732 ,
-0.467846 ,
-0.49839 ,
-0.528328 ,
-0.557622 ,
-0.586238 ,
-0.61414 ,
-0.641295 ,
-0.66767 ,
-0.693231 ,
-0.717949 ,
-0.741793 ,
-0.764735 ,
-0.786745 ,
-0.807798 ,
-0.827868 ,
-0.84693 ,
-0.864962 ,
-0.88194 ,
-0.897846 ,
-0.912658 ,
-0.92636 ,
-0.938934 ,
-0.950365 ,
-0.96064 ,
-0.969745 ,
-0.97767 ,
-0.984406 ,
-0.989943 ,
-0.994275 ,
-0.997397 ,
-0.999305 ,
-0.999997 ,
-0.999472 ,
-0.99773 ,
-0.994774 ,
-0.990607 ,
-0.985235 ,
-0.978663 ,
-0.970901 ,
-0.961956 ,
-0.951841 ,
-0.940567 ,
-0.928149 ,
-0.9146 ,
-0.899939 ,
-0.884182 ,
-0.86735 ,
-0.849461 ,
-0.830539 ,
-0.810605 ,
-0.789686 ,
-0.767805 ,
-0.744989 ,
-0.721267 ,
-0.696667 ,
-0.671219 ,
-0.644954 ,
-0.617904 ,
-0.590102 ,
-0.561582 ,
-0.532378 ,
-0.502527 ,
-0.472063 ,
-0.441025 ,
-0.409451 ,
-0.377378 ,
-0.344846 ,
-0.311894 ,
-0.278562 ,
-0.244891 ,
-0.210923 ,
-0.176697 ,
-0.142257 ,
-0.107643 ,
-0.0728984 ,
-0.038065 
};
E_Circle *E_SimpleCircleByArea(Image *edgeImage,Image *meanImage,int area_index,int scale) //,int *center_x,int *center_y
{
   E_Circle *m_circle;
    int radius = 0;
    int i = 0, j = 0, k = 0, theta = 0,width_index = 0, final_x = -1, final_y = -1,maxvalue =0,theta_max_value = 180;
    int  cnt_value = 80,theta_step = 3;//max_r = 8, min_r =7,
    int max_r = 74,min_r = 70,k_step = 2;
    int half_width = edgeImage->image_width/2;
    int half_height = edgeImage->image_height/2;
    int half_sub_width = edgeImage->image_width/4;
    int half_sub_height = edgeImage->image_height/4;
    int half_and_width = edgeImage->image_width*0.75;
    int half_and_height = edgeImage->image_height*0.75;
    if(scale==4)
		{
			max_r = 148,min_r = 140,k_step = 2;
            cnt_value = 200;
		}
		else
		{
			max_r =74,min_r = 70,k_step = 2;
            cnt_value = 80;
		}
    m_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));
    switch (area_index)
    {
    case 0:
        for (i =half_sub_height ; i < half_and_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = half_sub_width; j < half_and_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    for (k = min_r; k < max_r; k+=k_step)
                    {
                        for(theta=0;theta<theta_max_value;theta+=theta_step)
                        {
                            m_circle->x = j+k*0.1*cos_table[theta];
                            m_circle->y = i+k*0.1*sin_table[theta];
                            if(m_circle->x>=0&&m_circle->x<edgeImage->image_width&&m_circle->y>=0&&m_circle->y<=edgeImage->image_height)
                            {
                                meanImage->pixes.gray_value[m_circle->x+m_circle->y*edgeImage->image_width]+=1;
                            }
                        }
                    }
                }
            }
        }

        for (i =0 ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < edgeImage->image_width; j++)
            {
                if (meanImage->pixes.gray_value[j + width_index]>maxvalue&&meanImage->pixes.gray_value[j + width_index]<=cnt_value)
                {
                    final_x = j;
                    final_y = i;
                    maxvalue = meanImage->pixes.gray_value[j + width_index];
                }
            }
        }
        break;
    case 1:
        for (i =0 ; i < half_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < half_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    for (k = min_r; k < max_r; k+=k_step)
                    {
                        for(theta=0;theta<theta_max_value;theta+=theta_step)
                        {
                            m_circle->x = j+k*0.1*cos_table[theta];
                            m_circle->y = i+k*0.1*sin_table[theta];
                            if(m_circle->x>=0&&m_circle->x<edgeImage->image_width&&m_circle->y>=0&&m_circle->y<=edgeImage->image_height)
                            {
                                meanImage->pixes.gray_value[m_circle->x+m_circle->y*edgeImage->image_width]+=1;
                            }
                        }
                    }
                }
            }
        }

        for (i =0 ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < edgeImage->image_width; j++)
            {
                if (meanImage->pixes.gray_value[j + width_index]>maxvalue&&meanImage->pixes.gray_value[j + width_index]<=cnt_value)
                {
                    final_x = j;
                    final_y = i;
                    maxvalue = meanImage->pixes.gray_value[j + width_index];
                }
            }
        }
        break;
    case 2:
        for (i =0 ; i < half_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = half_width; j < edgeImage->image_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    for (k = min_r; k < max_r; k+=k_step)
                    {
                        for(theta=0;theta<theta_max_value;theta+=theta_step)
                        {
                            m_circle->x = j+k*0.1*cos_table[theta];
                            m_circle->y = i+k*0.1*sin_table[theta];
                            if(m_circle->x>=0&&m_circle->x<edgeImage->image_width&&m_circle->y>=0&&m_circle->y<=edgeImage->image_height)
                            {
                                meanImage->pixes.gray_value[m_circle->x+m_circle->y*edgeImage->image_width]+=1;
                            }
                        }
                    }
                }
            }
        }

        for (i =0 ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < edgeImage->image_width; j++)
            {
                if (meanImage->pixes.gray_value[j + width_index]>maxvalue&&meanImage->pixes.gray_value[j + width_index]<=cnt_value)
                {
                    final_x = j;
                    final_y = i;
                    maxvalue = meanImage->pixes.gray_value[j + width_index];
                }
            }
        }
        break;
    case 3:
        for (i =half_height ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < half_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    for (k = min_r; k < max_r; k+=k_step)
                    {
                        for(theta=0;theta<theta_max_value;theta+=theta_step)
                        {
                            m_circle->x = j+k*0.1*cos_table[theta];
                            m_circle->y = i+k*0.1*sin_table[theta];
                            if(m_circle->x>=0&&m_circle->x<edgeImage->image_width&&m_circle->y>=0&&m_circle->y<=edgeImage->image_height)
                            {
                                meanImage->pixes.gray_value[m_circle->x+m_circle->y*edgeImage->image_width]+=1;
                            }
                        }
                    }
                }
            }
        }

        for (i =0 ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < edgeImage->image_width; j++)
            {
                if (meanImage->pixes.gray_value[j + width_index]>maxvalue&&meanImage->pixes.gray_value[j + width_index]<=cnt_value)
                {
                    final_x = j;
                    final_y = i;
                    maxvalue = meanImage->pixes.gray_value[j + width_index];
                }
            }
        }
        break;
    case 4:
        for (i =half_height ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = half_width; j < edgeImage->image_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    for (k = min_r; k < max_r; k+=k_step)
                    {
                        for(theta=0;theta<theta_max_value;theta+=theta_step)
                        {
                            m_circle->x = j+k*0.1*cos_table[theta];
                            m_circle->y = i+k*0.1*sin_table[theta];
                            if(m_circle->x>=0&&m_circle->x<edgeImage->image_width&&m_circle->y>=0&&m_circle->y<=edgeImage->image_height)
                            {
                                meanImage->pixes.gray_value[m_circle->x+m_circle->y*edgeImage->image_width]+=1;
                            }
                        }
                    }
                }
            }
        }

        for (i =0 ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < edgeImage->image_width; j++)
            {

                if (meanImage->pixes.gray_value[j + width_index]>maxvalue&&meanImage->pixes.gray_value[j + width_index]<=cnt_value)
                {

                    final_x = j;
                    final_y = i;
                    maxvalue = meanImage->pixes.gray_value[j + width_index];
                }
            }
        }
        break;
    default:
        break;
    }
    m_circle->x = final_x;
    m_circle->y = final_y;
	m_circle->radius = 14;
	if(scale==8)
     m_circle->radius = 7;
    return m_circle;
}


E_Circle *E_SimpleCircleByFastCircle(Image *edgeImage,int area_index)
{
    E_Circle *m_circle;
    int radius = 0;
    int i = 0, j = 0, k = 0, theta = 0,width_index = 0, final_x = -1, final_y = -1, max_pts_nums = 300;
    int half_width = edgeImage->image_width/2;
    int half_height = edgeImage->image_height/2;
    int half_sub_width = edgeImage->image_width/4;
    int half_sub_height = edgeImage->image_height/4;
    int half_and_width = edgeImage->image_width*0.75;
    int half_and_height = edgeImage->image_height*0.75;
    int candidatePts[300][2];
    int candidatePtsNums = 0;
   
    switch (area_index)
    {
    case 0:
        for (i =half_sub_height ; i < half_and_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = half_sub_width; j < half_and_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    if(candidatePtsNums>=max_pts_nums)
                    {
                        break;
                    }
                    else
                    {
                        candidatePts[candidatePtsNums][0] = j;
                        candidatePts[candidatePtsNums][1] = i;
                        candidatePtsNums+=1;
                    }

                }
            }
        }
        m_circle = E_FastCircleDetection(candidatePts,candidatePtsNums);
        break;
    case 1:
        for (i =0 ; i < half_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < half_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    if(candidatePtsNums>=max_pts_nums)
                    {
                        break;
                    }
                    else
                    {
                        candidatePts[candidatePtsNums][0] = j;
                        candidatePts[candidatePtsNums][1] = i;
                        candidatePtsNums+=1;
                    }

                }
            }
        }
        m_circle = E_FastCircleDetection(candidatePts,candidatePtsNums);
        break;
    case 2:
        for (i =0 ; i < half_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = half_width; j < edgeImage->image_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    if(candidatePtsNums>=max_pts_nums)
                    {
                        break;
                    }
                    else
                    {
                        candidatePts[candidatePtsNums][0] = j;
                        candidatePts[candidatePtsNums][1] = i;
                        candidatePtsNums+=1;
                    }

                }
            }
        }
        m_circle = E_FastCircleDetection(candidatePts,candidatePtsNums);
        break;
    case 3:
        for (i =half_height ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = 0; j < half_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    if(candidatePtsNums>=max_pts_nums)
                    {
                        break;
                    }
                    else
                    {
                        candidatePts[candidatePtsNums][0] = j;
                        candidatePts[candidatePtsNums][1] = i;
                        candidatePtsNums+=1;
                    }

                }
            }
        }
        m_circle = E_FastCircleDetection(candidatePts,candidatePtsNums);
        break;
    case 4:
        for (i =half_height ; i < edgeImage->image_height; i++)
        {
            width_index = i * (edgeImage->image_width);
            for (j = half_width; j < edgeImage->image_width; j++)
            {
                if (edgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    if(candidatePtsNums>=max_pts_nums)
                    {
                        break;
                    }
                    else
                    {
                        candidatePts[candidatePtsNums][0] = j;
                        candidatePts[candidatePtsNums][1] = i;
                        candidatePtsNums+=1;
                    }

                }
            }
        }
        m_circle = E_FastCircleDetection(candidatePts,candidatePtsNums);
        break;
    default:
     m_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));
     m_circle->x = -1;
     m_circle->y = -1;
     m_circle->radius = 0;
        break;
    }
    return m_circle;
}


E_Circle *E_FastCircleDetection(int candidate_pts[][2],int pts_nums)
{
    E_Circle *m_circle;
    float x1 = 0;
    float x2 = 0;
    float x3 = 0;
    float y1 = 0;
    float y2 = 0;
    float y3 = 0;
    float x1y1 = 0;
    float x1y2 = 0;
    float x2y1 = 0;
    int i=0,j=0,k=0;
    float C, D, E, G, H, a, b, c;
    m_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));
    for(int i=0;i<pts_nums;i++)
    {
        x1 = x1 + candidate_pts[i][0];
        x2 = x2 + candidate_pts[i][0] *  candidate_pts[i][0];
        x3 = x3 + candidate_pts[i][0] *  candidate_pts[i][0] *  candidate_pts[i][0];
        y1 = y1 + candidate_pts[i][1];
        y2 = y2 + candidate_pts[i][1] * candidate_pts[i][1];
        y3 = y3 + candidate_pts[i][1]* candidate_pts[i][1] * candidate_pts[i][1];
        x1y1 = x1y1 + candidate_pts[i][0] * candidate_pts[i][1];
        x1y2 = x1y2 + candidate_pts[i][0] * candidate_pts[i][1] * candidate_pts[i][1];
        x2y1 = x2y1 + candidate_pts[i][0] * candidate_pts[i][0] * candidate_pts[i][1];
    }
    C = pts_nums* x2 - x1 * x1;
    D = pts_nums * x1y1 - x1 * y1;
    E = pts_nums * x3 +pts_nums * x1y2 - x1 * (x2 + y2);
    G = pts_nums * y2 - y1 * y1;
    H =pts_nums* x2y1 + pts_nums * y3 - y1 * (x2 + y2);
    a = (H * D - E * G) / (C * G - D * D);
    b = (H * C - E * D) / (D * D - G * C);
    c = -(x2 + y2 + a * x1 + b * y1) / pts_nums;
    m_circle->x = -a / 2;                               //圆心x坐标
    m_circle->y = -b / 2;                               //圆心y坐标
    m_circle->radius = sqrt(a * a + b * b - 4 * c) / 2; //圆心半径


   //m_circle = E_RANSACCircleDetection(candidate_pts,pts_nums);

    return m_circle;
}




void E_QuickSortArray(int *array, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int i = left;
    int j = right;
    int key = array[left];
    while (i < j)                        
    {
        while (i < j && key <= array[j])
        {
            j--;
        }

        array[i] = array[j];

        while (i < j && key >= array[i])
        {
            i++;
        }

        array[j] = array[i];
    }

    array[i] = key;
    E_QuickSortArray(array, left, i - 1);
    E_QuickSortArray(array, i + 1, right);
}


int  E_FastCornerDetection(Image *Oriimage,Image *OutputImage,int blur_threshold_value,int scale)
{                                                                                                                                                                                         //threshold_value：130-160之间， 
    int width_index = 0,i=0,j=0, center_value = 0,left_value = 0,right_value = 0,up_value = 0,down_value = 0,left_up_value = 0,left_down_value = 0,right_up_value = 0,right_down_value = 0,radius =3;
    int cnt = 0;
    int lu_cnt=0,ld_cnt=0,ru_cnt=0,rd_cnt=0,center_area= 0,max_cnt = 0,max_index=-1;
    int half_width = Oriimage->image_width/2;
    int half_height = Oriimage->image_height/2;
   for (i = radius; i < Oriimage->image_height-radius; i++)
    {
        for (j = radius; j < Oriimage->image_width-radius; j++)
        {
            center_value = Oriimage->pixes.gray_value[j + i * (Oriimage->image_width)];
            if(j>=radius&&i>=1&&i<=Oriimage->image_height-1)
            {
            left_value = Oriimage->pixes.gray_value[j-radius + i * (Oriimage->image_width)];
            left_up_value = Oriimage->pixes.gray_value[j-radius+1 + (i-1) * (Oriimage->image_width)];
            left_down_value = Oriimage->pixes.gray_value[j-radius+1 + (i+1) * (Oriimage->image_width)];
            }
            if(j<Oriimage->image_width-radius&&i>=1&&i<=Oriimage->image_height-1)
            {
              right_value = Oriimage->pixes.gray_value[j+radius + i * (Oriimage->image_width)];
              right_up_value = Oriimage->pixes.gray_value[j+radius-1 + (i-1) * (Oriimage->image_width)];
              right_down_value = Oriimage->pixes.gray_value[j+radius-1 + (i+1) * (Oriimage->image_width)];
            }
            if(i>=radius&&i<=Oriimage->image_height-radius)
            {
              up_value = Oriimage->pixes.gray_value[j + (i-radius) * (Oriimage->image_width)];
              down_value = Oriimage->pixes.gray_value[j + (i+radius) * (Oriimage->image_width)];
            }
            if((center_value-left_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-right_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-up_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-down_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
            if((center_value-left_up_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
              if((center_value-left_down_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
              if((center_value-right_up_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
              if((center_value-right_down_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
            if(cnt>=4)
            {
                OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 255;
                cnt = 0;
                     if(i>half_height*0.5&&i<half_height*1.5&&j>half_width*0.5&&j<half_width*1.5)
                {
                    center_area +=1;
                    if(center_area>max_cnt)
                    {
                        max_cnt = center_area;
                        max_index = 0;
                    }
                }
                 if(i>0&&i<half_height&&j>0&&j<half_width)
                {
                    lu_cnt +=1;
                     if(lu_cnt>max_cnt)
                    {
                        max_cnt = lu_cnt;
                        max_index = 1;
                    }
                }
                 if(i>0&&i<half_height&&j>half_width&&j<Oriimage->image_width)
                {
                    ru_cnt +=1;
                     if(ru_cnt>max_cnt)
                    {
                        max_cnt = ru_cnt;
                        max_index = 2;
                    }
                }
                   if(i>half_height&&i<Oriimage->image_height&&j>0&&j<half_width)
                {
                    ld_cnt +=1;
                     if(ld_cnt>max_cnt)
                    {
                        max_cnt = ld_cnt;
                        max_index = 3;
                    }
                }
                   if(i>half_height&&i<Oriimage->image_height&&j>half_width&&j<Oriimage->image_width)
                {
                    rd_cnt +=1;
                     if(rd_cnt>max_cnt)
                    {
                        max_cnt = rd_cnt;
                        max_index = 4;
                    }
                }
            }
        }
    }
    if(max_cnt>=25)
    {

    if(scale==4)
		{
	if(center_area>=25)
    {
        max_index = 0;
    }
        }
		}
        else
        {
            max_index = -1;
        }
        
		
    //printf("center-->%d,lu_cnt-->%d,ld_cnt-->%d,ru_cnt-->%d,rd_cnt-->%d,max_cnt--->%d,max_index-->%d\r\n",center_area,lu_cnt,ld_cnt,ru_cnt,rd_cnt,max_cnt,max_index);
    return max_index;
}


int E_TestNewCornerDection(Image *Oriimage,Image *OutputImage,int blur_thresholdvalue,int scale)
{
    int width_index = 0,i=0,j=0, center_value = 0,left_value = 0,right_value = 0,up_value = 0,down_value = 0,left_up_value = 0,left_down_value = 0,right_up_value = 0,right_down_value = 0,threshold_value = 0,radius =6;
    int l_c_vec_value = 0,r_c_vec_value=0,u_c_vec_value, d_c_vec_value= 0,lu_c_vec_value = 0,ld_c_vec_value = 0,ru_c_vec_value = 0,rd_c_vec_value = 0; 
    int cnt_value = 0,max_threhold_value = 0;
    int lu_cnt=0,ld_cnt=0,ru_cnt=0,rd_cnt=0,center_area= 0,max_cnt = 0,max_index=-1;
    int half_width = Oriimage->image_width/2;
    int half_height = Oriimage->image_height/2;
    //int pixesvalueArr[255]={0};
    int byvalueArray[8]={0};
    int maxsubpiexvalue = 30;
     int cnt = 0,index = 0;
     int average_value=0,average_count=0,aver_k=0;
    if(scale==4)
    {
        radius = 8;
    }
    else
    {
        radius = 3;
    }
    for (i = radius; i < Oriimage->image_height-radius; i++)
    {
        for (j = radius; j < Oriimage->image_width-radius; j++)
        {
            center_value = Oriimage->pixes.gray_value[j + i * (Oriimage->image_width)];
            if(j>=radius&&i>=1&&i<=Oriimage->image_height-1)
            {
                left_value = Oriimage->pixes.gray_value[j-radius + i * (Oriimage->image_width)];
                left_up_value = Oriimage->pixes.gray_value[j-radius+1 + (i-1) * (Oriimage->image_width)];
                left_down_value = Oriimage->pixes.gray_value[j-radius+1 + (i+1) * (Oriimage->image_width)];
            }
            if(j<Oriimage->image_width-radius&&i>=1&&i<=Oriimage->image_height-1)
            {
                right_value = Oriimage->pixes.gray_value[j+radius + i * (Oriimage->image_width)];
                right_up_value = Oriimage->pixes.gray_value[j+radius-1 + (i-1) * (Oriimage->image_width)];
                right_down_value = Oriimage->pixes.gray_value[j+radius-1 + (i+1) * (Oriimage->image_width)];
            }
            if(i>=radius&&i<=Oriimage->image_height-radius)
            {
                up_value = Oriimage->pixes.gray_value[j + (i-radius) * (Oriimage->image_width)];
                down_value = Oriimage->pixes.gray_value[j + (i+radius) * (Oriimage->image_width)];
            }
           if(center_value>blur_thresholdvalue)
           {
              
               l_c_vec_value = center_value-left_value;
               if(l_c_vec_value<=maxsubpiexvalue)
               {
                l_c_vec_value = 0;
                    byvalueArray[0] = 0;
               }
              
               else
               {
                   cnt_value+=1;
                   byvalueArray[0] = l_c_vec_value;
               }
               
               r_c_vec_value = center_value-right_value;
               if(r_c_vec_value<=maxsubpiexvalue)
               {
                 r_c_vec_value = 0;
                 byvalueArray[1] = 0;
               }
              
                else
               {
                   cnt_value+=1;
                   byvalueArray[1] = r_c_vec_value;
               }
                u_c_vec_value = center_value-up_value;
               if(u_c_vec_value<=maxsubpiexvalue)
               {
 u_c_vec_value = 0;
  byvalueArray[2] = 0;
               }
              
                else
               {
                   cnt_value+=1;
                   byvalueArray[2] = u_c_vec_value;
               }
                d_c_vec_value = center_value-down_value;
               if(d_c_vec_value<=maxsubpiexvalue)
               {
 d_c_vec_value = 0;
  byvalueArray[3] = 0;
               }
                
                else
               {
                   cnt_value+=1;
                   byvalueArray[3] = d_c_vec_value;
               }
               lu_c_vec_value = center_value-left_up_value;
               if(lu_c_vec_value<=maxsubpiexvalue)
               {
 lu_c_vec_value = 0;
  byvalueArray[4] = 0;
               }
              
               else
               {
                   cnt_value+=1;
                   byvalueArray[4] = lu_c_vec_value;
               }
               
               ld_c_vec_value = center_value-left_down_value;
               if(ld_c_vec_value<=maxsubpiexvalue)
               {
ld_c_vec_value = 0;
   byvalueArray[5] = 0;
               }
               
               else
               {
                   cnt_value+=1;
                   byvalueArray[5] = ld_c_vec_value;
               }
               
               ru_c_vec_value = center_value-right_up_value;
               if(ru_c_vec_value<=maxsubpiexvalue)
               {
 ru_c_vec_value =0;
  byvalueArray[6] = 0;
               }
               
                else
                {
                    cnt_value +=1;
                    byvalueArray[6] = ru_c_vec_value;
                }
                rd_c_vec_value = center_value-right_down_value;
                if(rd_c_vec_value<=maxsubpiexvalue)
                {
  rd_c_vec_value = 0;
  byvalueArray[7] = 0;
                }
              
                else
                {
                    cnt_value+=1;
                    byvalueArray[7] = rd_c_vec_value;
                }
                
                
               if(cnt_value>=6)
               {
                   cnt_value = 0;
                   E_QuickSortArray(byvalueArray,0,7);
                    average_count=0;
                    average_value = 0;
                  // if(byvalueArray[7]-byvalueArray[0]>=20)
                   // printf("or_by-->%d,%d,%d,%d,%d,%d,%d,%d\r\n",byvalueArray[0],byvalueArray[1],byvalueArray[2],byvalueArray[3],byvalueArray[4],byvalueArray[5],byvalueArray[6],byvalueArray[7]);
                    for(aver_k=0;aver_k<8;aver_k++)
                    {
                        if(byvalueArray[aver_k]!=0)
                        {
                            average_value +=byvalueArray[aver_k];
                            average_count+=1;
                        }
                    }
                    average_value = average_value/average_count;
                   
                   // printf("aver_value-->%d\r\n",average_value);

                    for(aver_k=0;aver_k<8;aver_k++)
                    {
                        if(byvalueArray[aver_k]!=0)
                        {
                           byvalueArray[aver_k]= byvalueArray[aver_k]-average_value;
                            //average_count+=1;
                        }
                    }
                    
                    // printf("by-->%d,%d,%d,%d,%d,%d,%d,%d\r\n",byvalueArray[0],byvalueArray[1],byvalueArray[2],byvalueArray[3],byvalueArray[4],byvalueArray[5],byvalueArray[6],byvalueArray[7]);
                    if(byvalueArray[7]<=50&&byvalueArray[7]>=0&&(byvalueArray[7]==byvalueArray[6]||byvalueArray[6]==byvalueArray[5]))//>=-1&&byvalueArray[6]-byvalueArray[5]<=1)
                        {
                            OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 255;
                            if(i>half_height*0.5&&i<half_height*1.5&&j>half_width*0.5&&j<half_width*1.5)
                        {
                            center_area +=1;
                            if(center_area>max_cnt)
                                {
                            max_cnt = center_area;
                            max_index = 0;
                                }
                        }
                        else
                        {
                            if(i>0&&i<half_height&&j>0&&j<half_width)
                        {
                            lu_cnt +=1;
                            if(lu_cnt>max_cnt)
                            {
                                max_cnt = lu_cnt;
                                max_index = 1;
                            }
                        }
                if(i>0&&i<half_height&&j>half_width&&j<Oriimage->image_width)
                {
                    ru_cnt +=1;
                    if(ru_cnt>max_cnt)
                    {
                        max_cnt = ru_cnt;
                        max_index = 2;
                    }
                }
                if(i>half_height&&i<Oriimage->image_height&&j>0&&j<half_width)
                {
                    ld_cnt +=1;
                    if(ld_cnt>max_cnt)
                    {
                        max_cnt = ld_cnt;
                        max_index = 3;
                    }
                }
                if(i>half_height&&i<Oriimage->image_height&&j>half_width&&j<Oriimage->image_width)
                {
                    rd_cnt +=1;
                    if(rd_cnt>max_cnt)
                    {
                        max_cnt = rd_cnt;
                        max_index = 4;
                    }
                }
                        }
                        }
                      
                    
               }
                else
                {
                    cnt_value = 0;
                    OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 0;
                }
           }
        }
    }
   // printf("lu_cnt-->%d,ld_cnt-->%d,ru_cnt-->%d,rd_cnt-->%d,center-->%d,max_cnt-->%d,max_index-->%d\r\n",lu_cnt,ld_cnt,ru_cnt,rd_cnt,center_area,max_cnt,max_index);
     return max_index;
}


float VerifyCircle(E_Circle* predictCircle,int innerCirclePts[][2],int ptsNums)
{
   int nums = 0;
   int i=0;
   float pt_distance = 0.0;
   float inner_score = 0.0;
   float radius_err = 2.0;
   for(i=0;i<ptsNums;i++)
   {
      pt_distance = sqrt((innerCirclePts[i][0]-predictCircle->x)*(innerCirclePts[i][0]-predictCircle->x)+(innerCirclePts[i][1]-predictCircle->y)*(innerCirclePts[i][1]-predictCircle->y));
      //printf("pt_distance-->%f,%f,%f\r\n",pt_distance,(float)predictCircle->radius*0.7,(float)predictCircle->radius*1.3);
      if(pt_distance>=((float)predictCircle->radius-radius_err*2.0)&&pt_distance<=((float)predictCircle->radius+radius_err))
      {
          nums+=1;
        //edgeImage->pixes.gray_value[innerCirclePts[i][0]+innerCirclePts[i][1]*edgeImage->image_width]=255;
      }
      else
      {
          // edgeImage->pixes.gray_value[innerCirclePts[i][0]+innerCirclePts[i][1]*edgeImage->image_width]=0;
      }
      
   }
  // printf("num-->%d,%d,%d\r\n",nums,(int)(2.09*predictCircle->radius),predictCircle->radius);
   //if(nums>=(int)(2.09*predictCircle->radius))
    inner_score = (float)nums/(float)ptsNums;
   return inner_score;
}
void CreateCircle(int cadidatePt[][2],E_Circle* predictCircle)
{
     float x1 = cadidatePt[0][0];
     float x2 = cadidatePt[1][0];
     float x3 = cadidatePt[2][0];
     float y1 = cadidatePt[0][1];
     float y2 = cadidatePt[1][1];
     float y3 = cadidatePt[2][1];
     if(( 2*(x1*(y2-y3) - y1*(x2-x3) + x2*y3 - x3*y2) )!=0)
     {
     predictCircle->x = (x1*x1+y1*y1)*(y2-y3) + (x2*x2+y2*y2)*(y3-y1) + (x3*x3+y3*y3)*(y1-y2);
     predictCircle->x /= ( 2*(x1*(y2-y3) - y1*(x2-x3) + x2*y3 - x3*y2) );
     predictCircle->y = (x1*x1 + y1*y1)*(x3-x2) + (x2*x2+y2*y2)*(x1-x3) + (x3*x3 + y3*y3)*(x2-x1);
     predictCircle->y /= ( 2*(x1*(y2-y3) - y1*(x2-x3) + x2*y3 - x3*y2) );
     predictCircle->radius = sqrt((predictCircle->x-x1)*(predictCircle->x-x1) + (predictCircle->y-y1)*(predictCircle->y-y1));
     }
     
    
}

E_Circle *E_RANSACCircleDetection(int candidate_pts[][2],int pts_nums,int min_radius,int max_radius)
{
    E_Circle *m_circle;
    int maxiters = 0;
    float mincirclepercentage = 0.75;
    int candidateforcirclePts[3][2];
    int i=0;
    int random_idx_1 = 0,random_idx_2=0,random_idx_3=0;
    float bestcirclepercentage,cacucirclepercentage;
    int best_x=-1,best_y=-1,best_radius=0;
     maxiters = pts_nums;
     m_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));
     m_circle->x = -1;
     m_circle->y = -1;
     m_circle->radius = 0;
     if(pts_nums<10)
     {
       return m_circle;
     }
    for(i=0;i<maxiters;i++)
    {
       
        random_idx_1 = rand()%pts_nums;
        random_idx_2 = rand()%pts_nums;
        random_idx_3 = rand()%pts_nums;
        if(random_idx_1 == random_idx_2) continue;
        if(random_idx_1 == random_idx_3) continue;
        if(random_idx_3 == random_idx_2) continue;
        candidateforcirclePts[0][0] = candidate_pts[random_idx_1][0];
        candidateforcirclePts[0][1] = candidate_pts[random_idx_1][1];
        candidateforcirclePts[1][0] = candidate_pts[random_idx_2][0];
        candidateforcirclePts[1][1] = candidate_pts[random_idx_2][1];
        candidateforcirclePts[2][0] = candidate_pts[random_idx_3][0];
        candidateforcirclePts[2][1] = candidate_pts[random_idx_3][1];
        CreateCircle(candidateforcirclePts,m_circle);
        //printf("createcircle-->%d,%d,%d\r\n",m_circle->x,m_circle->y,m_circle->radius);
        if(m_circle->x!=-1 && m_circle->y!=-1&&m_circle->radius>min_radius&&m_circle->radius<=max_radius)
        {
            cacucirclepercentage = VerifyCircle(m_circle,candidate_pts,pts_nums);
            if(cacucirclepercentage>bestcirclepercentage)
                {
                    if(m_circle->radius>=min_radius&&m_circle->radius<max_radius)
                        {
                            bestcirclepercentage = cacucirclepercentage;
                            best_x = m_circle->x;
                            best_y = m_circle->y;
                            best_radius =m_circle->radius;
                        }
                }
        }      
    }
    //printf("bestcirclepercentage-->%f,best_x-->%d,%d,%d\r\n",bestcirclepercentage,best_x*4,best_y*4,best_radius*4);
    if(bestcirclepercentage>=mincirclepercentage)
    {
        m_circle->x = best_x;
        m_circle->y = best_y;
        m_circle->radius = best_radius;
    }
    else
    {
        m_circle->x = -1;
        m_circle->y = -1;
        m_circle->radius = 0;   
    }
     //printf("final best_circle-->%d,%d,%d\r\n",m_circle->x,m_circle->y,m_circle->radius);
    return m_circle;
}




E_Circle*  E_FastCornerDetectionByNineArea(Image *Oriimage,Image *OutputImage,int blur_threshold_value,int scale,int min_radius,int max_radius)
{            
    E_Circle* test_circle;                                                                                                                                                                             //threshold_value：130-160之间， 
    int width_index = 0,i=0,j=0, center_value = 0,left_value = 0,right_value = 0,up_value = 0,down_value = 0,left_up_value = 0,left_down_value = 0,right_up_value = 0,right_down_value = 0,radius =3;
    int cnt = 0;
    int area_1=0,area_2 = 0,area_3=0,area_4=0,area_5=0,area_6=0,area_7=0,area_8=0,area_9=0,max_area = 0,max_area_index = 0;
    int area_arr[9]={0};
    int left_x_1 = 0,left_x_2 = 60,left_x_3 = 100,left_x_4 = 160;
    int left_y_1 = 0,left_y_2 = 40,left_y_3 = 80,left_y_4 = 120;
    int area_left_x = 0,area_left_y = 0,area_right_x = 0,area_right_y = 0;
    int min_r = min_radius;
    int max_r = max_radius;
   // printf("min_max-->%d,%d\r\n",min_r,max_r);
    //int min_radius=12,max_radius = 20;
    if(scale==8)
    {
         left_x_1 = 0,left_x_2 = 30,left_x_3 = 50,left_x_4 =80;
         left_y_1 = 0,left_y_2 = 20,left_y_3 = 40,left_y_4 = 60;
         //min_radius = 6,max_radius = 8;
         radius = 2;
    }
    else
    {
        radius = 3;
    }
    
   for (i = radius; i < Oriimage->image_height-radius; i++)
    {
        for (j = radius; j < Oriimage->image_width-radius; j++)
        {
            center_value = Oriimage->pixes.gray_value[j + i * (Oriimage->image_width)];
            if(j>=radius&&i>=1&&i<=Oriimage->image_height-1)
            {
            left_value = Oriimage->pixes.gray_value[j-radius + i * (Oriimage->image_width)];
            left_up_value = Oriimage->pixes.gray_value[j-radius+1 + (i-1) * (Oriimage->image_width)];
            left_down_value = Oriimage->pixes.gray_value[j-radius+1 + (i+1) * (Oriimage->image_width)];
            }
            if(j<Oriimage->image_width-radius&&i>=1&&i<=Oriimage->image_height-1)
            {
              right_value = Oriimage->pixes.gray_value[j+radius + i * (Oriimage->image_width)];
              right_up_value = Oriimage->pixes.gray_value[j+radius-1 + (i-1) * (Oriimage->image_width)];
              right_down_value = Oriimage->pixes.gray_value[j+radius-1 + (i+1) * (Oriimage->image_width)];
            }
            if(i>=radius&&i<=Oriimage->image_height-radius)
            {
              up_value = Oriimage->pixes.gray_value[j + (i-radius) * (Oriimage->image_width)];
              down_value = Oriimage->pixes.gray_value[j + (i+radius) * (Oriimage->image_width)];
            }
            if((center_value-left_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-right_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-up_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-down_value)>=blur_threshold_value)
            {
               cnt+=1;
            }
              if((center_value-left_up_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
              if((center_value-left_down_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
              if((center_value-right_up_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
              if((center_value-right_down_value)>=blur_threshold_value)
            {
                cnt+=1;
            }
            if(cnt>=6)
            {
                OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 255;
                cnt = 0;
                if(i>=left_y_1&&i<left_y_2&&j>=left_x_1&&j<left_x_2)
                {
                    area_1+=1;
                    if(area_1>max_area)
                    {
                        max_area = area_1;
                        max_area_index = 1;
                    }
                    area_arr[0]= area_1;
                }
                if(i>=left_y_1&&i<left_y_2&&j>=left_x_2&&j<left_x_3)
                {
                    area_2+=1;
                    if(area_2>max_area)
                    {
                        max_area = area_2;
                         max_area_index = 2;
                    }
                     area_arr[1]= area_2;
                }
                if(i>=left_y_1&&i<left_y_2&&j>=left_x_3&&j<left_x_4)
                {
                    area_3 +=1;
                    if(area_3>max_area)
                    {
                        max_area = area_3;
                         max_area_index = 3;
                    }
                     area_arr[2]= area_3;
                }
                if(i>=left_y_2&&i<left_y_3&&j>=left_x_1&&j<left_x_2)
                {
                    area_4+=1;
                    if(area_4>max_area)
                    {
                        max_area = area_4;
                        max_area_index = 4;
                    }
                     area_arr[3]= area_4;
                }
                if(i>=left_y_2&&i<left_y_3&&j>=left_x_2&&j<left_x_3)
                {
                    area_5+=1;
                    if(area_5>max_area)
                    {
                        max_area = area_5;
                         max_area_index = 5;
                    }
                     area_arr[4]= area_5;
                }
                if(i>=left_y_2&&i<left_y_3&&j>=left_x_3&&j<left_x_4)
                {
                    area_6 +=1;
                    if(area_6>max_area)
                    {
                        max_area = area_6;
                         max_area_index = 6;
                    }
                     area_arr[5]= area_6;
                }
                 if(i>=left_y_3&&i<left_y_4&&j>=left_x_1&&j<left_x_2)
                {
                    area_7+=1;
                    if(area_7>max_area)
                    {
                        max_area = area_7;
                         max_area_index = 7;
                    }
                     area_arr[6]= area_7;
                }
                if(i>=left_y_3&&i<left_y_4&&j>=left_x_2&&j<left_x_3)
                {
                    area_8+=1;
                    if(area_8>max_area)
                    {
                        max_area  =area_8;
                         max_area_index = 8;
                    }
                     area_arr[7]= area_8;
                }
                if(i>=left_y_3&&i<left_y_4&&j>=left_x_3&&j<left_x_4)
                {
                    area_9 +=1;
                    if(area_9>max_area)
                    {
                        max_area = area_9;
                         max_area_index = 9;
                    }
                     area_arr[8]= area_9;
                }
            }
        }
    }
         if(max_area>=10)
         {
            // printf("max_area_index-->%d\r\n",max_area_index);
             switch (max_area_index)
                {
                case 1:
                    area_left_x = left_x_1;
                    area_left_y = left_y_1;
                    area_right_x = left_x_2;
                    area_right_y = left_y_2;
                    if(area_arr[1]>=2)
                    {
                        area_right_x = left_x_3;
                    }
                    if(area_arr[3]>=2)
                    {
                        area_right_y = left_y_3;
                    }
                    break;
                case 2:
                    area_left_x = left_x_2;
                    area_left_y = left_y_1;
                    area_right_x = left_x_3;
                    area_right_y = left_y_2;
                    if(area_arr[2]>=2)
                    {
                        area_right_x = left_x_4;
                    }
                    if(area_arr[4]>=2)
                    {
                        area_right_y = left_y_3;
                    }
                break;
                case 3:
                    area_left_x = left_x_3;
                    area_left_y = left_y_1;
                    area_right_x = left_x_4;
                    area_right_y = left_y_2;
                    if(area_arr[5]>=2)
                    {
                        area_right_y = left_y_3;
                    }
                break;
                case 4:
                    area_left_x = left_x_1;
                    area_left_y = left_y_2;
                    area_right_x = left_x_2;
                    area_right_y = left_y_3;
                    if(area_arr[4]>=2)
                    {
                        area_right_x = left_x_3;
                    }
                    if(area_arr[6]>=2)
                    {
                        area_right_y = left_y_4;
                    }
                break;
                case 5:
                    area_left_x = left_x_2;
                    area_left_y = left_y_2;
                    area_right_x = left_x_3;
                    area_right_y = left_y_3;
                break;
                case 6:
                    area_left_x = left_x_3;
                    area_left_y = left_y_2;
                    area_right_x = left_x_4;
                    area_right_y = left_y_3;
                    if(area_arr[8]>=2)
                    {
                        area_right_y = left_y_4;
                    }
                break;
                case 7:
                    area_left_x = left_x_1;
                    area_left_y = left_y_3;
                    area_right_x = left_x_2;
                    area_right_y = left_y_4;
                    if(area_arr[3]>=2)
                    {
                        area_left_y = left_y_2;
                    }
                    if(area_arr[7]>=2)
                    {
                        area_right_x = left_x_3;
                    }
                break;
                case 8:
                    area_left_x =left_x_2;
                    area_left_y = left_y_3;
                    area_right_x = left_x_3;
                    area_right_y = left_y_4;
                    if(area_arr[4]>=2)
                    {
                        area_left_y = left_y_2;
                    }
                    if(area_arr[8]>=2)
                    {
                        area_right_x = left_x_4;
                    }
                break;
                case 9:
                    area_left_x = left_x_3;
                    area_left_y = left_y_3;
                    area_right_x = left_x_4;
                    area_right_y = left_y_4;
                    if(area_arr[5]>=2)
                    {
                        area_left_y = left_y_2;
                    }
                break;
                default:
                    break;
                }
               // printf("area-->%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",area_arr[0],area_arr[1],area_arr[2],area_arr[3],area_arr[4],area_arr[5],area_arr[6],area_arr[7],area_arr[8]);
               //printf("attention_area-->%d,%d,%d,%d\r\n",area_left_x,area_left_y,area_right_x,area_right_y);        
          E_Circle* test_circle;  
         test_circle =  E_SimpleCircleByNineArea(OutputImage,area_left_x,area_left_y,area_right_x,area_right_y,min_r,max_r);
       // printf("test detect circle-->%d,%d,%d\r\n",test_circle->x,test_circle->y,test_circle->radius);
         }
         else
         {
            test_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));
            test_circle->x = -1;
            test_circle->y = -1;
            test_circle->radius = 0;
         }
         
                
   // printf("area-->%d,%d,%d,%d,%d,%d,%d,%d,%d,max_area-->%d\r\n",area_1,area_2,area_3,area_4,area_5,area_6,area_7,area_8,area_9,max_area);
    
    //printf("center-->%d,lu_cnt-->%d,ld_cnt-->%d,ru_cnt-->%d,rd_cnt-->%d,max_cnt--->%d,max_index-->%d\r\n",center_area,lu_cnt,ld_cnt,ru_cnt,rd_cnt,max_cnt,max_index);
    return test_circle;
}

E_Circle *E_SimpleCircleByNineArea(Image* EdgeImage,int left_x,int left_y,int right_x,int right_y,int min_radius,int max_radius)
{
     //E_Circle *m_Finalcircle;
    int candidatePts[200][2];
    int candidatePtsNums = 0;
    int left_start_pt = left_x;
    int left_stop_pt = right_x;
    int up_start_pt =  left_y;
    int up_stop_pt =  right_y;
    int i = 0,j=0,max_pts_nums = 200;
    int width_index = 0;
    int min_r = min_radius;
    int max_r = max_radius;
     //printf("n_min_max-->%d,%d\r\n",min_r,max_r);
     for (i =up_start_pt ; i < up_stop_pt; i++)
        {
            width_index = i * (EdgeImage->image_width);
            for (j = left_start_pt; j < left_stop_pt; j++)
            {
                if (EdgeImage->pixes.gray_value[j + width_index] == 255)
                {
                    if(candidatePtsNums>=max_pts_nums)
                    {
                        break;
                    }
                    else
                    {
                        candidatePts[candidatePtsNums][0] = j;
                        candidatePts[candidatePtsNums][1] = i;
                        candidatePtsNums+=1;
                    }
                }
            }
        }
        //printf("candidatePtsNums--->%d\r\n",candidatePtsNums);
        return E_RANSACCircleDetection(candidatePts,candidatePtsNums,min_r,max_r);// m_Finalcircle;

}
E_Circle * E_FastDetectAttentionPoint(Image *Oriimage,Image* OutputImage,int scale,int min_radius,int max_radius)
{
       E_Circle* test_circle; 
    int width_index = 0,i=0,j=0,k=0, center_value = 0,radius = 3;
    int pixes_static[256]={0}, pixes_max_count = 0,pixes_static_threshold = 0,aver_pixes_err=0;
    int low_bound_value = 0,high_bound_value = 0,bound_cnt=0;
    int left_x_1 = 0,left_x_2 = 60,left_x_3 = 100,left_x_4 = 160;
    int left_y_1 = 0,left_y_2 = 40,left_y_3 = 80,left_y_4 = 120;
    int neborpixes[8] = {0};
    int area_arr[9]={0},max_area = 0,max_area_index = 0;
    int second_max_area_index[2]={0},second_max_area_value[2]={0};//,first_maxvalue=0,second_maxvalue = 0;
    int area_left_x = 0,area_left_y = 0,area_right_x = 0,area_right_y = 0;
    int min_r =min_radius,max_r = max_radius;
      for (i = radius; i < Oriimage->image_height-radius; i++)
    {
        for (j = radius; j < Oriimage->image_width-radius; j++)
        {
            center_value = Oriimage->pixes.gray_value[j + i * (Oriimage->image_width)];
            neborpixes[0] = center_value-Oriimage->pixes.gray_value[j-radius + i * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j-radius + i * (Oriimage->image_width)]:0;
            neborpixes[1]  = center_value-Oriimage->pixes.gray_value[j-radius+1 + (i-1) * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j-radius+1 + (i-1) * (Oriimage->image_width)]:0;
            neborpixes[2]  = center_value-Oriimage->pixes.gray_value[j-radius+1 + (i+1) * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j-radius+1 + (i+1) * (Oriimage->image_width)]:0;
            neborpixes[3] = center_value-Oriimage->pixes.gray_value[j+radius + i * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j+radius + i * (Oriimage->image_width)]:0;
            neborpixes[4] = center_value-Oriimage->pixes.gray_value[j+radius-1 + (i-1) * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j+radius-1 + (i-1) * (Oriimage->image_width)]:0;
            neborpixes[5] = center_value-Oriimage->pixes.gray_value[j+radius-1 + (i+1) * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j+radius-1 + (i+1) * (Oriimage->image_width)]:0;
            neborpixes[6] = center_value-Oriimage->pixes.gray_value[j + (i-radius) * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j + (i-radius) * (Oriimage->image_width)]:0;
            neborpixes[7] = center_value-Oriimage->pixes.gray_value[j + (i+radius) * (Oriimage->image_width)]>0?center_value-Oriimage->pixes.gray_value[j + (i+radius) * (Oriimage->image_width)]:0;
            E_QuickSortArray(neborpixes,0,7);
            for(k=0;k<8;k++)
            {
                if(neborpixes[k]>=20)
                {
                    bound_cnt+=1;
                }
            }
             if(bound_cnt>=6)
            {
             bound_cnt = 0;
             aver_pixes_err = (neborpixes[7]+neborpixes[6]+neborpixes[5]+neborpixes[4])/4;
              OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = aver_pixes_err;
             pixes_static[aver_pixes_err]+=1;
            }
            else
            {
                bound_cnt = 0;
                OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 0;
            }
        }
    }
  //high bound threshold
    for(i=255;i>=0;i--)
    {
        if(pixes_static[i]>=1)
          {
              high_bound_value = i;
              bound_cnt = pixes_static[i];
              break;
          }
    }
    //low bound
    i=i-1;
     for(;i>=0;i--)
    {
        bound_cnt+=pixes_static[i];
       if(bound_cnt>=150)
       {
              low_bound_value = i;
              bound_cnt = 0;
              break;
       }
    }
        if(low_bound_value<=30)
    {
        low_bound_value  = 30;
    }

    if(high_bound_value<=30)
    {
        high_bound_value = 0;
        low_bound_value = 0;
    }
     //printf("threshold-->%d,%d\r\n",low_bound_value,high_bound_value);

    //求解上界及下界
        for (i = radius; i < Oriimage->image_height-radius; i++)
        {
        for (j = radius; j < Oriimage->image_width-radius; j++)
            {
            if( OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)]>=low_bound_value&& OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)]<=high_bound_value)
                {
                    OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 255;
                    if(i>=left_y_1&&i<left_y_2&&j>=left_x_1&&j<left_x_2)
                {
                    area_arr[0]+=1;
                    if(area_arr[0]>max_area)
                    {
                        max_area = area_arr[0];
                        max_area_index = 1;
                    }
                }
                if(i>=left_y_1&&i<left_y_2&&j>=left_x_2&&j<left_x_3)
                {
                    area_arr[1]+=1;
                    if(area_arr[1]>max_area)
                    {
                        max_area = area_arr[1];
                         max_area_index = 2;
                    }
                }
                if(i>=left_y_1&&i<left_y_2&&j>=left_x_3&&j<left_x_4)
                {
                    area_arr[2] +=1;
                    if(area_arr[2]>max_area)
                    {
                        max_area = area_arr[2];
                         max_area_index = 3;
                    }
                }
                if(i>=left_y_2&&i<left_y_3&&j>=left_x_1&&j<left_x_2)
                {
                     area_arr[3]+=1;
                    if( area_arr[3]>max_area)
                    {
                        max_area =  area_arr[3];
                        max_area_index = 4;
                    }
                }
                if(i>=left_y_2&&i<left_y_3&&j>=left_x_2&&j<left_x_3)
                {
                    area_arr[4]+=1;
                    if(area_arr[4]>max_area)
                    {
                        max_area = area_arr[4];
                         max_area_index = 5;
                    }
                }
                if(i>=left_y_2&&i<left_y_3&&j>=left_x_3&&j<left_x_4)
                {
                     area_arr[5] +=1;
                    if( area_arr[5]>max_area)
                    {
                        max_area =  area_arr[5];
                         max_area_index = 6;
                    }
                }
                 if(i>=left_y_3&&i<left_y_4&&j>=left_x_1&&j<left_x_2)
                {
                    area_arr[6]+=1;
                    if(area_arr[6]>max_area)
                    {
                        max_area = area_arr[6];
                         max_area_index = 7;
                    }
                }
                if(i>=left_y_3&&i<left_y_4&&j>=left_x_2&&j<left_x_3)
                {
                     area_arr[7]+=1;
                    if( area_arr[7]>max_area)
                    {
                        max_area  = area_arr[7];
                         max_area_index = 8;
                    }
                }
                if(i>=left_y_3&&i<left_y_4&&j>=left_x_3&&j<left_x_4)
                {
                    area_arr[8] +=1;
                    if(area_arr[8]>max_area)
                    {
                        max_area = area_arr[8];
                         max_area_index = 9;
                    }
                }
                }
            else
             OutputImage->pixes.gray_value[j + i * (Oriimage->image_width)] = 0; 
        }
    }
  //  printf("area-->%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",area_arr[0],area_arr[1],area_arr[2],area_arr[3],area_arr[4],area_arr[5],area_arr[6],area_arr[7],area_arr[8]);
   // printf("max_area_index-->%d\r\n",max_area_index);
   //检测出两个感兴趣区域
     if(area_arr[0]<area_arr[1])
     {
         second_max_area_value[0] = area_arr[0];
         second_max_area_value[1] = area_arr[1];
         second_max_area_index[0] = 1;
         second_max_area_index[1] = 2;
     }
     else
     {
        second_max_area_value[0] = area_arr[1];
        second_max_area_value[1] = area_arr[0];
        second_max_area_index[0] = 2;
        second_max_area_index[1] = 1;
     }
     k = 2;
     while(k<9)
     {
       if(area_arr[k]>second_max_area_value[0]&&area_arr[k]<second_max_area_value[1])
       {
           second_max_area_value[0] = area_arr[k];
           second_max_area_index[0] = k+1;
       }
       else if(area_arr[k]>second_max_area_value[1])
       {
           second_max_area_value[0] = second_max_area_value[1];
           second_max_area_index[0] = second_max_area_index[1];
           second_max_area_value[1] = area_arr[k];
           second_max_area_index[1] = k+1;
       }
       k++;
     }
    // printf("max_area_value ----->%d,%d\r\n",second_max_area_value[0],second_max_area_value[1]);
     //printf("max area index ---->%d,%d\r\n",second_max_area_index[0],second_max_area_index[1]);
    //提取感兴趣区域并检测
  for(k=1;k>-1;k--)
  {
    if(second_max_area_value[k]>=10)
         {
             //printf("max_area_index-->%d\r\n",second_max_area_index[k]);
             switch (second_max_area_index[k])
                {
                case 1:
                    area_left_x = left_x_1;
                    area_left_y = left_y_1;
                    area_right_x = left_x_2;
                    area_right_y = left_y_2;
                    if(area_arr[1]>=2)
                    {
                        area_right_x = left_x_3;
                    }
                    if(area_arr[3]>=2)
                    {
                        area_right_y = left_y_3;
                    }
                    break;
                case 2:
                    area_left_x = left_x_2;
                    area_left_y = left_y_1;
                    area_right_x = left_x_3;
                    area_right_y = left_y_2;
                    if(area_arr[2]>=2)
                    {
                        area_right_x = left_x_4;
                    }
                    if(area_arr[4]>=2)
                    {
                        area_right_y = left_y_3;
                    }
                break;
                case 3:
                    area_left_x = left_x_3;
                    area_left_y = left_y_1;
                    area_right_x = left_x_4;
                    area_right_y = left_y_2;
                    if(area_arr[5]>=2)
                    {
                        area_right_y = left_y_3;
                    }
                break;
                case 4:
                    area_left_x = left_x_1;
                    area_left_y = left_y_2;
                    area_right_x = left_x_2;
                    area_right_y = left_y_3;
                    if(area_arr[4]>=2)
                    {
                        area_right_x = left_x_3;
                    }
                    if(area_arr[6]>=2)
                    {
                        area_right_y = left_y_4;
                    }
                break;
                case 5:
                    area_left_x = left_x_2;
                    area_left_y = left_y_2;
                    area_right_x = left_x_3;
                    area_right_y = left_y_3;
                break;
                case 6:
                    area_left_x = left_x_3;
                    area_left_y = left_y_2;
                    area_right_x = left_x_4;
                    area_right_y = left_y_3;
                    if(area_arr[8]>=2)
                    {
                        area_right_y = left_y_4;
                    }
                break;
                case 7:
                    area_left_x = left_x_1;
                    area_left_y = left_y_3;
                    area_right_x = left_x_2;
                    area_right_y = left_y_4;
                    if(area_arr[3]>=2)
                    {
                        area_left_y = left_y_2;
                    }
                    if(area_arr[7]>=2)
                    {
                        area_right_x = left_x_3;
                    }
                break;
                case 8:
                    area_left_x =left_x_2;
                    area_left_y = left_y_3;
                    area_right_x = left_x_3;
                    area_right_y = left_y_4;
                    if(area_arr[4]>=2)
                    {
                        area_left_y = left_y_2;
                    }
                    if(area_arr[8]>=2)
                    {
                        area_right_x = left_x_4;
                    }
                break;
                case 9:
                    area_left_x = left_x_3;
                    area_left_y = left_y_3;
                    area_right_x = left_x_4;
                    area_right_y = left_y_4;
                    if(area_arr[5]>=2)
                    {
                        area_left_y = left_y_2;
                    }
                break;
                default:
                    break;
                }
                  
                test_circle =  E_SimpleCircleByNineArea(OutputImage,area_left_x,area_left_y,area_right_x,area_right_y,min_r,max_r);
                if(test_circle->x==-1||test_circle->y==-1)
                {
                    M_Free(test_circle);
                    continue;
                }
                else
                {
                  //  printf("detect circle--------->%d,%d,%d\r\n",test_circle->x*4,test_circle->y*4,test_circle->radius*4);
                    break;
                } 
                }
                else
                {
                    test_circle = (E_Circle *)M_Malloc(sizeof(E_Circle));
                    test_circle->x = -1;
                    test_circle->y = -1;
                    test_circle->radius = 0;
                    break;
                }
  }

            // printf("area-->%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",area_arr[0],area_arr[1],area_arr[2],area_arr[3],area_arr[4],area_arr[5],area_arr[6],area_arr[7],area_arr[8]);
            // printf("attention_area-->%d,%d,%d,%d\r\n",area_left_x,area_left_y,area_right_x,area_right_y); 
        return test_circle;
}