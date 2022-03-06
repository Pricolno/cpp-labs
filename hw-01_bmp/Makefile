FLAGS = -Wall -Wextra -I include

.PHONY: all clean

all: hw-01_bmp

obj:
		mkdir obj;


hw-01_bmp: obj/bmp.o obj/main.o | obj
		gcc $(FLAGS) -o hw-01_bmp obj/bmp.o obj/main.o 

obj/bmp.o: include/bmp.h src/bmp.c | obj
		gcc $(FLAGS) -c src/bmp.c -o obj/bmp.o 

obj/main.o: include/bmp.h src/main.c | obj
		gcc $(FLAGS) -c src/main.c -o  obj/main.o

