#include <string>
#include <opencv2/opencv.hpp>

#include "LoadImage.cpp"
#include "ClassifyImage.cpp"


int main(int argc, char *argv[]) { 
    std::string filePath = argv[1];
    cv::Mat img = loadImg(filePath);

    // Get idenification vector for a card
    std::vector<char> img_identifier = ClassifyImage(img);

    for (int x : img_identifier){
        std::cout << x << " ";
    }
    std::cout << std::endl;  // flush before image pops up

    // Dont convert this one to HSV
    cv::Mat displayImg = loadImg(filePath, false);
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", displayImg);

    // cv::namedWindow("Classified", cv::WINDOW_AUTOSIZE);
    // cv::imshow("Classified", classImg);

    cv::waitKey(0);

    return 0;
}