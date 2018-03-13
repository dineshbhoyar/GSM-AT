include_directories(${INCLUDES})
aux_source_directory(. SRC_LIST)
add_library(gsm STATIC ${SRC_LIST})