#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "SaveContour.cpp"

using namespace cv;

std::vector<std::vector<Point> > diamondContour = loadContour("./images/diamond.png");
std::vector<std::vector<Point> > squiggleContour = loadContour("./images/squiggle.png");
std::vector<std::vector<Point> > ovalContour = loadContour("./images/oval2.png");


class Card {
 private:
  // card properties
  std::string shape;
  int shape_id;
  std::string color;
  int color_id;
  int number;
  std::string shading;
  int shading_id;
  std::vector<char> classification;

  // image stuff
  Mat rgbImage;
  Mat hsvImage;
  Mat threshImage;
  Mat contourImage;

  std::string colors[3] = {"red", "green", "purple"};
  std::string shapes[3] = {"diamond", "oval", "squiggle"};
  std::vector<std::vector<Point> > contours;

 public:
  Card(Mat rgbImage);
  std::vector<char> GetClassification() {
    return std::vector<char>{(char)shape_id, (char)color_id, (char)number,
                             (char)shading_id};
  }
  std::vector<std::string> GetCardInfo() {
    return std::vector<std::string>{shape, color, std::to_string(number + 1),
                                    shading};
  }
  int DetermineColor();
  int DetermineNumber();
  int DetermineShape();
  void ShowRgbImage();
  void ShowHsvImage();
  void ShowThreshImage();
  void ShowContourImage();
  ~Card();
};

Card::Card(Mat inputImage) { 
    rgbImage = inputImage.clone();
    cvtColor(rgbImage, hsvImage, COLOR_BGR2HSV);
}

Card::~Card()
{
}

// Finds the color of the symbols. Either red (0), green (1), or purple (2). 
int Card::DetermineColor() {
    // green
    inRange(hsvImage, Scalar(60, 100, 100), Scalar(80, 255, 255), threshImage);
    if (countNonZero(threshImage) > 0) {
      color_id = 1;
      color = colors[1];
      return color_id;
    }

    // purple
    // TODO recalibrate ranges
    inRange(hsvImage, Scalar(110, 50, 100), Scalar(130, 150, 255), threshImage);
    if (countNonZero(threshImage) > 0) {
      color_id = 2;
      color = colors[2];
      return color_id;
    }

    // red
    Mat red_lower, red_upper;
    inRange(hsvImage, Scalar(0, 100, 100), Scalar(20, 255, 255), red_lower);
    inRange(hsvImage, Scalar(160, 100, 100), Scalar(180, 255, 255), red_upper);
    bitwise_or(red_lower, red_upper, threshImage);
    if (countNonZero(threshImage) > 0) {
      color_id = 0;
      color = colors[0];
      return color_id;
    }
}

// Finds the number of symbols per card. Cards have either 1, 2, or 3 but this gets remapped to 0, 1, or 2.
int Card::DetermineNumber() {
    // Find contours
    std::vector<Vec4i> hierarchy;
    findContours(threshImage, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // Draw contours
    contourImage = rgbImage.clone();
    for (int i = 0; i < contours.size(); i++) {
      drawContours(contourImage, contours, i, CV_RGB(0, 0, 255), 2, 8,
                       hierarchy, 0);
    }
    // saveContour("contour.png", contours, hsvImage.size());
    
    number = contours.size() - 1;
    return number;
}

// Finds the shape of the symbol. Either diamond (0), oval (1), or squiggle (2).
int Card::DetermineShape() {
    double matchDiamond = matchShapes(contours[0], diamondContour[0], 1, 0.0);
    double matchSqiggle = matchShapes(contours[0], squiggleContour[0], 1, 0.0); 
    double matchOval = matchShapes(contours[0], ovalContour[0], 1, 0.0);

    std::cout << "   diamond: " << matchDiamond
              << " | squiggle: " << matchSqiggle 
              << " | oval: " << matchOval
              << std::endl;

    double matches [3] = {matchDiamond, matchOval, matchSqiggle};
    double minMatch = 1;
    for (int i = 0; i < 3; i++) {
      if (matches[i] < minMatch) {
        minMatch = matches[i];
        shape_id = i;
        shape = shapes[i];
      }
    }
    return shape_id;
}

void Card::ShowRgbImage() {
    namedWindow("Input Image", WINDOW_AUTOSIZE);
    imshow("Input Image", rgbImage);
}
void Card::ShowHsvImage() {
    namedWindow("HSV Image", WINDOW_AUTOSIZE);
    imshow("HSV Image", hsvImage);
}
void Card::ShowThreshImage() {
    namedWindow("Thresh Image", WINDOW_AUTOSIZE);
    imshow("Thresh Image", threshImage);
}
void Card::ShowContourImage() {
    namedWindow("Contour Image", WINDOW_AUTOSIZE);
    imshow("Contour Image", contourImage);
}
