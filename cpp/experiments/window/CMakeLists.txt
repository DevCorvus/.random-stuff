cmake_minimum_required(VERSION 3.10)
project(my_app_project)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(my_app main.cpp)

target_link_libraries(my_app OpenGL glfw)

