CC_FLAGS := -Wall -Werror -Wextra -I include

.PHONY: all clean

all: lab-03_mergesort

obj:
	mkdir obj


lab-03_mergesort: obj/main.o obj/mergesort.o
	gcc $(CC_FLAGS) -o lab-03_mergesort	 obj/main.o obj/mergesort.o

obj/main.o: src/main.c include/mergesort.h | obj
	gcc $(CC_FLAGS) -c src/main.c	 -o obj/main.o 

obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc $(CC_FLAGS) -c src/mergesort.c	 -o obj/mergesort.o


clean: 
	rm -rf obj




