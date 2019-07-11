#include <string>
#include <opencv2/opencv.hpp>

#include "LoadImage.cpp"
#include "ClassifyImage.cpp"


int main(int argc, char *argv[]) { 
    std::string filePath = argv[1];
    cv::Mat img = loadImg(filePath);

    cv::Mat classImg = ClassifyImage(img);

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", img);

    cv::namedWindow("Classified", cv::WINDOW_AUTOSIZE);
    cv::imshow("Classified", classImg);

    cv::waitKey(0);

    return 0;
}