CXX_FLAGS = -std=c++17 -Wall -Werror -Wextra -I include

.PHONY: all clean

all: lab-06_int-vector

obj:
	mkdir obj


lab-06_int-vector: obj/my_vector.o obj/main.o
	g++ $(CXX_FLAGS) -o lab-06_int-vector  obj/my_vector.o		obj/main.o

obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp  | obj
	g++ $(CXX_FLAGS) -c src/my_vector.cpp -o obj/my_vector.o	

obj/main.o: src/main.cpp include/my_vector.hpp | obj
	g++ $(CXX_FLAGS) -c src/main.cpp -o obj/main.o 

clean: 
	rm -rf obj



test: test_lab-06_int-vector

test_lab-06_int-vector: obj/my_vector.o 
	g++ $(CXX_FLAGS) -o test_lab-06_int-vector  obj/my_vector.o

obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp  | obj
	g++ $(CXX_FLAGS) -c src/my_vector.cpp -o obj/my_vector.o	
