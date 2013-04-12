#CMAKEFILES: src/libraries/ORB

FILE(GLOB LIBRARIES_SRCS *.cpp)

add_library(ORB ${LIBRARIES_SRCS})


