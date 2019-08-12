#include <gtest/gtest.h>

#include "test_board.h"
#include "test_card_classifiers.h"
#include "test_image_loading.h"
#include "test_contours.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}