#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "mergesort.h"


int int_gt_comparator(const void* a, const void* b) {
	return *(int*)a - *(int*)b;  // Сортировка массива по убыванию.
}

int char_gt_comparator(const void* a, const void* b){	
	return *(char*)a -  *(char*)b;
}

int str_gt_comparator(const void* a, const void* b){
	return strcmp(*(char**)a, *(char**)b);
}

void printf_int_element(void* element){
	printf("%d", *(int*)element);
	return;	
}

void printf_char_element(void* element){
	printf("%c", *(char*)element);
	return;
}

void printf_str_element(void* element){
	printf("%s", *(char**)element);
	return;
}

void printf_data(void* array,
	       	size_t elements,
	       	size_t element_size,
		void (*printf_element)(void* element)){

	for(size_t i = 0; i < elements; i++){
		char* now_elem = (char*)array + i * element_size;
		printf_element(now_elem);
		if(i != elements - 1) printf(" ");
	}

	printf("\n");
	return;
}


int main(int argc, char** argv){

	char* type = argv[1];
	
	int elements = argc - 2;
	
	if(elements == 0){
		printf("\n");
		return 0;
	}	

	char*  data[elements];

	for(int i = 0; i < elements; i++){
		data[i] = argv[i + 2];
	}

	if(!strcmp(type, "int")){
		int idata[elements];
	       	for(int i = 0; i < elements; i++){
			idata[i] = atoi(data[i]);
		}
		
		
		int flag = mergesort(idata, elements, sizeof(int), int_gt_comparator);
			
		assert(flag == 0 && "Error: memory allocation failed.");		

		printf_data(idata, elements, sizeof(int), printf_int_element);

		return 0;
	}

	if(!strcmp(type, "char")){
		char cdata[elements];
		for(int i = 0; i < elements; i++){
			cdata[i] = data[i][0]; 
		}
		
		mergesort(cdata, elements, sizeof(char), char_gt_comparator);
	
		printf_data(cdata, elements, sizeof(char), printf_char_element);
		
		return 0;
	}
	
	if(!strcmp(type, "str")){
					
		mergesort(data, elements, sizeof(char*), str_gt_comparator);
		
		printf_data(data, elements, sizeof(char*), printf_str_element);			
	
		return 0;
	}

	return 0;
}


