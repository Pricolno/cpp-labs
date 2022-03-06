CC_FLAGS := -Wall -Werror -Wextra -I include

.PHONY: all clean

all: lab-04_intrusive-list

obj:
	mkdir obj


lab-04_intrusive-list: obj/clist.o obj/main.o
	gcc $(CC_FLAGS) -o lab-04_intrusive-list  obj/clist.o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc $(CC_FLAGS) -c src/clist.c	 -o obj/clist.o 

obj/main.o: src/main.c include/clist.h | obj
	gcc $(CC_FLAGS) -c src/main.c -o obj/main.o


clean: 
	rm -rf obj

