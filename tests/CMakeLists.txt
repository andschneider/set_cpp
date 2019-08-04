cmake_minimum_required(VERSION 3.5)
project( set_cpp )
add_compile_options(-std=c++11)

find_package( OpenCV REQUIRED )

add_executable(all_tests test_main.cpp)
target_link_libraries(all_tests gtest_main ${OpenCV_LIBS})
add_test(NAME all_tests COMMAND all_tests)