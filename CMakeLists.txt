cmake_minimum_required(VERSION 3.5)
project( set_cpp )

find_package( OpenCV REQUIRED )

add_executable( dispImg src/Main.cpp )
target_link_libraries( dispImg ${OpenCV_LIBS} )

add_executable( threshImg src/ThresholdTester.cpp )
target_link_libraries( threshImg ${OpenCV_LIBS} )