#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "SaveContour.cpp"

cv::Scalar min_thresh [3] = {cv::Scalar(0, 100, 100),   // red
                            cv::Scalar(60, 100, 100),   // green
                            cv::Scalar(110, 50, 100)};  // blue

cv::Scalar max_thresh [3] = {cv::Scalar(20, 255, 255),
                            cv::Scalar(80, 255, 255),
                            cv::Scalar(130, 150, 255)};

std::string colors[3] = {"red", "green", "blue"};

// Image classifier to determine color, shape, fill, and count.
cv::Mat ClassifyImage(cv::Mat inputImage) {
    // Convert to greyscale
    // cv::Mat greyImage;
    // cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);

    cv::Mat hsvImage;
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);

    // Threshold
    cv::Mat threshImage;
    for (int i = 0; i < 3; i++ ){
        cv::inRange(hsvImage, min_thresh[i], max_thresh[i], threshImage);

        double coloredPixels = cv::countNonZero(threshImage);
        // std::cout << colors[i] << " non zero pixels: " << coloredPixels << std::endl;
    
        // TODO will this need a tollerance?
        if ( coloredPixels > 0 ){
          std::cout << " +++++ Color is: " << colors[i] << std::endl;
          break;
        }
    }

    // Determine edges using Canny
    // cv::Mat cannyImage;
    // cv::floodFill(greyImage, cv::Point(0, 0), cv::Scalar(0));
    // cv::Canny(threshImage, cannyImage, 140, 250, 3);

    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(threshImage, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    std::cout << " +++++ Number of shapes: " << contours.size() << std::endl;

    // Find longest contour
    float max_perimeter = 0;

    // Draw contours
    cv::Mat contourOverlay = threshImage.clone();
    cv::cvtColor(contourOverlay, contourOverlay, cv::COLOR_GRAY2RGB);
    for (int i = 0; i < contours.size(); i++) {
      cv::drawContours(contourOverlay, contours, i, CV_RGB(0, 0, 255), 2, 8,
                       hierarchy, 0);
      // double area = cv::contourArea(contours[i], false);
      // std::cout << "Contour area: " << area << std::endl;
      double perimeter = cv::arcLength(contours[i], false);
      std::cout << "Arc length: " << perimeter << std::endl;

      if (perimeter > max_perimeter) {
        max_perimeter = perimeter;
      }
      std::cout << "Max length: " << max_perimeter << std::endl;
    }

    std::string contourSave = "oval.png";
    saveContour( contourSave, contours, contourOverlay.size());

    // double match = cv::matchShapes(contours[0], contours[1], 1, 0.0);
    // std::cout << "Match: " << match << std::endl;
    return contourOverlay;
}