find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})
message("Test libraries are ${CHECK_LIBRARIES}")

add_executable(testexec test.c)
target_link_libraries(testexec lrsll ${CHECK_LIBRARIES} pthread)
