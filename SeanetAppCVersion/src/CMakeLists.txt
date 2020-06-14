project(src)
aux_source_directory(./ SRC_FILES)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})