CC_FLAGS := -Wall -Werror -Wextra -I include

.PHONY: all clean

all: lab-05_c-io

obj:
	mkdir obj


lab-05_c-io: obj/clist.o obj/point_list.o obj/main.o
	gcc $(CC_FLAGS) -o lab-05_c-io  obj/clist.o  obj/point_list.o  obj/main.o

obj/clist.o: src/clist.c include/clist.h  | obj
	gcc $(CC_FLAGS) -c src/clist.c	 -o obj/clist.o 

obj/point_list.o: src/point_list.c include/point_list.h include/clist.h | obj
	gcc $(CC_FLAGS) -c src/point_list.c -o obj/point_list.o 

obj/main.o: src/main.c include/clist.h include/point_list.h | obj
	gcc $(CC_FLAGS) -c src/main.c -o obj/main.o


clean: 
	rm -rf obj


