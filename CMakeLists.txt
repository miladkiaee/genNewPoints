cmake_minimum_required(VERSION 3.7)
project(genNewPoints)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Point.cpp Point.h BSpline.cpp BSpline.h PtsLis.cpp PtsLis.h DepResult.cpp DepResult.h ResultMatrix.cpp ResultMatrix.h Manager.cpp Manager.h)
add_executable(genNewPoints ${SOURCE_FILES})