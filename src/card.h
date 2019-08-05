#ifndef CARD_H_
#define CARD_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "save_contour.cpp"

using namespace cv;

const std::vector<std::vector<Point> > diamond_contour =
    LoadContour("./images/diamond2.png");
const std::vector<std::vector<Point> > squiggle_contour =
    LoadContour("./images/squiggle2.png");
const std::vector<std::vector<Point> > oval_contour =
    LoadContour("./images/oval2.png");

class Card {
 public:
  Card(Mat rgb_image_);
  std::vector<char> GetClassification() { return classification_; }
  // human readable information
  std::vector<std::string> GetCardInfo() {
    return std::vector<std::string>{color_, std::to_string(num_symbol_ + 1),
                                    shape_, shading_};
  }
  void ClassifyCard();
  int DetermineColor();
  int DetermineNumber();
  int DetermineShape();
  int DetermineShading();

  void ShowRgbImage();
  void ShowHsvImage();
  void ShowThreshImage();
  void ShowContourImage();
  void DisplayText();
  ~Card();

 private:
  // card properties
  std::string shape_;
  int shape_id_;
  std::string color_;
  int color_id_;
  int num_symbol_;
  std::string shading_;
  int shading_id_;
  std::vector<char> classification_;

  // image stuff
  Mat rgb_image_;
  Mat hsv_image_;
  Mat thresh_image_;
  Mat contour_image_;
  std::vector<std::vector<Point> > contours_;

  std::string colors_[3] = {"red", "green", "purple"};
  std::string shapes_[3] = {"diamond", "oval", "squiggle"};
  std::string shadings_[3] = {"outlined", "solid", "striped"};
};

Card::Card(Mat input_image) {
  rgb_image_ = input_image.clone();
  cvtColor(rgb_image_, hsv_image_, COLOR_BGR2HSV);
}

Card::~Card() {}

void Card::ClassifyCard() { 
  DetermineColor();
  DetermineNumber();
  DetermineShape();
  DetermineShading();
}

// Finds the color of the symbols. Either red (0), green (1), or purple (2).
int Card::DetermineColor() {
  // green
  inRange(hsv_image_, Scalar(60, 100, 100), Scalar(80, 255, 255),
          thresh_image_);
  if (countNonZero(thresh_image_) > 0) {
    color_id_ = 1;
    color_ = colors_[1];
    classification_.push_back((char)color_id_);
    return color_id_;
  }

  // purple
  inRange(hsv_image_, Scalar(140, 50, 50), Scalar(160, 250, 255),
          thresh_image_);
  if (countNonZero(thresh_image_) > 0) {
    color_id_ = 2;
    color_ = colors_[2];
    classification_.push_back((char)color_id_);
    return color_id_;
  }

  // red
  Mat red_lower, red_upper;
  inRange(hsv_image_, Scalar(0, 100, 100), Scalar(20, 255, 255), red_lower);
  inRange(hsv_image_, Scalar(160, 100, 100), Scalar(180, 255, 255), red_upper);
  bitwise_or(red_lower, red_upper, thresh_image_);
  if (countNonZero(thresh_image_) > 0) {
    color_id_ = 0;
    color_ = colors_[0];
    classification_.push_back((char)color_id_);
    return color_id_;
  }
}

// Finds the number of symbols per card. Cards have either 1, 2, or 3 but this
// gets remapped to 0, 1, or 2.
int Card::DetermineNumber() {
  // Dilate and erode
  Mat erroded, dilated;
  dilate(thresh_image_, dilated, Mat(), Point(-1, -1), 4);
  erode(dilated, erroded, Mat(), Point(-1, -1), 3);
  // imshow("dilated", dilated);
  // imshow("erode", erroded);

  // Find contours_
  std::vector<Vec4i> hierarchy;
  findContours(dilated, contours_, hierarchy, CV_RETR_EXTERNAL,
               CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  // Draw contours_
  contour_image_ = rgb_image_.clone();
  for (int i = 0; i < contours_.size(); i++) {
    drawContours(contour_image_, contours_, i, CV_RGB(0, 0, 255), 2, 8,
                 hierarchy, 0);
  }
  // SaveContour("squiggle.png", contours_, hsv_image_.size());

  num_symbol_ = contours_.size() - 1;
  classification_.push_back((char)num_symbol_);
  return num_symbol_;
}

// Finds the shape of the symbol. Either diamond (0), oval (1), or squiggle (2).
int Card::DetermineShape() {
  double matchDiamond = matchShapes(contours_[0], diamond_contour[0], 1, 0.0);
  double matchSqiggle = matchShapes(contours_[0], squiggle_contour[0], 1, 0.0);
  double matchOval = matchShapes(contours_[0], oval_contour[0], 1, 0.0);

  // std::cout << "   diamond: " << matchDiamond << " | squiggle: " << matchSqiggle
            // << " | oval: " << matchOval << std::endl;

  double matches[3] = {matchDiamond, matchOval, matchSqiggle};
  double minMatch = 1;
  for (int i = 0; i < 3; i++) {
    if (matches[i] < minMatch) {
      minMatch = matches[i];
      shape_id_ = i;
      shape_ = shapes_[i];
    }
  }
  classification_.push_back((char)shape_id_);
  return shape_id_;
}

// Finds the shading of the symbol. Either outlined (0), solid (1), or striped
// (2).
int Card::DetermineShading() {
  // Flood fill contour
  std::vector<Vec4i> hierarchy;
  Mat filled = Mat::zeros(thresh_image_.size(), CV_8UC1);
  drawContours(filled, contours_, 0, CV_RGB(255, 255, 255), -1, 8, hierarchy,
               0);

  // Subract border from flood fill
  // TODO the border size will need to be tuned
  drawContours(filled, contours_, 0, CV_RGB(0, 0, 0), 100, 8, hierarchy, 0);

  // Create mask and apply
  Mat mask, isolated;
  bitwise_not(filled, mask);
  bitwise_and(thresh_image_, filled, isolated);
  // imshow("filled image", mask);
  // imshow("isolated image", isolated);

  // Determine pixels remaining
  int count_black = cv::countNonZero(mask == 0);
  int count_white = cv::countNonZero(isolated == 255);
  int percent_remaining = ((float)count_white / (float)count_black) * 100;
  // std::cout << "black: " << count_black << " | white: " << count_white
  // << "    | %: " << percent_remaining << std::endl;

  // TODO these ranges probably need to be tuned
  if (percent_remaining < 3) {
    shading_id_ = 0;
    shading_ = shadings_[0];
  } else if (percent_remaining > 90) {
    shading_id_ = 1;
    shading_ = shadings_[1];
  } else {
    shading_id_ = 2;
    shading_ = shadings_[2];
  }
  classification_.push_back((char)shading_id_);
  return shading_id_;
}

void Card::ShowRgbImage() {
  namedWindow("Input Image", WINDOW_AUTOSIZE);
  imshow("Input Image", rgb_image_);
}
void Card::ShowHsvImage() {
  namedWindow("HSV Image", WINDOW_AUTOSIZE);
  imshow("HSV Image", hsv_image_);
}
void Card::ShowThreshImage() {
  namedWindow("Thresh Image", WINDOW_AUTOSIZE);
  imshow("Thresh Image", thresh_image_);
}
void Card::ShowContourImage() {
  namedWindow("Contour Image", WINDOW_AUTOSIZE);
  imshow("Contour Image", contour_image_);
}
void Card::DisplayText() {
  // write result on image
  std::string displayText;

  Point center(rgb_image_.cols / 3, rgb_image_.rows / 4);

  for (std::string text : GetCardInfo()) {
    cv::putText(rgb_image_, text, center, CV_FONT_HERSHEY_SIMPLEX, 2,
                Scalar(0));
    center.y -= 50;
  }
  namedWindow("Text Image", WINDOW_AUTOSIZE);
  imshow("Text Image", rgb_image_);
}

#endif