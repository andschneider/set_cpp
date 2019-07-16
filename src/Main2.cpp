#include <string>
#include <opencv2/opencv.hpp>

#include "LoadImage.cpp"
// #include "ClassifyImage.cpp"
#include "Card.h"

int main(int argc, char *argv[]) { 
    std::string filePath = argv[1];
    cv::Mat img = loadImg(filePath, false);

    Card card = Card(img);
    card.DetermineColor();
    card.DetermineNumber();
    card.DetermineShape();

    std::vector<char> img_identifier = card.GetClassification();
    std::vector<std::string> img_string = card.GetCardInfo();

    std::cout << "shape, color, number, shading" << std::endl;
    for (int x : img_identifier) {
      std::cout << x << " ";
    }
    std::cout << '\n';
    for (std::string x : img_string) {
      std::cout << x << " ";
    }
    std::cout << std::endl;  // flush before image pops up

    card.ShowRgbImage();
    card.ShowHsvImage();
    card.ShowThreshImage();
    card.ShowContourImage();

    cv::waitKey(0);

    return 0;
}