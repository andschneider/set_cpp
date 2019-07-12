#include <algorithm>
#include <initializer_list>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "SaveContour.cpp"


// TODO gotta be a better way to do this
cv::Scalar min_thresh [3] = {cv::Scalar(0, 100, 100),   // red
                            cv::Scalar(60, 100, 100),   // green
                            cv::Scalar(110, 50, 100)};  // purple TODO recalibrate for purple

cv::Scalar max_thresh [3] = {cv::Scalar(20, 255, 255),
                            cv::Scalar(80, 255, 255),
                            cv::Scalar(130, 150, 255)};

std::string colors[3] = {"red", "green", "purple"};


int DetermineColor(cv::Mat hsvImage){
    // Apply range of thresholds to determine color
    int color;
    for (int i = 0; i < 3; i++) {
      cv::Mat threshImage;
      cv::inRange(hsvImage, min_thresh[i], max_thresh[i], threshImage);

      double coloredPixels = cv::countNonZero(threshImage);
      if (coloredPixels > 0) {
        color = i;
        break;
      }
    }
    return color;
}


// Image classifier to determine color, shape, shading, and number.
std::vector<char>  ClassifyImage(cv::Mat inputImage) {

    int color_index = DetermineColor(inputImage);
    std::string color = colors[color_index];

    cv::Mat threshImage;
    cv::inRange(inputImage, min_thresh[color_index], max_thresh[color_index], threshImage);
    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(threshImage, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    int numberShapes = contours.size();

    // Draw contours
    // cv::Mat contourOverlay = threshImage.clone();
    // // cv::cvtColor(contourOverlay, contourOverlay, cv::COLOR_GRAY2RGB);
    // for (int i = 0; i < contours.size(); i++) {
    //   cv::drawContours(contourOverlay, contours, i, CV_RGB(0, 0, 255), 2, 8,
    //                    hierarchy, 0);
    // }
    
    // Match contours
    std::vector<std::vector<cv::Point> > diamondContour = loadContour("./images/diamond.png");
    std::vector<std::vector<cv::Point> > squiggleContour = loadContour("./images/squiggle.png");
    std::vector<std::vector<cv::Point> > ovalContour = loadContour("./images/oval_small.png");

    double matchDiamond = cv::matchShapes(contours[0], diamondContour[0], 1, 0.0);
    double matchSqiggle = cv::matchShapes(contours[0], squiggleContour[0], 1, 0.0); 
    double matchOval = cv::matchShapes(contours[0], ovalContour[0], 1, 0.0); 

    std::cout << "   diamond: " << matchDiamond 
              << " | squiggle: " << matchSqiggle 
              << " | oval: " << matchOval 
              << std::endl;

    std::string shapes [3] = {"diamond", "oval", "squiggle"};
    double matches [3] = {matchDiamond, matchSqiggle, matchOval};
    double minMatch = 1;
    int shape_index = 0;
    for (int i = 0; i < 3; i++) {
      if (matches[i] < minMatch) {
        minMatch = matches[i];
        shape_index = i;
      }
    }

    std::cout << "\n";
    std::cout << " >> Number:  " << numberShapes << std::endl;
    std::cout << " >> Color:   " << color << std::endl;
    std::cout << " >> Shape:   " << shapes[shape_index] << std::endl;

    // return contourOverlay;
    return std::vector<char>{(char)numberShapes, (char)color_index, (char)shape_index};
}