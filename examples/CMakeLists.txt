set (TARGET_NAME gsm_app)
add_custom_target(${TARGET_NAME}_clean COMMAND ${CMAKE_MAKE_PROGRAM} clean WORKING_DIRECTORY ${CMAKE_CURRENT_DIR})

include_directories(${INCLUDES})
aux_source_directory(. SRC_LIST)

add_executable(${TARGET_NAME} ${SRC_LIST})

set(LIBS -lrt -lpthread -lz ${CMAKE_CURRENT_SOURCE_DIR}/../src/libgsm.a) 
target_link_libraries(${TARGET_NAME} ${LIBS} ) 
