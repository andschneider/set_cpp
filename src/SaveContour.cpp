#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>

void saveContour( std::vector<std::vector<cv::Point> >, cv::Size );


void saveContour( std::string filePath, std::vector<std::vector<cv::Point> > contours, cv::Size outputImgSize ) {
    cv::Mat canvas = cv::Mat::zeros( outputImgSize, CV_8UC3 );

    std::vector<cv::Vec4i> hierarchy;
    cv::drawContours(canvas, contours, 0, CV_RGB(255, 255, 255), 2, 8,
                     hierarchy, 0);

    cv::imwrite(filePath, canvas);

    std::cout << "Image successfully saved to " << filePath << std::endl;
}
