#include <opencv2/opencv.hpp>
#include <string>

#include "card.h"
#include "load_image.cpp"

int main(int argc, char *argv[]) {
  std::string filePath = argv[1];
  cv::Mat img = LoadImg(filePath, false);

  Card card = Card(img);
  card.ClassifyCard();

  std::vector<char> img_identifier = card.GetClassification();
  std::vector<std::string> img_string = card.GetCardInfo();

  std::cout << "  type |  color  |  number |  shape  |  shading " << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "vector |";
  for (int x : img_identifier) {
    std::cout << std::setw(8) << std::setfill(' ') << x << " |";
  }
  std::cout << '\n';
  std::cout << " human |";
  for (std::string x : img_string) {
    std::cout << std::setw(8) << std::setfill(' ') << x << " |";
  }
  std::cout << std::endl;  // flush before image pops up

  // card.ShowRgbImage();
  // card.ShowHsvImage();
  // card.ShowThreshImage();
  // card.ShowContourImage();

  card.DisplayText();
  cv::waitKey(0);

  return 0;
}