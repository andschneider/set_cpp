#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

class Board {
 public:
  Board(std::vector<std::vector<char>> image_classifications);
  bool FindSet();

 private:
  std::vector<std::vector<char>> test_;
};

#endif