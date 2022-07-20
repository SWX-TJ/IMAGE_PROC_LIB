#include "arm_malloc.h"

unsigned char mem1base[MEM1_MAX_SIZE];

//AT_NONCACHEABLE_SECTION_ALIGN( uint8_t mem1base[MEM1_MAX_SIZE], 64);

unsigned short int  mem1mapbase[MEM1_ALLOC_TABLE_SIZE];													
  
const unsigned int memtblsize[SRAMBANK]={MEM1_ALLOC_TABLE_SIZE};			
const unsigned int  memblksize[SRAMBANK]={MEM1_BLOCK_SIZE};						     
const unsigned int  memsize[SRAMBANK]={MEM1_MAX_SIZE};								         


struct _m_mallco_dev mallco_dev=
{
	my_mem_init,				           
	my_mem_perused,				         
	mem1base,			         
	mem1mapbase,	      
	0  		 				           
};



void mymemcpy(void *des,void *src,unsigned int n)  
{  
	unsigned char *xdes=des;
	unsigned char *xsrc=src; 
	
	while(n--)*xdes++=*xsrc++;  
	
}  



void mymemset(void *s,unsigned char c,unsigned int count)  
{  
	unsigned char *xs = s;  


	while(count--)*xs++=c;  
	
}	   


void my_mem_init(unsigned char memx)  
{  
	mymemset(mallco_dev.memmap[memx], 0,memtblsize[memx]*2); 
	mymemset(mallco_dev.membase[memx], 0,memsize[memx]);	 
	mallco_dev.memrdy[memx]=1;								
}  



unsigned char my_mem_perused(unsigned char memx)  
{  
	unsigned int used=0;  
	unsigned int i;  
	
	
	for(i=0;i<memtblsize[memx];i++)  
	{  
			if(mallco_dev.memmap[memx][i])used++; 
	} 
	
	return (used*100)/(memtblsize[memx]);  
	
}  


unsigned int my_mem_malloc(unsigned char memx,unsigned int size)  
{  
	signed long offset=0;  
	unsigned int nmemb;
	unsigned int cmemb=0;
	unsigned int i;  
	
	
	if(!mallco_dev.memrdy[memx])mallco_dev.init(memx);
	
	if(size==0)
		return 0XFFFFFFFF;
	
	nmemb=size/memblksize[memx];  
	
	if(size%memblksize[memx])nmemb++; 
	
	for(offset=memtblsize[memx]-1;offset>=0;offset--) 
	{     
		if(!mallco_dev.memmap[memx][offset])cmemb++;
		else cmemb=0;								
		
		if(cmemb==nmemb)							
		{
			for(i=0;i<nmemb;i++)  				
			{  
					mallco_dev.memmap[memx][offset+i]=nmemb;  
			}  
			return (offset*memblksize[memx]);
		}
		
	}  
	
	return 0XFFFFFFFF;
	
}  


unsigned char my_mem_free(unsigned char memx,unsigned int offset)  
{  
	int i;  
	
	
	if(!mallco_dev.memrdy[memx])
	{
	mallco_dev.init(memx);    
			return 1; 
	}  
	
	if(offset<memsize[memx])
	{  
			int index=offset/memblksize[memx];			
			int nmemb=mallco_dev.memmap[memx][index];	
			for(i=0;i<nmemb;i++)  						
			{  
					mallco_dev.memmap[memx][index+i]=0;  
			}  
			return 0;  
	}
	else 
		return 2;
	
}  



void myfree(unsigned char memx,void *ptr)  
{  
	unsigned int offset;   
	
	
	if(ptr==NULL)return;
	offset=(unsigned int)ptr-(unsigned int)mallco_dev.membase[memx];     
	my_mem_free(memx,offset);	   
	
}  



void *mymalloc(unsigned char memx,unsigned int size)  
{  
	unsigned int offset;   
	
	
	offset=my_mem_malloc(memx,size);  	   	 
	
	if(offset==0XFFFFFFFF)return NULL;  
	else return (void*)((unsigned int)mallco_dev.membase[memx]+offset);  
	
}  


void *myrealloc(unsigned char memx,void *ptr,unsigned int size)  
{  
	unsigned int offset;    
	
	
	offset=my_mem_malloc(memx,size);   	
	if(offset==0XFFFFFFFF)return NULL;     
	else  
	{  									   
		mymemcpy((void*)((unsigned int)mallco_dev.membase[memx]+offset),ptr,size);	
		myfree(memx,ptr);  											  		
		return (void*)((unsigned int)mallco_dev.membase[memx]+offset);  			
	}  
	
}