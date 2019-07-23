#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../src/load_image.cpp"
#include "../src/card.h"

TEST_CASE( "Determine Red Color", "[image]") {
  Card red_card = Card(LoadImg("./images/r_3_o_s_noBorder.jpg"));

  REQUIRE(red_card.DetermineColor() == 0);
}

TEST_CASE( "Determine Green Color", "[image]") {
  Card green_card = Card(LoadImg("./images/g_1_d_e_noBorder.png"));

  REQUIRE(green_card.DetermineColor() == 1);
}

TEST_CASE( "Determine Blue Color", "[image]") {
  Card blue_card = Card(LoadImg("./images/b_2_s_h_noBorder.png"));

  REQUIRE(blue_card.DetermineColor() == 2);
}