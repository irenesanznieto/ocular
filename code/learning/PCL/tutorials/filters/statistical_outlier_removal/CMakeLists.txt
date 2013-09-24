cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(statistical_removal)


find_package(PCL 1.5 REQUIRED COMPONENTS segmentation filters visualization)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

add_executable (statistical_removal main.cpp)
target_link_libraries (statistical_removal ${PCL_LIBRARIES})

