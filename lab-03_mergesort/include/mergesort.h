#ifndef __MERGESORT_H__

#define __MERGESORT_H__

#include <stddef.h>

typedef int (*comp_t)(const void* , const void* );

int mergesort(void* ,
	        size_t ,
		size_t ,
		comp_t );


#endif 

