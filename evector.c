#include "evector.h"
VectorPt* Init_VectorPt(int elemSize)
{
    VectorPt* _vector = (VectorPt*) M_Malloc(sizeof(VectorPt));
    assert(_vector != NULL);
    _vector->element_size = elemSize;
    _vector->allocatedSize = 50;
    _vector->total_size = 0;
    _vector->element = M_Malloc(_vector->element_size*_vector->allocatedSize);
    assert(_vector->element != NULL);
    return _vector;
}
static void VectorGrow(VectorPt* _vector) {
    _vector->element = M_Realloc(_vector->element,(_vector->allocatedSize + 10)*_vector->element_size);
    _vector->allocatedSize = _vector->allocatedSize + 10;
}

E_Point2D* VectorPt_At(VectorPt* _vector, int index)
{
    return ((E_Point2D*)_vector->element + index);
}

bool VectorPt_PushBack(VectorPt* _vector, void* element)
{
	  E_Point2D* destAddr;
    if (_vector->total_size == _vector->allocatedSize)
        VectorGrow(_vector);
   destAddr = (E_Point2D*)_vector->element + _vector->total_size ;
    destAddr->x = ((E_Point2D*)element)->x;
    destAddr->y = ((E_Point2D*)element)->y;
    _vector->total_size++;
    return true;
}
bool VectorPt_Search(VectorPt* _vector, void* element)
{
    int i = 0;
    for (; i < _vector->total_size; i++)
    {
        if (((E_Point2D*)element)->x == ((E_Point2D*)_vector->element + i * _vector->element_size)->x && ((E_Point2D*)element)->y == ((E_Point2D*)_vector->element + i * _vector->element_size)->y)
        {
            return true;
        }
    }
 
    return false;
}
bool VectorPt_Clear(VectorPt* _vector)
{
    _vector->total_size = 0;
	return true;
}
int VectorPt_TotalSize(VectorPt* _vector)
{
    return _vector->total_size;
}



VectorPt3D* Init_VectorPt3D(int elemSize)
{
    VectorPt3D* _vector = (VectorPt3D*)M_Malloc(sizeof(VectorPt3D*));
    assert(_vector != NULL);
    _vector->element_size = elemSize;
    _vector->allocatedSize = 100;
    _vector->total_size = 0;
    _vector->element = M_Malloc(_vector->element_size*_vector->allocatedSize);
    assert(_vector->element != NULL);
    return _vector;
}

E_Point3D* VectorPt3D_At(VectorPt3D* _vector, int index)
{
    assert(index >= 0);
    assert(index < _vector->total_size);
    return ((E_Point3D *)_vector->element + index);
}

static void Vector3DGrow(VectorPt3D* _vector) {
    _vector->element = M_Realloc(_vector->element, (_vector->allocatedSize + 1)*_vector->element_size);
    assert(_vector->element != NULL);
    _vector->allocatedSize = _vector->allocatedSize + 1;
}

bool VectorPt3D_PushBack(VectorPt3D* _vector, void* element)
{
	 E_Point3D* destAddr;
    if (_vector->total_size == _vector->allocatedSize)
        Vector3DGrow(_vector);
  destAddr = (E_Point3D*)_vector->element + _vector->total_size;
   destAddr->x = ((E_Point3D*)element)->x;
   destAddr->y = ((E_Point3D*)element)->y;
   destAddr->z = ((E_Point3D*)element)->z;
    _vector->total_size++;
    return true;
}

bool VectorPt3D_Search(VectorPt3D* _vector, void* element)
{
	int i = 0;
    for (; i < _vector->total_size; i++)
    {
        if (((E_Point3D*)element)->x == ((E_Point3D*)_vector->element + i * _vector->element_size)->x && ((E_Point3D*)element)->y == ((E_Point3D*)_vector->element + i * _vector->element_size)->y && ((E_Point3D*)element)->z == ((E_Point3D*)_vector->element + i * _vector->element_size)->z)
        {
            return true;
        }
    }
    return false;
}

int VectorPt3D_TotalSize(VectorPt3D* _vector)
{
    return _vector->total_size;
}
