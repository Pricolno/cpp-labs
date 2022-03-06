#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "str.h"
#include "test_str.h"


void test_my_strcpy(){
	char buffer_change[50];
	memset(buffer_change, '0', 50 * sizeof(char)); 
	
	char* buffer[] =  {"Hello", "foo", "good", "cat", "dog", ""};	
	
	for(size_t i=0; i < sizeof(buffer) / sizeof(buffer[0]); i++){	
		assert(!strcmp(my_strcpy(buffer_change, buffer[i]), buffer[i]));	
	}	
	
}


void test_my_strcat(){
	char buffer[][50] = {"Goodbye", "nothing", ""};
        char buffer_change[][50] = {"Hello", "", "a"};
	assert(!strcmp(my_strcat(buffer_change[0], buffer[0]), "HelloGoodbye"));
	assert(!strcmp(my_strcat(buffer_change[1], buffer[1]), "nothing"));
	assert(!strcmp(my_strcat(buffer_change[2], buffer[2]), "a"));
}


int sign(const int a){
	if(a == 0) return 0;
       	if(a > 0) return 1;
	else return -1;	
}


void test_my_strcmp(){
	char buffer1[][50] = {"Goodbye", "czt", "", "", "Hello"};
	char buffer2[][50] = {"Hello", "current", "", "a", "Hello"};
	int answer[] = {-1, 1, 0, -1, 0};
	for(size_t i=0; i < sizeof(buffer1) / sizeof(buffer1[0]); i++) {
		assert(sign(my_strcmp(buffer1[i], buffer2[i])) == answer[i]);
	}
}


void test_my_strlen(){
	assert(my_strlen("Hello") == 5);
	assert(my_strlen("") == 0);
	assert(my_strlen("a") == 1);
	size_t MAX_SIZE = 255;
	char long_str[MAX_SIZE];
	for(size_t i=0; i < MAX_SIZE - 1; i++){
		long_str[i] = 'a';
	}
	long_str[MAX_SIZE - 1] = '\0';

	assert(my_strlen(long_str) == MAX_SIZE - 1);
}


