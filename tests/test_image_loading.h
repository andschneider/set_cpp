#include <opencv2/opencv.hpp>
#include "gtest/gtest.h"

#include "../src/utils/load_image.cpp"

TEST(IMAGE_LOADING, G_1_D_O_CARD) {
  cv::Mat image = LoadImg("./images/g_1_d_e_noBorder.png", false);

  ASSERT_EQ(image.type(), 16);  // CV_8U
  ASSERT_EQ(image.channels(), 3);
  // cv::imshow("rgb", image);
  // cv::waitKey(0);
}

TEST(IMAGE_LOADING, G_1_D_O_CARD_HSV) {
  cv::Mat image = LoadImg("./images/g_1_d_e_noBorder.png", true);

  ASSERT_EQ(image.type(), 16);  // CV_8U
  ASSERT_EQ(image.channels(), 3);
  // cv::imshow("hsv", image);
  // cv::waitKey(0);
}