#ifndef __POINT_LIST_H__

#define __POINT_LIST_H__


struct point {
	int x, y;
	struct intrusive_node node;
};

void  add_point(struct intrusive_list* , int , int );

struct point* get_point(struct intrusive_node* );

void remove_point(struct intrusive_list* , int , int );

void  show_all_points(struct intrusive_list* );

void  remove_all_points(struct intrusive_list* list);	


#endif 
