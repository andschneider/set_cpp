#include "gtest/gtest.h"

#include "../src/card.cpp"
#include "../src/load_image.cpp"

TEST(IMAGE_CLASSIFICATION, G_1_D_O_CARD) {
  Card green_card(LoadImg("./images/g_1_d_e_noBorder.png", false));
  green_card.ClassifyCard();
  std::vector<char> classification = {1, 0, 0, 0};

  ASSERT_EQ(green_card.GetColor(), 1);
  ASSERT_EQ(green_card.GetNumber(), 0);
  ASSERT_EQ(green_card.GetShape(), 0);
  ASSERT_EQ(green_card.GetShading(), 0);
  ASSERT_EQ(green_card.GetClassification(), classification);
}

TEST(IMAGE_CLASSIFICATION, P_2_S_H_CARD) {
  Card purple_card(LoadImg("./images/p_2_s_h_noBorder.jpg", false));
  purple_card.ClassifyCard();
  std::vector<char> classification = {2, 1, 2, 2};

  ASSERT_EQ(purple_card.GetColor(), 2);
  ASSERT_EQ(purple_card.GetNumber(), 1);
  ASSERT_EQ(purple_card.GetShape(), 2);
  ASSERT_EQ(purple_card.GetShading(), 2);
  ASSERT_EQ(purple_card.GetClassification(), classification);
}

TEST(IMAGE_CLASSIFICATION, R_3_O_S_CARD) {
  Card red_card(LoadImg("./images/r_3_o_s_noBorder.jpg", false));
  red_card.ClassifyCard();
  std::vector<char> classification = {0, 2, 1, 1};

  ASSERT_EQ(red_card.GetColor(), 0);
  ASSERT_EQ(red_card.GetNumber(), 2);
  ASSERT_EQ(red_card.GetShape(), 1);
  ASSERT_EQ(red_card.GetShading(), 1);
  ASSERT_EQ(red_card.GetClassification(), classification);
}

TEST(IMAGE_CLASSIFICATION, R_3_O_S_CARD_SIMPLE) {
  Card red_card(LoadImg("./images/r_3_o_s_noBorder.jpg", false));
  red_card.ClassifyCard();

  std::vector<char> classification = {0, 2, 1, 1};
  ASSERT_EQ(red_card.GetClassification(), classification);
}