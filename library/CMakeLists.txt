option(BUILD_SHARED_LIBS "build as shared libraries" OFF)
add_library(lrsll lrsll.c)
target_include_directories(lrsll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})