#ifndef __CLIST_H__
#define __CLIST_H__

struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
};

struct intrusive_list {
  struct intrusive_node* head;
};

void  init_list(struct intrusive_list* );
void  add_node(struct intrusive_list*, struct intrusive_node*);
void  remove_node(/*struct intrusive_list*,*/ struct intrusive_node*);

int get_length(struct intrusive_list*);


void apply(struct intrusive_list*,
		void (*op)(struct intrusive_node* , void* ),
		void* );







#endif

