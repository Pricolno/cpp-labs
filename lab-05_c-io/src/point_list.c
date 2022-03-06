#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "clist.h"
#include "point_list.h"

#define container_of(ptr, type, member) \
	    (type*)((char*)(ptr) - offsetof(type, member))


struct point* create_point(int x_, int y_){
	struct point* pt = malloc(sizeof(struct point));
	pt->x = x_;
	pt->y = y_;

	return pt;
}


void  add_point(struct intrusive_list* list, int x_, int y_) {
	struct point* pt = create_point(x_, y_);
	add_node(list, &pt->node);
	return;
}


struct point* get_point(struct intrusive_node* cur){
	return container_of(cur, struct point, node);
}


void remove_point_(struct intrusive_node* node){
	remove_node(node);
	free(get_point(node));

	return;
}


void remove_point(struct intrusive_list* list, int x_, int y_) { // removes all (x, y) pairs
	struct intrusive_node* cur = list->head;
	cur = cur->next;
	while(cur){
		struct intrusive_node* now = cur;
		struct point* pt = get_point(cur);
		cur = cur->next;
		if(pt->x == x_ && pt->y == y_){
			remove_point_(now);
		}
	}

	return;
}


void  show_all_points(struct intrusive_list* list) {
	struct intrusive_node* cur = list->head;
	while(cur->next){
		cur = cur->next;
		struct point* pt = get_point(cur);
		printf("(%d %d)", pt->x, pt->y);
		if(cur->next) printf(" ");
	}
	printf("\n");

	return;
}


void  remove_all_points(struct intrusive_list* list) {
	struct intrusive_node* cur = list->head->next;

	while(cur){
		struct intrusive_node* now = cur;
		cur = cur->next;

		remove_point_(now);
	}
	return;
}

/*
int main() {
     	struct intrusive_list inst_list;
    	init_list(&inst_list);

	while(1){
		char data[239];
		scanf("%239s", data);
		if(!strcmp(data, "add")){
			int x, y;
			scanf("%d%d", &x, &y);
			add_point(&inst_list, x, y);
			continue;
		}

		if(!strcmp(data, "rm")){
			int x, y;
			scanf("%d%d", &x, &y);
			remove_point(&inst_list, x, y);
			continue;
		}

		if(!strcmp(data, "print")){
			show_all_points(&inst_list);
			continue;
		}

		if(!strcmp(data, "rma")){
			remove_all_points(&inst_list);
			continue;
		}

		if(!strcmp(data, "len")){
			printf("%d\n", get_length(&inst_list));
			continue;
		}

		if(!strcmp(data, "exit")){
			remove_all_points(&inst_list);
			free(inst_list.head);
			return 0;
		}

		printf("Unknown command\n");

	}

	return 0;
}
*/

