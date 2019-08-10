#ifndef CARD_H_
#define CARD_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "save_contour.cpp"

class Card {
 public:
  Card(cv::Mat input_image);

  void ClassifyCard();

  int GetColor() { return color_id_; }
  int GetShape() { return shape_id_; }
  int GetNumber() { return num_id_; }
  int GetShading() { return shading_id_; }
  std::vector<char> GetClassification() { return classification_; }
  std::vector<std::string> GetCardInfo();

  void ShowRgbImage();
  void ShowHsvImage();
  void ShowThreshImage();
  void ShowContourImage();
  void DisplayText();

 private:
  void DetermineColor();
  void DetermineNumber();
  void DetermineShape();
  void DetermineShading();

  // card properties
  int shape_id_;
  int color_id_;
  int num_id_;
  int shading_id_;
  std::vector<char> classification_;

  // image stuff
  cv::Mat rgb_image_;
  cv::Mat hsv_image_;
  cv::Mat thresh_image_;
  cv::Mat contour_image_;
  std::vector<std::vector<cv::Point> > contours_;

  // humand readable SET options
  std::string colors_[3] = {"red", "green", "purple"};
  std::string shapes_[3] = {"diamond", "oval", "squiggle"};
  std::string shadings_[3] = {"outlined", "solid", "striped"};
  std::string numbers_[3] = {"1", "2", "3"};
};

#endif