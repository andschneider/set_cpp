cmake_minimum_required(VERSION 3.5)
project( set_cpp )
add_compile_options(-std=c++11)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example test_gtest.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)