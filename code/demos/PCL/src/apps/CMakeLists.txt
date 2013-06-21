#CMAKELISTS: main/src/apps

add_executable (point_cloud_compression point_cloud_compression.cpp)
target_link_libraries (point_cloud_compression ${PCL_LIBRARIES})



