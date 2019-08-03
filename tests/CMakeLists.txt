cmake_minimum_required(VERSION 3.5)
project( set_cpp )
add_compile_options(-std=c++11)

find_package( OpenCV REQUIRED )

add_executable(testClassifiers test_card_classifiers.cpp)
target_link_libraries(testClassifiers gtest_main ${OpenCV_LIBS})
add_test(NAME testClassifiers COMMAND testClassifiers)