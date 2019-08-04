#include "gtest/gtest.h"

#include "../src/card.h"
#include "../src/load_image.cpp"

TEST(IMAGE_CLASSIFICATION, G_1_D_O_CARD) {
  Card green_card = Card(LoadImg("./images/g_1_d_e_noBorder.png", false));
  std::vector<char> classification = {1, 0, 0, 0};

  ASSERT_EQ(green_card.DetermineColor(), 1);
  ASSERT_EQ(green_card.DetermineNumber(), 0);
  ASSERT_EQ(green_card.DetermineShape(), 0);
  ASSERT_EQ(green_card.DetermineShading(), 0);
  ASSERT_EQ(green_card.GetClassification(), classification);
}

TEST(IMAGE_CLASSIFICATION, P_2_S_H_CARD) {
  Card purple_card = Card(LoadImg("./images/p_2_s_h_noBorder.jpg", false));
  std::vector<char> classification = {2, 1, 2, 2};

  ASSERT_EQ(purple_card.DetermineColor(), 2);
  ASSERT_EQ(purple_card.DetermineNumber(), 1);
  ASSERT_EQ(purple_card.DetermineShape(), 2);
  ASSERT_EQ(purple_card.DetermineShading(), 2);
  ASSERT_EQ(purple_card.GetClassification(), classification);
}

TEST(IMAGE_CLASSIFICATION, R_3_O_S_CARD) {
  Card red_card = Card(LoadImg("./images/r_3_o_s_noBorder.jpg", false));
  std::vector<char> classification = {0, 2, 1, 1};

  ASSERT_EQ(red_card.DetermineColor(), 0);
  ASSERT_EQ(red_card.DetermineNumber(), 2);
  ASSERT_EQ(red_card.DetermineShape(), 1);
  ASSERT_EQ(red_card.DetermineShading(), 1);
  ASSERT_EQ(red_card.GetClassification(), classification);
}

TEST(IMAGE_CLASSIFICATION, R_3_O_S_CARD_SIMPLE) {
  Card red_card = Card(LoadImg("./images/r_3_o_s_noBorder.jpg", false));
  red_card.ClassifyCard();

  std::vector<char> classification = {0, 2, 1, 1};
  ASSERT_EQ(red_card.GetClassification(), classification);
}