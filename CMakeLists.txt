cmake_minimum_required(VERSION 3.5.1)
project(gsm_modem)

add_compile_options(-std=c++11 -Wall -g)
set (INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include)
add_subdirectory(src)
add_subdirectory(examples)
