#ifndef __IMAGE_MATH_H__
#define __IMAGE_MATH_H__
#include "image_engine.h"
#include "image_core.h"
/**图像运算模块v1.0****/
/*
Author: 沈文祥
Edit time:2020.3.21
*/
typedef struct
{
  double* ElementData;
  unsigned int rows;
  unsigned int cols;
  unsigned int size;
}M_Matrix2D;//二维矩阵类
typedef struct
{
  	struct
		{
		double* c_1_value;
		double* c_2_value;
		double* c_3_value;
		}ElementData;
  unsigned int rows;
  unsigned int cols;
  unsigned int size;
}M_Matrix3D;//三维矩阵类
/*初始化定义*/
//初始常值二维矩阵创建
M_Matrix2D* Matrix2D_Create(  unsigned int rows,
		                      unsigned int cols,
					          double static_padd_value);
//从一维数组中创建二维矩阵
M_Matrix2D* Matrix2D_Create_FArry(  double OriArray[],
                                    int ArraySize,
                                    unsigned int rows,
		                            unsigned int cols);
//从Image类型转换为Matrix2D
M_Matrix2D* Matrix2D_Create_FImage(Image* OriImage);
//从Matrix2D转换为Image
Image* Matrix2D_Trans_TImage(M_Matrix2D* OriMatrix);
//Matrix2D内存释放
bool Matrix2D_Destroy(M_Matrix2D** OriMatrix);
//打印Matrix2D
bool Matrix2D_Printf(M_Matrix2D* OriMatrix);
//初始常值三维矩阵创建
M_Matrix3D* Matrix3D_Create(  unsigned int rows,
		                      unsigned int cols,
					          double static_padd_c1value,
                              double static_padd_c2value,
                              double static_padd_c3value);
//从一维数组中创建三维矩阵
M_Matrix3D* Matrix3D_Create_FArry(  double OriArray[],
                                    int ArraySize,
                                    unsigned int rows,
		                            unsigned int cols);
//从Image类型转换为Matrix3D
M_Matrix3D* Matrix3D_Create_FImage(Image* OriImage);
//从Matrix3D转换为Image
Image* Matrix3D_Trans_TImage(M_Matrix3D* OriMatrix);
//Matrix3D释放内存
bool Matrix3D_Destroy(M_Matrix3D** OriMatrix);
/*矩阵加法*/
M_Matrix2D* Matrix2DAdd(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix);
/*矩阵减法*/
M_Matrix2D* Matrix2DSub(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix);
/*矩阵点乘*/
M_Matrix2D* Matrix2DDotProduct(M_Matrix2D* OriMatrix,double Mask_N);
/*矩阵达哈马内积*/
M_Matrix2D* Matrix2DDahaMProduct(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix);
/*矩阵叉乘*/
M_Matrix2D* Matrix2DCrossProduct(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix);
/*矩阵转置*/
M_Matrix2D* Matrix2DTransForm(M_Matrix2D* OriMatrix);
/*2-D卷积*/
bool Matrix2DConvFliter(M_Matrix2D* OriMatrix,M_Matrix2D* MaskMatrix);
/*快速排序算法*/

#endif