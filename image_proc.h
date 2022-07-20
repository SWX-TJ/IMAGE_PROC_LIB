#ifndef __IMAGE_PROC_H__
#define __IMAGE_PROC_H__
#include "image_engine.h"
#include "image_core.h"
#include "evector.h"
typedef struct
{
    VectorPt* Candidate_Point;
    unsigned int edge_point_num;
}E_Edge;


typedef struct
{
    E_Edge Candidate_Edge[100];
    unsigned int edge_num;
}E_Edge_t;

typedef struct
{
    VectorPt3D* Candidate_Circle;
    unsigned int Circle_num;
}E_Circles;

typedef struct
{
     int x;
     int y;
    unsigned int radius;
}E_Circle;


typedef enum
{
 IMAGE_THREAD_BIN=0,
 IMAGE_THREAD_BIN_INV,
 IMAGE_THREAD_OSTU,
 IMAGE_THREAD_HIST,
 IMAGE_THREAD_LOG
}IMAGE_THREAD_TYPE;
typedef enum
{
  IMAGE_RESIZE_NEAREST=0,
  IMAGE_RESIZE_LINEAR,
  IMAGE_RESIZE_AREA,
  IMAGE_RESIZE_CUBIC
}IMAGE_RESIZE_TYPE;
/*图像二值化*/  
int Image_Threshold(Image* Oriimage,unsigned char thresholdvalue,unsigned char MaxValue,IMAGE_THREAD_TYPE method);
/*图像上/下采样*/
Image* Image_Resize(Image* OriImage,int target_width,int target_height,double fx,double fy,IMAGE_RESIZE_TYPE image_resize_type);


typedef struct
{
    VectorPt* Candidate_Line;
    unsigned int line_num;
}E_Lines;

//Image Proc Func
//插入点操作
bool insert_pt(E_Edge *arg1, E_Point2D  *arg2);
//找点操作
unsigned int find_pt(E_Edge *arg1, E_Point2D *arg2);
//清楚边的操作
bool E_Edge_Clear(E_Edge* arg1);
//边的结构
E_Edge* Init_E_Edge_Struct(void);
//插入边的操作
bool insert_edge(E_Edge_t *arg1, E_Edge *arg2);
//初始化边集合
E_Edge_t* Init_E_Edge_t_Struct(void);
//插入线操作
bool insert_line(E_Lines *arg1, E_Point2D* arg2);
//寻找线操作
bool find_line(E_Lines *arg1, E_Point2D* arg2);
//初始化线集合
E_Lines* Init_E_Lines_Struct(void);
//插入圆的操作
bool insert_circle(E_Circles *arg1, E_Point3D* arg2);
//初始化圆集合
E_Circles* Init_E_Circles_Struct(void);
//轮廓提出
int E_Contour_extract(Image* InputImage, Image* OutputImage);
//轮廓追踪
E_Edge_t* E_Contour_track(Image* InputImage);
//LSF拟合圆
E_Circle* E_LeastSquareFittingCircle(E_Edge* edge);
//霍夫直线
int E_HoughLines(Image* InputImage, E_Lines* m_lines, double rho, double theta, int threshold);
//圆的选择操作
int E_SelectCircle(E_Circle* InputCircles,E_Edge* InputEdge);
//计算点到点的距离函数
int E_CacuPtDistance(E_Point2D* m_pt1,E_Point2D* m_pt2);
int E_FindMaxValue(unsigned int *Array, int start_pos,int stop_pos);
int E_Contour_extractSimple(Image *InputImage, Image *OutputImage);
E_Circle *E_SimpleCircleByArea(Image *edgeImage,Image *meanImage,int area_index,int scale);
int  E_FastCornerDetection(Image *Oriimage,Image *OutputImage,int blur_threshold_value,int scale);
int  E_TestNewCornerDection(Image *Oriimage,Image *OutputImage,int blur_thresholdvalue,int scale);
E_Circle *E_FastCornerDetectionByNineArea(Image *Oriimage,Image *OutputImage,int blur_threshold_value,int scale,int min_radius,int max_radius);
E_Circle *E_FastCircleDetection(int candidate_pts[][2],int pts_nums);
E_Circle * E_FastDetectAttentionPoint(Image *Oriimage,Image* OutputImage,int scale,int min_radius,int max_radius);
E_Circle *E_RANSACCircleDetection(int candidate_pts[][2],int pts_nums,int min_radius,int max_radius);
E_Circle *E_SimpleCircleByFastCircle(Image *edgeImage,int area_index);
E_Circle *E_SimpleCircleByNineArea(Image* EdgeImage,int left_x,int left_y,int right_x,int right_y,int min_radius,int max_radius);
void E_QuickSortArray(int *array, int left, int right);
#endif
