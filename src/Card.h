#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "SaveContour.cpp"

std::vector<std::vector<cv::Point> > diamondContour = loadContour("./images/diamond.png");
std::vector<std::vector<cv::Point> > squiggleContour = loadContour("./images/squiggle.png");
std::vector<std::vector<cv::Point> > ovalContour = loadContour("./images/oval.png");

class Card
{
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
 cv::Mat rgbImage;
 cv::Mat hsvImage;
 cv::Mat threshImage;

 cv::Scalar min_thresh [3] = {cv::Scalar(0, 100, 100),   // red
                              cv::Scalar(60, 100, 100),   // green
                              cv::Scalar(110, 50, 100)};  // purple TODO recalibrate for purple
 cv::Scalar max_thresh[3] = {cv::Scalar(20, 255, 255), 
                             cv::Scalar(80, 255, 255),
                             cv::Scalar(130, 150, 255)};
 std::string colors[3] = {"red", "green", "purple"};
 std::string shapes [3] = {"diamond", "oval", "squiggle"};
 std::vector<std::vector<cv::Point> > contours;

public:
 Card(cv::Mat rgbImage);
 std::vector<char> GetClassification() {
   return std::vector<char>{(char)shape_id, (char)color_id, (char)number,
                            (char)shading_id};
 }
 std::vector<std::string> GetCardInfo() {
   return std::vector<std::string>{shape, color, std::to_string(number),
                                   shading};
 }
 int DetermineColor();
 int DetermineNumber();
 int DetermineShape();
 void ShowRgbImage();
 void ShowHsvImage();
 void ShowThreshImage();
 ~Card();
};

Card::Card(cv::Mat inputImage) { 
    rgbImage = inputImage.clone();
    cv::cvtColor(rgbImage, hsvImage, cv::COLOR_BGR2HSV);
}

Card::~Card()
{
}

// Finds the color of the symbols. Either red (0), green (1), or purple (2). 
int Card::DetermineColor() {
    for (int i = 0; i < 3; i++) {
      cv::inRange(hsvImage, min_thresh[i], max_thresh[i], threshImage);

      double coloredPixels = cv::countNonZero(threshImage);
      if (coloredPixels > 0) {
        color_id = i;
        color = colors[i];
        break;
      }
    }
    return color_id; 
}

// Finds the number of symbols per card. Cards have either 1, 2, or 3 but this gets remapped to 0, 1, or 2.
int Card::DetermineNumber() {
    // Find contours
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(threshImage, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    number = contours.size() - 1;
    return number;
}

// Finds the shape of the symbol. Either diamond (0), oval (1), or squiggle (2).
int Card::DetermineShape() {
    double matchDiamond = cv::matchShapes(contours[0], diamondContour[0], 1, 0.0);
    double matchSqiggle = cv::matchShapes(contours[0], squiggleContour[0], 1, 0.0); 
    double matchOval = cv::matchShapes(contours[0], ovalContour[0], 1, 0.0);

    // std::cout << "   diamond: " << matchDiamond
    //           << " | squiggle: " << matchSqiggle 
    //           << " | oval: " << matchOval
    //           << std::endl;

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
    cv::namedWindow("Input Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input Image", rgbImage);
}
void Card::ShowHsvImage() {
    cv::namedWindow("HSV Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("HSV Image", hsvImage);
}
void Card::ShowThreshImage() {
    cv::namedWindow("Thresh Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Thresh Image", threshImage);
}