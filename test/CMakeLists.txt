#add_executable(testexec test.c)
#target_link_libraries(testexec lrsll check m rt pthread)

add_executable(test_create_list test_create_list.c)
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})
message("Test libraries are ${CHECK_LIBRARIES}")
target_link_libraries(test_create_list lrsll ${CHECK_LIBRARIES} pthread)
