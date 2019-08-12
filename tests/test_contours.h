#include <opencv2/opencv.hpp>
#include "gtest/gtest.h"

#include "../src/utils/image_contours.cpp"

TEST(CONTOURS, DIAMOND) {
  const std::vector<std::vector<cv::Point> > diamond_contour =
      LoadContour("./images/diamond2.png");

  ASSERT_EQ(diamond_contour.size(), 1);
  // cv::Mat contour_img = DrawContour(diamond_contour, cv::Size(600, 1200));
  // cv::imshow("diamond", contour_img);
  // cv::waitKey(0);
}

TEST(CONTOURS, OVAL) {
  const std::vector<std::vector<cv::Point> > diamond_contour =
      LoadContour("./images/oval2.png");

  ASSERT_EQ(diamond_contour.size(), 1);
  // cv::Mat contour_img = DrawContour(diamond_contour, cv::Size(600, 1200));
  // cv::imshow("diamond", contour_img);
  // cv::waitKey(0);
}

TEST(CONTOURS, SQUIGGLE) {
  const std::vector<std::vector<cv::Point> > diamond_contour =
      LoadContour("./images/squiggle2.png");

  ASSERT_EQ(diamond_contour.size(), 1);
  // cv::Mat contour_img = DrawContour(diamond_contour, cv::Size(900, 1200));
  // cv::imshow("diamond", contour_img);
  // cv::waitKey(0);
}