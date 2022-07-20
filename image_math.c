#include "image_math.h"
M_Matrix2D* Matrix2D_Create(  unsigned int rows,
		                      unsigned int cols,
					          double static_padd_value)
    {
        M_Matrix2D* new_matrix2d = (M_Matrix2D*)M_Malloc(sizeof(M_Matrix2D));
        unsigned int  size = cols*rows;
       int i=0,j=0;
        new_matrix2d->ElementData = (double*)M_Malloc(size*sizeof(double));
        new_matrix2d->cols = cols;
        new_matrix2d->rows = rows;
        new_matrix2d->size = size;
        if(rows<cols)
        {
            for(i=0;i<rows;i++)
                {
                    int cols_size = i*cols;
                    for(j=0;j<cols;j++)
                    {
                        new_matrix2d->ElementData[j+cols_size] = static_padd_value;
                    }
                }
        }
        else
        {
            for(i=0;i<cols;i++)
                {
                    int rows_size = i*rows;
                    for(j=0;j<rows;j++)
                    {
                        new_matrix2d->ElementData[j+rows_size] = static_padd_value;
                    }
                }
        }
        
       
        //M_Memset(new_matrix2d->ElementData,static_padd_value,size*sizeof(double));
        return new_matrix2d;
    }
M_Matrix2D* Matrix2D_Create_FArry(  double OriArray[],
                                    int ArraySize,
                                    unsigned int rows,
		                            unsigned int cols)
    {
        M_Matrix2D* new_matrix2d = (M_Matrix2D*)M_Malloc(sizeof(M_Matrix2D));
        unsigned int  size = cols*rows;
          int i=0,j=0;
        new_matrix2d->ElementData = (double*)M_Malloc(size*sizeof(double));
        new_matrix2d->cols = cols;
        new_matrix2d->rows = rows;
        new_matrix2d->size = size;
        for(i=0;i<rows;i++)
        {
            for(j=0;j<cols;j++)
            {
                new_matrix2d->ElementData[j+i*cols] =OriArray[j+i*cols];
            }
        }
        return new_matrix2d;
    }
M_Matrix2D* Matrix2D_Create_FImage(Image* OriImage)
    {
    if(OriImage->image_channel!=1)
    {
        return NULL;
    }
    M_Matrix2D* new_matrix2d = (M_Matrix2D*)M_Malloc(sizeof(M_Matrix2D));
    unsigned int  size = OriImage->image_height*OriImage->image_width;
      int i=0,j=0;
    new_matrix2d->ElementData = (double*)M_Malloc(size*sizeof(double));
    new_matrix2d->cols =  OriImage->image_width;
    new_matrix2d->rows =  OriImage->image_height;
    new_matrix2d->size =  size;
    if(OriImage->image_height<OriImage->image_width)
    {
       for(i=0;i<OriImage->image_height;i++)
        {
            int width_size = i*OriImage->image_width;
            for(j=0;j<OriImage->image_width;j++)
            {
                new_matrix2d->ElementData[j+width_size] =OriImage->pixes.gray_value[j+width_size];
            }
        }
    }
    else
    {
          for(i=0;i<OriImage->image_width;i++)
        {
            int height_size= i*OriImage->image_height;
            for(j=0;j<OriImage->image_height;j++)
            {
                new_matrix2d->ElementData[j+height_size] =OriImage->pixes.gray_value[j+height_size];
            }
        }
    }
    
  
        return new_matrix2d;
    }
Image* Matrix2D_Trans_TImage(M_Matrix2D* OriMatrix)
    {
     Image* new_image = (Image*)M_Malloc(sizeof(Image));
     int image_size = OriMatrix->rows*OriMatrix->cols;
      int i=0,j=0;
     new_image->pixes.gray_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
     new_image->image_width = OriMatrix->cols;
     new_image->image_height = OriMatrix->rows;
     new_image->image_channel = 1;
     new_image->image_size = image_size;
      new_image->image_format = IMAGE_FORMAT_GRAY;
      if(new_image->image_height<new_image->image_width)
      {
        for(i=0;i<new_image->image_height;i++)
        {
            int width_size = i*new_image->image_width;
            for(j=0;j<new_image->image_width;j++)
            {
                if(OriMatrix->ElementData[j+width_size]<0.0)
                {
                    new_image->pixes.gray_value[j+width_size] = 0;
                }
                else if(OriMatrix->ElementData[j+width_size]>255.0)
                {
                    new_image->pixes.gray_value[j+width_size] = 255;
                }
                else
                {
                    new_image->pixes.gray_value[j+width_size] = OriMatrix->ElementData[j+width_size];
                }
                
            }
        }
      }
      else
      {
          for(i=0;i<new_image->image_width;i++)
        {
            int height_size= i*new_image->image_height;
            for(j=0;j<new_image->image_height;j++)
            {
                if(OriMatrix->ElementData[j+height_size]<0.0)
                {
                    new_image->pixes.gray_value[j+height_size] = 0;
                }
                else if(OriMatrix->ElementData[j+height_size]>255.0)
                {
                    new_image->pixes.gray_value[j+height_size] = 255;
                }
                else
                {
                    new_image->pixes.gray_value[j+height_size] = OriMatrix->ElementData[j+height_size];
                }
                
            }
        }
      }
    return new_image;
    }
bool Matrix2D_Destroy(M_Matrix2D** OriMatrix)
    {
    if((*OriMatrix)==NULL||(*OriMatrix)->ElementData==NULL)
    {
       return false;
    }
    M_Free((*OriMatrix)->ElementData);
    (*OriMatrix)->ElementData=NULL;
    M_Free((*OriMatrix));
    (*OriMatrix) = NULL;
    return true;
    }
bool Matrix2D_Printf(M_Matrix2D* OriMatrix)
    {
        if(OriMatrix==NULL)
        {
            return false;
        }
         int i=0,j=0;
        for(i=0;i<OriMatrix->rows;i++)
        {
            for(j=0;j<OriMatrix->cols;j++)
            {
                printf("%f ",OriMatrix->ElementData[j+i*OriMatrix->cols]);
            }
            printf("\n");
        }
        return true;
    }
M_Matrix3D* Matrix3D_Create(  unsigned int cols,
		                      unsigned int rows,
					          double static_padd_c1value,
                              double static_padd_c2value,
                              double static_padd_c3value)
    {
        M_Matrix3D* new_matrix3d = (M_Matrix3D*)M_Malloc(sizeof(M_Matrix3D));
        unsigned int size = cols*rows;
         int i=0,j=0;
        new_matrix3d->cols = cols;
        new_matrix3d->rows = rows;
        new_matrix3d->size = 3*size;
        new_matrix3d->ElementData.c_1_value = (double*)M_Malloc(size*sizeof(double));
        new_matrix3d->ElementData.c_2_value = (double*)M_Malloc(size*sizeof(double));
        new_matrix3d->ElementData.c_3_value = (double*)M_Malloc(size*sizeof(double));
        for(i=0;i<rows;i++)
        {
            for(j=0;j<cols;j++)
            {
                new_matrix3d->ElementData.c_1_value[j+i*cols] = static_padd_c1value;
                new_matrix3d->ElementData.c_2_value[j+i*cols] = static_padd_c2value;
                new_matrix3d->ElementData.c_3_value[j+i*cols] = static_padd_c3value;
            }
        }
        return new_matrix3d; 
    }
M_Matrix3D* Matrix3D_Create_FArry(  double OriArray[],
                                    int ArraySize,
                                    unsigned int cols,
		                            unsigned int rows)
    {
        if(cols*rows*3!=ArraySize)
        {
            return NULL;
        }
        M_Matrix3D* new_matrix3d = (M_Matrix3D*)M_Malloc(sizeof(M_Matrix3D));
        unsigned int size = cols*rows;
         int i=0,j=0,step_flag=0;
        new_matrix3d->cols = cols;
        new_matrix3d->rows = rows;
        new_matrix3d->size = 3*size;
        new_matrix3d->ElementData.c_1_value = (double*)M_Malloc(size*sizeof(double));
        new_matrix3d->ElementData.c_2_value = (double*)M_Malloc(size*sizeof(double));
        new_matrix3d->ElementData.c_3_value = (double*)M_Malloc(size*sizeof(double));
        for(i=0;i<rows;i++)
                {
                    step_flag = 0;
                    for(j=0;j<cols;j++)
                        {
                            new_matrix3d->ElementData.c_1_value[j+i*cols] = OriArray[step_flag+i*cols*3];
                            new_matrix3d->ElementData.c_2_value[j+i*cols] = OriArray[step_flag+1+i*cols*3];
                            new_matrix3d->ElementData.c_3_value[j+i*cols] = OriArray[step_flag+2+i*cols*3];
                            step_flag+=3;
                        }
                }
        return new_matrix3d;
    }
M_Matrix3D* Matrix3D_Create_FImage(Image* OriImage)
    {
        M_Matrix3D* new_matrix3d = (M_Matrix3D*)M_Malloc(sizeof(M_Matrix3D));
        int cols = OriImage->image_width;
        int rows = OriImage->image_height;
        unsigned int size = cols*rows;
         int i= 0,j=0;
        new_matrix3d->cols = cols;
        new_matrix3d->rows = rows;
        new_matrix3d->size = 3*size;
        new_matrix3d->ElementData.c_1_value = (double*)M_Malloc(size*sizeof(double));
        new_matrix3d->ElementData.c_2_value = (double*)M_Malloc(size*sizeof(double));
        new_matrix3d->ElementData.c_3_value = (double*)M_Malloc(size*sizeof(double));
          for(i=0;i<rows;i++)
                {
                    for(j=0;j<cols;j++)
                        {
                            new_matrix3d->ElementData.c_1_value[j+i*cols] = OriImage->pixes.rgb_value.r_value[j+i*cols];
                            new_matrix3d->ElementData.c_2_value[j+i*cols] = OriImage->pixes.rgb_value.g_value[j+i*cols];
                            new_matrix3d->ElementData.c_3_value[j+i*cols] = OriImage->pixes.rgb_value.b_value[j+i*cols];
                        }
                }
        return new_matrix3d;
    }
Image* Matrix3D_Trans_TImage(M_Matrix3D* OriMatrix)
    {
        if(OriMatrix==NULL)
        {
            return NULL;
        }
        Image* new_image = (Image*)M_Malloc(sizeof(Image));
        int image_size = OriMatrix->rows*OriMatrix->cols;
        int i=0,j=0;
        new_image->image_width = OriMatrix->cols;
        new_image->image_height = OriMatrix->rows;
        new_image->image_channel = 3;
        new_image->image_size = 3*image_size;
         new_image->image_format = IMAGE_FORMAT_RGB;
        new_image->pixes.rgb_value.r_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
        new_image->pixes.rgb_value.g_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
        new_image->pixes.rgb_value.b_value = (unsigned char*)M_Malloc(image_size*sizeof(unsigned char));
        for(i=0;i<new_image->image_height;i++)
            {
                for(j=0;j<new_image->image_width;j++)
                    {
                        if( OriMatrix->ElementData.c_1_value[j+i*new_image->image_width]<0.0)
                        {
                            new_image->pixes.rgb_value.r_value[j+i*new_image->image_width] =0;
                            continue;
                        }
                        else if(OriMatrix->ElementData.c_1_value[j+i*new_image->image_width]>255.0)
                        {
                           new_image->pixes.rgb_value.r_value[j+i*new_image->image_width] = 255;
                            continue;
                        }
                        
                        if(OriMatrix->ElementData.c_2_value[j+i*new_image->image_width]<0.0)
                        {
                            new_image->pixes.rgb_value.g_value[j+i*new_image->image_width] = 0;
                        }
                        else if(OriMatrix->ElementData.c_2_value[j+i*new_image->image_width]>255.0)
                        {
                           new_image->pixes.rgb_value.g_value[j+i*new_image->image_width] = 255;
                            continue;
                        }
                        if(OriMatrix->ElementData.c_3_value[j+i*new_image->image_width]<0.0)
                        {
                            new_image->pixes.rgb_value.b_value[j+i*new_image->image_width] = 0;
                        }
                        else if(OriMatrix->ElementData.c_3_value[j+i*new_image->image_width]>255.0)
                        {
                            new_image->pixes.rgb_value.b_value[j+i*new_image->image_width] = 255;
                            continue;
                        }
                        new_image->pixes.rgb_value.r_value[j+i*new_image->image_width] =  OriMatrix->ElementData.c_1_value[j+i*new_image->image_width];
                        new_image->pixes.rgb_value.g_value[j+i*new_image->image_width] =  OriMatrix->ElementData.c_2_value[j+i*new_image->image_width];
                        new_image->pixes.rgb_value.b_value[j+i*new_image->image_width] =  OriMatrix->ElementData.c_3_value[j+i*new_image->image_width];
                    }
            }
        return new_image;
    }
bool Matrix3D_Destroy(M_Matrix3D** OriMatrix)
    {
        if((*OriMatrix)==NULL)
        {
            return false;
        }
        M_Free((*OriMatrix)->ElementData.c_1_value);
        M_Free((*OriMatrix)->ElementData.c_2_value);
        M_Free((*OriMatrix)->ElementData.c_3_value);
        M_Free((*OriMatrix));
        (*OriMatrix) = NULL;
        return true;
    }
M_Matrix2D* Matrix2DAdd(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix)
    {
     M_Matrix2D* new_matrix2d = Matrix2D_Create(OriMatrix->rows,OriMatrix->cols,0); 
     int i=0,j=0;
     if(OriMatrix->cols!=MaskMatrix->cols||OriMatrix->rows!=MaskMatrix->rows)
     {
        Matrix2D_Destroy(&new_matrix2d);
         return NULL;
     }
        for(i=0;i<OriMatrix->rows;i++)
        {
            for(j=0;j<OriMatrix->cols;j++)
            {
                new_matrix2d->ElementData[j+i*OriMatrix->cols] =OriMatrix->ElementData[j+i*OriMatrix->cols]+MaskMatrix->ElementData[j+i*OriMatrix->cols];
            }
        }
    return new_matrix2d;
    }

M_Matrix2D* Matrix2DSub(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix)
    {
         M_Matrix2D* new_matrix2d = Matrix2D_Create(OriMatrix->rows,OriMatrix->cols,0); 
         int i=0,j=0;
        if(OriMatrix->cols!=MaskMatrix->cols||OriMatrix->rows!=MaskMatrix->rows)
        {
            Matrix2D_Destroy(&new_matrix2d);
            return NULL;
        }
        for(i=0;i<OriMatrix->rows;i++)
        {
            for(j=0;j<OriMatrix->cols;j++)
            {
                 new_matrix2d->ElementData[j+i*OriMatrix->cols] =OriMatrix->ElementData[j+i*OriMatrix->cols]-MaskMatrix->ElementData[j+i*OriMatrix->cols];
            }
        }
    return new_matrix2d;
    }
M_Matrix2D* Matrix2DDotProduct(M_Matrix2D* OriMatrix,double Mask_N)
    {
         M_Matrix2D* new_matrix2d = Matrix2D_Create(OriMatrix->rows,OriMatrix->cols,0.0); 
         int i=0,j=0;
        if(OriMatrix==NULL)
            {
                Matrix2D_Destroy(&new_matrix2d);
                return NULL;
            }
        for(i=0;i<OriMatrix->rows;i++)
        {
            for(j=0;j<OriMatrix->cols;j++)
            {
                 new_matrix2d->ElementData[j+i*OriMatrix->cols] = OriMatrix->ElementData[j+i*OriMatrix->cols] *Mask_N;
            }
        }
    return new_matrix2d;
    }
M_Matrix2D* Matrix2DDahaMProduct(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix)
    {
        M_Matrix2D* new_matrix2d = Matrix2D_Create(OriMatrix->rows,OriMatrix->cols,0.0); 
        int i=0,j=0;
     if(OriMatrix->cols!=MaskMatrix->cols||OriMatrix->rows!=MaskMatrix->rows)
     {
        Matrix2D_Destroy(&new_matrix2d);
         return NULL;
     }
        for(i=0;i<OriMatrix->rows;i++)
        {
            for(j=0;j<OriMatrix->cols;j++)
            {
                new_matrix2d->ElementData[j+i*OriMatrix->cols] =OriMatrix->ElementData[j+i*OriMatrix->cols]*MaskMatrix->ElementData[j+i*OriMatrix->cols];
            }
        }
    return new_matrix2d;
    }
M_Matrix2D* Matrix2DCrossProduct(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix)
    {
       M_Matrix2D* new_matrix2d = Matrix2D_Create(OriMatrix->rows,MaskMatrix->cols,0.0); 
       int i=0,j=0,k=0;
      if(OriMatrix->cols!=MaskMatrix->rows)
      {
           Matrix2D_Destroy(&new_matrix2d);
            return NULL;
      }
      for(i=0;i<OriMatrix->rows;i++)
      {
          for(j=0;j<MaskMatrix->cols;j++)
          {
              for(k=0;k<OriMatrix->cols;k++)
              {
                  new_matrix2d->ElementData[i*new_matrix2d->cols+j]+=OriMatrix->ElementData[i*OriMatrix->cols + k] * MaskMatrix->ElementData[k*MaskMatrix->cols + j];
              }
          }
      }
      return new_matrix2d;
    }
M_Matrix2D* Matrix2DTransForm(M_Matrix2D* OriMatrix)
    {
        M_Matrix2D* new_matrix2d = Matrix2D_Create(OriMatrix->cols,OriMatrix->rows,0);
        int i,j;
        if(new_matrix2d==NULL)
        {
            return NULL;
        }
          for(i=0;i<OriMatrix->rows;i++)
        {
            for(j=0;j<OriMatrix->cols;j++)
            {
                new_matrix2d->ElementData[i+j*OriMatrix->rows]=OriMatrix->ElementData[j+i*OriMatrix->cols];
            }
        }
        return new_matrix2d;
    }
bool Matrix2DConvFliter(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix)
    {
       int mask_center_rows = MaskMatrix->rows/2;
       int mask_center_cols = MaskMatrix->cols/2;
       int i,j,k,m;
       if(OriMatrix->rows<OriMatrix->cols)
       {
            for(i=0;i<OriMatrix->rows;i++)
                {
                    int ori_cols_size = i*OriMatrix->cols;
                    for(j=0;j<OriMatrix->cols;j++)
                    {
               int rows_edge_down = i-(mask_center_rows);
               int rows_edge_up = i+(mask_center_rows);
               int cols_edge_down = j-mask_center_cols;
               int cols_edge_up = j+mask_center_cols;
                if(rows_edge_down>=0&&rows_edge_up<OriMatrix->rows&&cols_edge_down>=0&&cols_edge_up<OriMatrix->cols)
                    {
                    double sum = 0;
                    for(k=0;k<MaskMatrix->rows;k++)
                    {
                        int cols_size= k*MaskMatrix->cols;
                        int shift_cols_size = (i-mask_center_rows+k)*OriMatrix->cols;
                        for(m=0;m<MaskMatrix->cols;m++)
                        {
                            sum+=MaskMatrix->ElementData[m+cols_size]*OriMatrix->ElementData[j-mask_center_cols+m+shift_cols_size];
                        }
                    }
                   OriMatrix->ElementData[j+ori_cols_size] = sum;
                 }
            }
        }
       }
       else
       {
          for(i=0;i<OriMatrix->cols;i++)
        {
            int ori_rows_size = i*OriMatrix->rows;
            for(j=0;j<OriMatrix->rows;j++)
            {
               int rows_edge_down = j-(mask_center_rows);
               int rows_edge_up = j+(mask_center_rows);
               int cols_edge_down = i-mask_center_cols;
               int cols_edge_up = i+mask_center_cols;
                if(rows_edge_down>=0&&rows_edge_up<OriMatrix->rows&&cols_edge_down>=0&&cols_edge_up<OriMatrix->cols)
                    {
                    double sum = 0;
                    for(k=0;k<MaskMatrix->rows;k++)
                    {
                        int cols_size = k*MaskMatrix->cols;
                        int shift_rows_size = (i-mask_center_cols+k)*OriMatrix->rows;
                        for(m=0;m<MaskMatrix->cols;m++)
                        {
                            sum+=MaskMatrix->ElementData[m+cols_size]*OriMatrix->ElementData[j-mask_center_rows+m+shift_rows_size];
                        }
                    }
                   OriMatrix->ElementData[j+ori_rows_size] = sum;
                 }
            }
        }
       }
       
        return true;
    }