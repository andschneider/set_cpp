#include "gtest/gtest.h"


TEST(ThisIsATest, TestOne) { 
    int result = 2 + 2;

  ASSERT_EQ(4, result);
}