#include "gtest/gtest.h"

#include "../src/card.h"
#include "../src/load_image.cpp"

TEST(IMAGE_CLASSIFICATION, G_1_D_O_CARD) {
  Card green_card = Card(LoadImg("./images/g_1_d_e_noBorder.png", false));

  ASSERT_EQ(green_card.DetermineColor(), 1);
  ASSERT_EQ(green_card.DetermineNumber(), 0);
  ASSERT_EQ(green_card.DetermineShape(), 0);
  ASSERT_EQ(green_card.DetermineShading(), 0);
}

TEST(IMAGE_CLASSIFICATION, P_2_S_H) {
  Card purple_card = Card(LoadImg("./images/p_2_s_h_noBorder.jpg", false));

  ASSERT_EQ(purple_card.DetermineColor(), 2);
  ASSERT_EQ(purple_card.DetermineNumber(), 1);
  ASSERT_EQ(purple_card.DetermineShape(), 2);
  ASSERT_EQ(purple_card.DetermineShading(), 2);
}

TEST(IMAGE_CLASSIFICATION, R_3_O_S_CARD) {
  Card red_card = Card(LoadImg("./images/r_3_o_s_noBorder.jpg", false));

  ASSERT_EQ(red_card.DetermineColor(), 0);
  ASSERT_EQ(red_card.DetermineNumber(), 2);
  ASSERT_EQ(red_card.DetermineShape(), 1);
  ASSERT_EQ(red_card.DetermineShading(), 1);
}
