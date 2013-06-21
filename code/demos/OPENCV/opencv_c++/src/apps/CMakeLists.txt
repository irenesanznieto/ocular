#CMAKELISTS: src/apps

set(EXECUTABLE_OUTPUT_PATH ${RBCP_BIN_DIR})

###################################################

add_executable(static_matching static_matching.cpp)

target_link_libraries(static_matching functions)

TARGET_LINK_LIBRARIES( static_matching ${OpenCV_LIBS} )


###################################################

add_executable(templates templates.cpp)

target_link_libraries(templates functions)

TARGET_LINK_LIBRARIES( templates ${OpenCV_LIBS} )


###################################################


add_executable(images_matching images_matching.cpp)

target_link_libraries(images_matching functions)

TARGET_LINK_LIBRARIES(images_matching ${OpenCV_LIBS} )


##################################################

add_executable(no_background no_background.cpp)

target_link_libraries(no_background functions)

TARGET_LINK_LIBRARIES(no_background ${OpenCV_LIBS} )
