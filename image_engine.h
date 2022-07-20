#ifndef __IMAGE_ENGINE_H__
#define __IMAGE_ENGINE_H__
#include "stdio.h"
#include "stdlib.h"
//#include "stdbool.h"
#include "string.h"
#include "assert.h"
#include "stdarg.h"
#include <math.h>
#include "arm_malloc.h"
/**图像库引擎v1.0****/
/*Author: 沈文祥*/
/*Edit time:2020.3.21*/
#define M_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define M_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define E_PI 3.1415926535897932384626433832795
#define HOUGH_RES_SHT	180
/*模块*/
#define USING_IMAGE_IO_MODULE     1
#define USING_IMAGE_FILTER_MODULE 0
#define USING_IMAGE_MATH_MODULE   0
#define USING_IMAGE_PROC_MODULE   0
//异常错误处理
typedef enum
{
 M_ERR_PTRNULL=0,
 M_ERR_None,
 M_ERR_WRITEERROR
}M_ErrMsg;
//bool
typedef int bool;
#define true 1
#define false 0
//内存分配相关,使用时需要替换为对应硬件的内存管理函数，默认是标准内存分配函数
void *M_Malloc(unsigned int size);
void M_Free(void *ptr);
void *M_Realloc(void *ptr,unsigned int size);
void M_Memset(void *s,unsigned char c,unsigned int count);
void M_Memcpy(void *des,void *src,unsigned int n);  
//初始化图像引擎

#endif