cmake_minimum_required(VERSION 3.1)
project(Rani_Pokhari)

## main project files

set (files "main.cpp")
add_executable(${PROJECT_NAME} ${files})

file (GLOB sources src/*.cpp)

add_library(mylib ${sources})
target_include_directories(mylib PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE mylib)

#glut / freeglut
target_link_libraries(${PROJECT_NAME} PRIVATE glut GLU GL)