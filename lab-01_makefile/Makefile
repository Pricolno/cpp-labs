FLAGS:=-Werror -Wextra -I include



create: main

main: obj/main.o obj/algorithm.o obj/util.o obj/io.o
	gcc obj/main.o obj/algorithm.o obj/util.o obj/io.o -o main

obj:
	mkdir obj

obj/main.o: src/main.c include/logDebug.h include/doComputation.h include/max.h | obj
	gcc -c $(FLAGS) src/main.c -o obj/main.o
obj/algorithm.o: src/algorithm.c include/logDebug.h include/max.h include/doComputation.h | obj
	gcc -c $(FLAGS) src/algorithm.c -o obj/algorithm.o
obj/io.o: src/io.c include/logDebug.h | obj
	gcc -c $(FLAGS) src/io.c -o obj/io.o
obj/util.o: src/util.c include/logDebug.h include/max.h | obj
	gcc -c $(FLAGS) src/util.c -o obj/util.o    


clean:
	rm -rf main obj
