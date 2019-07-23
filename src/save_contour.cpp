#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>

void SaveContour( std::vector<std::vector<cv::Point> >, cv::Size );
std::vector<std::vector<cv::Point> > LoadContour( std::string );


// Saves a single contour out as a white outline on a black background.
void SaveContour( std::string file_path, std::vector<std::vector<cv::Point> > contours, cv::Size output_image_size ) {
    cv::Mat canvas = cv::Mat::zeros( output_image_size, CV_8UC1 );

    std::vector<cv::Vec4i> hierarchy;
    cv::drawContours(canvas, contours, 0, CV_RGB(255, 255, 255), 2, 8,
                     hierarchy, 0);

    cv::imwrite(file_path, canvas);

    std::cout << "Image successfully saved to " << file_path << std::endl;
}


// Loads an image that was created using the SaveContour function and finds a contour.
// This is used for contour matching to determine a card's shape.
std::vector<std::vector<cv::Point> > LoadContour( std::string file_path) {
    cv::Mat input_img = cv::imread( file_path, 0 );

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(input_img, contours, hierarchy, CV_RETR_EXTERNAL,
                    CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // std::cout << "Contour successfully created" << std::endl;
    return contours;
}
