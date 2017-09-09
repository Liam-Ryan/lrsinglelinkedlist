set(SOURCE_FILES lrsll.c lrsll.h)
add_library(lrsll ${SOURCE_FILES})
target_include_directories(lrsll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})