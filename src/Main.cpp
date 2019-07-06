#include <string>
#include <opencv2/opencv.hpp>

#include "LoadImage.cpp"
#include "ClassifyImage.cpp"


int main(int argc, char *argv[]) { 
    std::string filePath = argv[1];
    cv::Mat img = loadImg(filePath);

    // std::string filePath = "./images/g_1_d_e_noBorder.png";
    // cv::Mat img2 = loadImg("./images/b_2_s_h_noBorder.png");
    // cv::Mat img3 = loadImg("./images/r_3_o_f_noBorder.png");

    cv::Mat classImg = ClassifyImage(img);

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", img);

    cv::namedWindow("Classified", cv::WINDOW_AUTOSIZE);
    cv::imshow("Classified", classImg);

    cv::waitKey(0);

    return 0;
}