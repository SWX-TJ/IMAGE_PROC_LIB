#include "image_engine.h"
void *M_Malloc(unsigned int size)
{
    return mymalloc(0,size);
   // return malloc(size);
}
void M_Free(void *ptr)
{
    myfree(0,ptr);
   // free(ptr);
}
void *M_Realloc(void *ptr,unsigned int size)
{
    return myrealloc(0,ptr,size);
    //return realloc(ptr,size);
}
void M_Memset(void *s,unsigned char c,unsigned int count)
{
     mymemset(s,c,count);
     //memset(s,c,count);
}
void M_Memcpy(void *des,void *src,unsigned int n)
{
    mymemcpy(des,src,n);
   //  memcpy(des,src,n);
}