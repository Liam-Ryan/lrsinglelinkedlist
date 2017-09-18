#add_executable(testexec test.c)
#target_link_libraries(testexec lrsll check m rt pthread)

add_executable(test_create_list test_create_list.c)
target_link_libraries(test_create_list lrsll check m rt pthread)
