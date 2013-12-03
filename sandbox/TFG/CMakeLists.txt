cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example example/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#EXECUTABLES: 
rosbuild_add_executable(recognizer src/apps/recognizer.cpp)
rosbuild_add_executable(learner src/apps/learner.cpp)
#rosbuild_add_executable(event_handler src/apps/event_handler.cpp)
rosbuild_add_executable(converter src/apps/converter.cpp)
rosbuild_add_executable(roi_segmenter2D	src/apps/roi_segmenter2D.cpp)
rosbuild_add_executable(roi_segmenter3D	src/apps/roi_segmenter3D.cpp)
#rosbuild_add_executable(feature_extractor src/apps/feature_extractor.cpp)
#rosbuild_add_executable(data_parser src/apps/data_parser.cpp)
#rosbuild_add_executable(display src/apps/display.cpp)




#LIBRARIES: 
FILE(GLOB LIBRARIES_SRCS src/libraries/*.cpp)
rosbuild_add_library(custom_libs ${LIBRARIES_SRCS})


#LINKING:

target_link_libraries(recognizer custom_libs)
target_link_libraries(learner custom_libs)
#target_link_libraries(event_handler custom_libs)
target_link_libraries(converter custom_libs)
target_link_libraries(roi_segmenter2D custom_libs)
target_link_libraries(roi_segmenter3D custom_libs)
#target_link_libraries(feature_extractor custom_libs)
#target_link_libraries(data_parser custom_libs)
#target_link_libraries(display custom_libs)


