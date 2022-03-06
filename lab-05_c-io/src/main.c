#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "clist.h"
#include "point_list.h"


void op_print(struct intrusive_node* node, void* data){
	if(node == NULL){
		printf("\n");
		return;
	}

	struct point* pt = get_point(node);
	printf((char*)data, pt->x, pt->y);
	return;
}


void op_count(struct intrusive_node* node, void* data){
	static size_t count = 0;
	if((char*)data){}  // unused data


	if(node == NULL){
		printf("%ld\n", count);
		return;
	}
	count++;

	return;
}


struct request{
	char* load_type;
	char* path_to_infile;
	char* action;
	char* data;
};


void read_text_file(char* path_to_file, struct intrusive_list* list){
	FILE* fin = fopen(path_to_file, "r");
	int x, y;
	while(fscanf(fin, "%d %d", &x, &y) != EOF)  add_point(list, x, y);
	fclose(fin);
	return;
}


void read_bin_file(char* path_to_file, struct intrusive_list* list){
	FILE* fin = fopen(path_to_file, "rb");	
	
	int* x = malloc(sizeof(int));
	memset(x, 0, sizeof(int));
	int* y = malloc(sizeof(int));
	memset(y, 0, sizeof(int));

	while(fread(x, 3, 1, fin)){
		if(feof(fin))return;
		
		fread(y, 3, 1, fin);
		add_point(list, *x, *y);
	}
	free(x);
	free(y);

	fclose(fin);

	return;
}


void op_save_text(struct intrusive_node* node, void* data){	
	static char* outfile = NULL;
	if(outfile == NULL) outfile = (char*)data;
	
	static FILE* fout = NULL;
	if(fout == NULL)fout = fopen(outfile, "w");	
	
	if(node == NULL){
		fclose(fout);
		return;	
	}

	struct point* pt = get_point(node);
	fprintf(fout, "%d %d\n", pt->x, pt->y);
	
	return;
}




void op_save_bin(struct intrusive_node* node, void* data){	
	static char* outfile = NULL;
	if(outfile == NULL) outfile = (char*)data;
	
	static FILE* fout = NULL;
	if(fout == NULL)fout = fopen(outfile, "wb");	
	
	if(node == NULL){
		fclose(fout);
		return;	
	}

	struct point* pt = get_point(node);
	fwrite(&pt->x, 1, 3, fout);
	fwrite(&pt->y, 1, 3, fout);
	
	return;
}


int main(int argc, char** argv) {	
     	argc++; // unused val
	
	struct intrusive_list intr_list;
    	init_list(&intr_list);
	
	struct request* req = malloc(sizeof(struct request));
	req->load_type = argv[1];
	req->path_to_infile = argv[2];
	req->action = argv[3];
	req->data = NULL;
	
	// load file
	
	if(!strcmp(req->load_type, "loadtext")){
		read_text_file(req->path_to_infile, &intr_list);
	}


	
	if(!strcmp(req->load_type, "loadbin")){
		read_bin_file(req->path_to_infile, &intr_list);
	}

	// action 
	
	if(!strcmp(req->action, "savetext")){
		req->data = argv[4];
		apply(&intr_list, op_save_text, req->data);	
	}
	
	if(!strcmp(req->action, "savebin")){
		req->data = argv[4];		
		apply(&intr_list, op_save_bin, req->data);	
	}
	if(!strcmp(req->action, "print")){
		req->data = argv[4];
		apply(&intr_list, op_print, req->data);
	}

	if(!strcmp(req->action, "count")){
		apply(&intr_list, op_count, req->data);
	}
	
	// fix leek
	free(req);
	remove_all_points(&intr_list);
	free(intr_list.head);
			

	return 0;
}


