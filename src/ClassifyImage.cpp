
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>

cv::Scalar min_thresh [3] = {cv::Scalar(0, 100, 100),   // red
                            cv::Scalar(60, 100, 100),   // green
                            cv::Scalar(100, 50, 100)};  // blue

cv::Scalar max_thresh [3] = {cv::Scalar(20, 255, 255),
                            cv::Scalar(80, 255, 255),
                            cv::Scalar(120, 150, 255)};

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
    
        if ( coloredPixels > 0 ){
          std::cout << " +++++ Color is: " << colors[i] << std::endl;
          break;
        }
    }

    // Determine edges using Canny
    cv::Mat cannyImage;
    // cv::floodFill(greyImage, cv::Point(0, 0), cv::Scalar(0));
    cv::Canny(threshImage, cannyImage, 140, 250, 3);

    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(cannyImage, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    std::cout << "Number of shapes: " << contours.size() << std::endl;

    // Draw contours
    cv::Mat drawing = cv::Mat::zeros( hsvImage.size(), CV_8UC3 );
    for (int i =0; i < contours.size(); i++ ){
        cv::drawContours(drawing, contours, i, CV_RGB(0, 0, 255), 2, 8,
                        hierarchy, 0);
        // double area = cv::contourArea(contours[i], false);
        // std::cout << "Contour area: " << area << std::endl;
    }

    return drawing;
}