#include <stdio.h>
#include <assert.h>

#include "test_str.h"


int main(){
	

	printf("\nStart test: my_strcpy\n");
	test_my_strcpy();
	printf("Succuessful pass test: my_strcpy\n\n");

      	printf("Start test: my_strcat\n");
	test_my_strcat();
	printf("Succuessful pass test: my_strcat\n\n");
	printf("Start test: my_strcmp\n");
	test_my_strcmp();
	printf("Succuessful pass test: my_strcmp\n\n");
	printf("Start test: my_strlen\n");
	test_my_strlen();
	printf("Succuessful pass test: my_strlen\n\n");												
	return 0;
}

