#include <vector>
#include "gtest/gtest.h"

#include "../src/board.h"

TEST(SET_CALCS, SET) {
  std::vector<char> g_1_d_o = {1, 0, 0, 0};
  std::vector<char> p_2_s_h = {2, 1, 2, 2};
  std::vector<char> r_3_o_s = {0, 2, 1, 1};

  std::vector<std::vector<char>> cards{g_1_d_o, p_2_s_h, r_3_o_s};

  Board test_board = Board(cards);
  bool is_set = test_board.FindSet();
  ASSERT_EQ(is_set, true);
}

TEST(SET_CALCS, NO_SET) {
  std::vector<char> g_1_d_s = {1, 0, 0, 1};
  std::vector<char> p_2_s_h = {2, 1, 2, 2};
  std::vector<char> r_3_o_s = {0, 2, 1, 1};

  std::vector<std::vector<char>> cards{g_1_d_s, p_2_s_h, r_3_o_s};

  Board test_board = Board(cards);
  bool is_set = test_board.FindSet();
  ASSERT_EQ(is_set, false);
}