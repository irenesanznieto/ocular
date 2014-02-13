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
rosbuild_add_executable(featureextractor2D src/apps/featureextractor2D.cpp)
rosbuild_add_executable(featureextractor3D src/apps/featureextractor3D.cpp)
#rosbuild_add_executable(data_parser src/apps/data_parser.cpp)
#rosbuild_add_executable(display src/apps/display.cpp)

rosbuild_add_executable(image_view src/apps/image_view.cpp)


#LIBRARIES: 
FILE(GLOB LIBRARIES_SRCS src/libraries/libraries/*.cpp src/libraries/nodes/*.cpp)
rosbuild_add_library(custom_libs ${LIBRARIES_SRCS})

#FILE(GLOB LIBRARIES_SRCS src/libraries/libraries/other/*.cpp)
#rosbuild_add_library(other_libs ${LIBRARIES_SRCS})

#LINKING:
target_link_libraries(recognizer custom_libs)
target_link_libraries(learner custom_libs)
#target_link_libraries(event_handler custom_libs)
target_link_libraries(converter custom_libs)
target_link_libraries(roi_segmenter2D custom_libs)
target_link_libraries(roi_segmenter3D custom_libs)
target_link_libraries(featureextractor2D custom_libs)
target_link_libraries(featureextractor3D custom_libs)
#target_link_libraries(data_parser custom_libs)
#target_link_libraries(display custom_libs)

#GTESTS:
rosbuild_add_gtest(TestConverter src/tests/ConverterTest.cpp)
rosbuild_add_gtest(TestROISegmenter3D src/tests/RoiSegmenter3DTest.cpp)
rosbuild_add_gtest(TestROISegmenter2D src/tests/RoiSegmenter2DTest.cpp)

target_link_libraries(TestROISegmenter3D custom_libs)
target_link_libraries(TestROISegmenter2D custom_libs)
target_link_libraries(TestConverter custom_libs)
