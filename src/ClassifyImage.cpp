
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>


// Image classifier to determine color, shape, and count.
cv::Mat ClassifyImage(cv::Mat inputImage) {
    // Convert to greyscale
    cv::Mat greyImage;
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);

    // Threshold
    // cv::Mat threshImage;
    // cv::threshold(greyImage, threshImage, 160, 255, cv::THRESH_BINARY);

    // Determine edges using Canny
    cv::Mat cannyImage;
    // cv::floodFill(greyImage, cv::Point(0, 0), cv::Scalar(0));
    cv::Canny(greyImage, cannyImage, 140, 250, 3);

    // Find contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(cannyImage, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    std::cout << "Number of shapes: " << contours.size() << std::endl;

    // Draw contours
    cv::Mat drawing = cv::Mat::zeros( greyImage.size(), CV_8UC3 );
    for (int i =0; i < contours.size(); i++ ){
        cv::drawContours(drawing, contours, i, CV_RGB(0, 0, 255), 2, 8,
                        hierarchy, 0);
        // double area = cv::contourArea(contours[i], false);
        // std::cout << "Contour area: " << area << std::endl;
    }

    return drawing;
}