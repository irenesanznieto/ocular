#CMAKELISTS: src/apps

set(EXECUTABLE_OUTPUT_PATH ${RBCP_BIN_DIR})

add_executable(recognition main.cpp)

target_link_libraries(recognition functions)

TARGET_LINK_LIBRARIES( recognition ${OpenCV_LIBS} )


###################################################


add_executable(flann flann.cpp)

target_link_libraries(flann functions)

TARGET_LINK_LIBRARIES(flann ${OpenCV_LIBS} )
