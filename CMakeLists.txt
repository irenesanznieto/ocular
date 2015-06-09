cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)


#rosbuild_find_ros_package(actionlib_msgs)
#include(${actionlib_msgs_PACKAGE_PATH}/cmake/actionbuild.cmake)
#genaction()

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()
# rosbuild_find_ros_package(sensor_msgs)
# rosbuild_find_ros_package(geometry_msgs)


#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

include_directories(${PCL_INCLUDE_DIRS})

add_definitions(-DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example example/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#EXECUTABLES: 
rosbuild_add_executable(path_finder src/apps/path_finder.cpp)

rosbuild_add_executable(converter src/apps/converter.cpp)
rosbuild_add_executable(roi_segmenter2D	src/apps/roi_segmenter2D.cpp)
rosbuild_add_executable(roi_segmenter3D	src/apps/roi_segmenter3D.cpp)
rosbuild_add_executable(featureextractor2D src/apps/featureextractor2D.cpp)
rosbuild_add_executable(featureextractor3D src/apps/featureextractor3D.cpp)

#rosbuild_add_executable(recognizer src/apps/recognizer.cpp)
#rosbuild_add_executable(learner src/apps/learner.cpp)
rosbuild_add_executable(event_handler src/apps/event_handler.cpp)

rosbuild_add_executable(learner_recognizer src/apps/learner_recognizer.cpp)

#rosbuild_add_executable(dummy src/tests/dummy.cpp)
rosbuild_add_executable(image_view src/apps/image_view.cpp)



#LIBRARIES: 
FILE(GLOB LIBRARIES_SRCS src/libraries/libraries/*.cpp src/libraries/nodes/*.cpp)
rosbuild_add_library(custom_libs ${LIBRARIES_SRCS})
target_link_libraries(custom_libs ${OpenCV_LIBS} ${PCL_LIBRARIES})


#LINKING:
target_link_libraries(path_finder custom_libs)

target_link_libraries(converter custom_libs)
target_link_libraries(roi_segmenter2D custom_libs)
target_link_libraries(roi_segmenter3D custom_libs)
target_link_libraries(featureextractor2D custom_libs)
target_link_libraries(featureextractor3D custom_libs)


#target_link_libraries(recognizer custom_libs)
#target_link_libraries(learner custom_libs)
target_link_libraries(event_handler custom_libs)

target_link_libraries(learner_recognizer custom_libs)

#target_link_libraries(dummy custom_libs)

#GTESTS:
rosbuild_add_gtest(TestConverter src/tests/ConverterTest.cpp)
rosbuild_add_gtest(TestROISegmenter3D src/tests/RoiSegmenter3DTest.cpp)
rosbuild_add_gtest(TestROISegmenter2D src/tests/RoiSegmenter2DTest.cpp)
rosbuild_add_gtest(TestFeatureExtractor2D src/tests/FeatureExtractor2DTest.cpp)

rosbuild_add_gtest(TestAlgorithm2D src/tests/Algorithm2DTest.cpp)
rosbuild_add_gtest(TestAlgorithm3D src/tests/Algorithm3DTest.cpp)
rosbuild_add_gtest(TestDataParser src/tests/DataParserTest.cpp)
rosbuild_add_gtest(TestFeatureExtractor3D src/tests/FeatureExtractor3DTest.cpp)
rosbuild_add_gtest(TestEventHandler src/tests/EventHandlerTest.cpp)



target_link_libraries(TestConverter custom_libs)
target_link_libraries(TestROISegmenter3D custom_libs)
target_link_libraries(TestROISegmenter2D custom_libs)
target_link_libraries(TestFeatureExtractor2D custom_libs)

target_link_libraries(TestAlgorithm2D  custom_libs)
target_link_libraries(TestAlgorithm3D  custom_libs)
target_link_libraries(TestDataParser custom_libs)
target_link_libraries(TestFeatureExtractor3D custom_libs)
target_link_libraries(TestEventHandler custom_libs)

