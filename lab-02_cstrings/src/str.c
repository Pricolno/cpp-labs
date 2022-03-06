#include "str.h"


char* my_strcpy(char* restrict s1, const char* restrict  s2){
	char* cur1 = (char*)s1;
	char* cur2 = (char*)s2;
	
	while(*cur2){
		*cur1 = *cur2;
		cur2++;
		cur1++;
	}

	*cur1 = '\0'; 
	return s1;	
}


char* my_strcat(char* restrict s1, const char* restrict s2){
	char* cur1 = (char*) s1;

	while(*cur1++);
	cur1--;

	my_strcpy(cur1, s2);
	
	return s1;
}


int my_strcmp(const char* s1, const char* s2){
	char* cur1 = (char*)s1;
	char* cur2 = (char*)s2;

	while(*cur1 == *cur2){
		if(!*cur1)return 0;
		cur1++;
		cur2++;
	}

	return *cur1 - *cur2;  
}


size_t my_strlen(const char* s){
	size_t len = 0;
	while(*s != 0){
		s++;
		len++;
	}
	return len;
}

