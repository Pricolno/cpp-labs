#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "mergesort.h"

typedef int (*comp_t)(const void* , const void* );


void* shift_to(void* array, size_t element_size, size_t count){
	return (char*)array + count * element_size;
}



void swap(void* left, void* right, size_t element_size){
	char* cleft = (char*)left;
	char* cright = (char*)right;
	char buff;


	for(size_t i = 0; i < element_size; i++){	
		 buff = cleft[i];
		 cleft[i] = cright[i];
		 cright[i] = buff;
	}
}




int mergesort(void* array,
		size_t elements,
                size_t element_size,
                comp_t comporator){
	
	if(elements <= 1) return 0;

        size_t l = 0, r = elements;
	size_t m = (l + r)/ 2;
	
	int flag;	
	flag = mergesort(array, m, element_size, comporator);
	if(flag == -1) return -1;

	char* mid = (char*)shift_to(array, element_size, m);
	flag = mergesort(mid, r - m, element_size, comporator);
	if(flag == -1) return -1;

	void* result = malloc(elements * element_size);
	
	if(result == NULL)return -1;

	size_t cur1 = 0, cur2 = m;
	size_t cur_res = 0;
	while((cur1 < m) && (cur2 < r)){
		void* val1 = shift_to(array, element_size, cur1);
		void* val2 = shift_to(array, element_size, cur2);
		
		void* val_res = shift_to(result, element_size, cur_res);

		if(comporator(val1, val2) > 0){
			swap(val_res, val2, element_size);
			cur2++;
		}else{
			swap(val_res, val1, element_size);
			cur1++;
		}
		
		cur_res++;	

	}	

	while(cur1 < m){
		void* val1 = shift_to(array, element_size, cur1);
		void* val_res = shift_to(result, element_size, cur_res);
		swap(val_res, val1, element_size);
		cur1++;
		cur_res++;
	}

	while(cur2 < r){
		void* val2 = shift_to(array, element_size, cur2);
		void* val_res = shift_to(result, element_size, cur_res);
		swap(val_res, val2, element_size);
		cur2++;
		cur_res++;	
	}

	for(size_t i = l; i < r; i++){
		void* val_res = shift_to(result, element_size, i);
		void* val_arr = shift_to(array, element_size, i);
		swap(val_res, val_arr, element_size);

	}
	
	free(result);

	return 0;

}

		             

