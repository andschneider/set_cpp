#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../src/ClassifyImage.cpp"
#include "../src/LoadImage.cpp"


TEST_CASE( "Determine color", "[image]" ) {
  cv::Mat red_img = loadImg("./images/r_3_o_f_noBorder.png");
  cv::Mat green_img = loadImg("./images/g_1_d_e_noBorder.png");
  cv::Mat blue_img = loadImg("./images/b_2_s_h_noBorder.png");

  REQUIRE(DetermineColor(red_img) == 0);
  REQUIRE(DetermineColor(green_img) == 1);
  REQUIRE(DetermineColor(blue_img) == 2);
}