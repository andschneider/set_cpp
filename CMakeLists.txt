cmake_minimum_required(VERSION 3.5)
project( set_cpp )
add_compile_options(-std=c++11)

find_package( OpenCV REQUIRED )

add_executable( classifyCard src/Main2.cpp )
target_link_libraries( classifyCard ${OpenCV_LIBS} )

add_executable( threshImg src/ThresholdTester.cpp )
target_link_libraries( threshImg ${OpenCV_LIBS} )

add_executable( runTests tests/TestCard.cpp )
target_link_libraries( runTests ${OpenCV_LIBS} )