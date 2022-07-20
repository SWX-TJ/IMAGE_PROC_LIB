#ifndef __EVECTOR_H__
#define __EVECTOR_H_
#include "image_engine.h"
typedef struct 
{
     int x;
     int y;
}E_Point2D;

typedef struct 
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
}E_Point3D;

typedef struct 
{
	void* element;
	int element_size;//ÿ��Ԫ��ռ�ڴ��С
	int allocatedSize;//�Ѿ�������ڴ��ܴ�С
	unsigned int total_size;//�����ܸ���
}VectorPt;

typedef struct 
{
	void* element;
	int element_size;//ÿ��Ԫ��ռ�ڴ��С
	int allocatedSize;//�Ѿ�������ڴ��ܴ�С
	unsigned int total_size;//�����ܸ���
}VectorPt3D;


//E_Point2d Func
VectorPt* Init_VectorPt(int elemSize);
E_Point2D* VectorPt_At(VectorPt* _vector, int index);
bool VectorPt_PushBack(VectorPt* _vector, void* element);
int VectorPt_TotalSize(VectorPt* _vector);
bool VectorPt_Search(VectorPt* _vector, void* element);
bool VectorPt_Clear(VectorPt* _vector);
//E_Point3D Func
VectorPt3D* Init_VectorPt3D(int elemSize);
E_Point3D* VectorPt3D_At(VectorPt3D* _vector, int index);
bool VectorPt3D_PushBack(VectorPt3D* _vector, void* element);
int VectorPt3D_TotalSize(VectorPt3D* _vector);
bool VectorPt3D_Search(VectorPt3D* _vector, void* element);

#endif // !__EVECTOR_H__

