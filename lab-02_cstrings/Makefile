CC_FLAGS := -Wall -Werror -Wextra -I include

.PHONY: all clean

all: lab_02

obj:
		mkdir obj

lab_02: obj/str.o obj/test_str.o obj/test.o 
		gcc $(CC_FLAGS) -o lab_02 obj/str.o obj/test_str.o obj/test.o


obj/str.o : src/str.c include/str.h | obj
		gcc $(CC_FLAGS) -c src/str.c -o obj/str.o 

obj/test_str.o : src/test_str.c include/str.h include/test_str.h | obj
		gcc $(CC_FLAGS)  -c src/test_str.c -o obj/test_str.o

obj/test.o : src/test.c include/test_str.h | obj
		gcc $(CC_FLAGS) -c src/test.c -o obj/test.o

clean: 
		rm -rf obj

