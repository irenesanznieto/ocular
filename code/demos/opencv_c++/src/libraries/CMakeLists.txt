#CMAKEFILES: src/libraries

FILE(GLOB LIBRARIES_SRCS *.cpp)

add_library(functions ${LIBRARIES_SRCS})

add_subdirectory(ORB)

