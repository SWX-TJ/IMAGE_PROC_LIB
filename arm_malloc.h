#ifndef  __ARM_MALLOC_H__
#define __ARM_MALLOC_H__

#ifndef NULL
#define NULL 0
#endif

#define SRAMIN	 0		
// #define SRAMEX   1		
#define SRAMBANK 	1	 

#define MEM1_BLOCK_SIZE			64//32  	  						             
#define MEM1_MAX_SIZE			  640*480*600 						             
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 

struct _m_mallco_dev
{
	void    ( * init ) ( unsigned char );			
	unsigned char ( * perused ) ( unsigned char );	
	unsigned char  * membase [ SRAMBANK ];		 
	unsigned short int * memmap [ SRAMBANK ]; 		  
	unsigned char    memrdy [ SRAMBANK ]; 			
};
extern struct _m_mallco_dev mallco_dev;	 


void mymemset(void *s,unsigned char c,unsigned int count);	   
void mymemcpy(void *des,void *src,unsigned int n);       
void my_mem_init(unsigned char memx);				               
unsigned int my_mem_malloc(unsigned char memx,unsigned int size);	 
unsigned char my_mem_free(unsigned char memx,unsigned int offset);		
unsigned char my_mem_perused(unsigned char memx);				       



void myfree(unsigned char memx,void *ptr);  			         
void *mymalloc(unsigned char memx,unsigned int size);			      
void *myrealloc(unsigned char memx,void *ptr,unsigned int size); 
#endif