#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>

cv::Mat LoadImg(std::string, bool);

// Simple image loader from disk that converts to HSV color space.
cv::Mat LoadImg(std::string file_path, bool hsv = true) {
  cv::Mat input_image = cv::imread(file_path, 1);

  if (!input_image.data) {
    printf("No input_image data \n");
  }

  if (hsv) {
    cv::cvtColor(input_image, input_image, cv::COLOR_BGR2HSV);
  }
  return input_image;
}
