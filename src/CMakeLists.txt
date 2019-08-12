cmake_minimum_required(VERSION 3.5)
project( set_cpp )
add_compile_options(-std=c++11)

find_package( OpenCV REQUIRED )

add_executable( classifyCard main.cpp )
target_link_libraries( classifyCard ${OpenCV_LIBS} )

add_executable( threshImg utils/threshold_calibrator.cpp )
target_link_libraries( threshImg ${OpenCV_LIBS} )
