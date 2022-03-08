cmake_minimum_required(VERSION  3.16.3)
project(lab_07_matrix)

set(MAKE_STANDARD 16.3)

include_directories(include)

add_executable(lab_07_matrix src/main.cpp src/matrix.cpp include/matrix.h)
