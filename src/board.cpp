#include "board.h"

Board::Board(std::vector<std::vector<char>> image_classifications) {
  test_ = image_classifications;
}

// WIP method to determine if a SET exists.
bool Board::FindSet() {
  int colors = 0, numbers = 0, shapes = 0, shadings = 0;
  //   int all_properties = 0;

  // TODO check individual properties or the sum?
  for (auto card : test_) {
    colors += card[0];
    numbers += card[1];
    shapes += card[2];
    shadings += card[3];
    // all_properties += std::accumulate(card.begin(), card.end(), 0);
  }

  // if all the properties are divisible by three there is a set.
  int all_properties = colors + numbers + shapes + shadings;
  int is_set = all_properties % 3;
  std::cout << all_properties << std::endl;
  return (is_set == 0 ? true : false);
}