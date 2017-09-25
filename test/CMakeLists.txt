find_package(Check REQUIRED)
add_executable(testexec test.c)
target_link_libraries(testexec lrsll ${CHECK_LIBRARIES} pthread)
ADD_TEST(UnitTests testexec)