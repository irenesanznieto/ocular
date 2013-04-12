#CMAKEFILES: src/

add_subdirectory(libraries)

set(EXECUTABLE_OUTPUT_PATH ${RBCP_BIN_DIR})

add_executable(recognition main.cpp)

target_link_libraries(recognition functions)
TARGET_LINK_LIBRARIES( recognition ${OpenCV_LIBS} )


