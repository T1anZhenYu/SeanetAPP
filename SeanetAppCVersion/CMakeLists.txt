cmake_minimum_required(VERSION 3.5)
project(SeanetAPP)
include_directories(./include ../SeaEP/SeaEp_C_Lib_test/include ../SEADP/seadp_test/lib)
add_subdirectory(./src)
add_executable(${PROJECT_NAME} main.c)
LINK_DIRECTORIES(../SEADP/seadp_test ../SeaEP/SeaEp_C_Lib_test)

