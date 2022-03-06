#include <stdio.h>
#include <stdlib.h>

#include "clist.h"


void init_list(struct intrusive_list* list){
	list->head = malloc(sizeof(struct intrusive_node));
	list->head->next = NULL;	
	list->head->prev = NULL;
	return;
}


void connect_nodes(struct intrusive_node* left, struct intrusive_node* right){
	left->next = right;
	right->prev = left;
	return;
}


void add_node(struct intrusive_list* list, struct intrusive_node* node){
	if(list->head->next == NULL){
		connect_nodes(list->head, node);
		node->next = NULL;
		return;
	}
	
	connect_nodes(node, list->head->next);
	connect_nodes(list->head, node);
	
	return;
}


void  remove_node(/*struct intrusive_list*, */ struct intrusive_node* node){
	if(node->next == NULL){
		node->prev->next = NULL;
	}
	else{
		connect_nodes(node->prev, node->next);
	}
	
	return;	
}


int get_length(struct intrusive_list* list){
	struct intrusive_node* cur = list->head;
	int length = 0;
	while(cur->next){
		cur = cur->next;
		length++;
	}

	return length;
}


void printf_list(struct intrusive_list* list){
	struct intrusive_node* cur = list->head;
	while(cur){
		printf("%p\n", cur);
		cur = cur->next;
	}

	return;
}


void apply(struct intrusive_list* list,	
		void (*op)(struct intrusive_node* node, void* data),
	       	void* data){

	struct intrusive_node* cur = list->head;
	while(cur->next){
		cur = cur->next;
	}
	
	while(cur->prev){
		op(cur, data);
		cur = cur->prev;
	}

	op(NULL, data);

	return;

}


